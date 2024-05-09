#include "highlight.h"
#include "variables.h"

#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Editor.H>

const char* code_keywords[] = { // List of known C/C++ keywords...
                     "and",
                     "and_eq",
                     "asm",
                     "bitand",
                     "bitor",
                     "break",
                     "case",
                     "catch",
                     "compl",
                     "continue",
                     "default",
                     "delete",
                     "do",
                     "else",
                     "false",
                     "for",
                     "goto",
                     "if",
                     "new",
                     "not",
                     "not_eq",
                     "operator",
                     "or",
                     "or_eq",
                     "return",
                     "switch",
                     "template",
                     "this",
                     "throw",
                     "true",
                     "try",
                     "using",
                     "while",
                     "xor",
                     "xor_eq"
};
const char* code_types[] = {    // List of known C/C++ types...
                     "auto",
                     "bool",
                     "char",
                     "class",
                     "const",
                     "const_cast",
                     "double",
                     "dynamic_cast",
                     "enum",
                     "explicit",
                     "extern",
                     "float",
                     "friend",
                     "inline",
                     "int",
                     "long",
                     "mutable",
                     "namespace",
                     "private",
                     "protected",
                     "public",
                     "register",
                     "short",
                     "signed",
                     "sizeof",
                     "static",
                     "static_cast",
                     "struct",
                     "template",
                     "typedef",
                     "typename",
                     "union",
                     "unsigned",
                     "virtual",
                     "void",
                     "volatile"
};

//
// 'compare_keywords()' - Compare two keywords...
//

extern "C" {
    int
        compare_keywords(const void* a,
            const void* b) {
        return (strcmp(*((const char**)a), *((const char**)b)));
    }
}

// 初始化，不然会报指针错误
void style_init(void) {
    char* style = new char[textbuffer->length() + 1];
    const char* text = textbuffer->text();

    memset(style, 'A', textbuffer->length());
    style[textbuffer->length()] = '\0';

    if (!stylebuf) stylebuf = new Fl_Text_Buffer(textbuffer->length());

    style_parse(text, style, textbuffer->length());

    stylebuf->text(style);
    delete[] style;
}

//
// 'style_update()' - Update the style buffer...
//

void
style_update(int        pos,          // I - Position of update
    int        nInserted,    // I - Number of inserted chars
    int        nDeleted,     // I - Number of deleted chars
    int        nRestyled,    // I - Number of restyled chars
    const char* deletedText, // I - Text that was deleted
    void* cbArg) {     // I - Callback data
    int  start,                         // Start of text
        end;                           // End of text
    char last,                          // Last style on line
        * style,                        // Style data
        * text;                         // Text data


    // If this is just a selection change, just unselect the style buffer...
    if (nInserted == 0 && nDeleted == 0) {
        stylebuf->unselect();
        return;
    }

    // Track changes in the text buffer...
    if (nInserted > 0) {
        // Insert characters into the style buffer...
        style = new char[nInserted + 1];
        memset(style, 'A', nInserted);
        style[nInserted] = '\0';

        stylebuf->replace(pos, pos + nDeleted, style);
        delete[] style;
    }
    else {
        // Just delete characters in the style buffer...
        stylebuf->remove(pos, pos + nDeleted);
    }

    // Select the area that was just updated to avoid unnecessary
    // callbacks...
    stylebuf->select(pos, pos + nInserted - nDeleted);

    // Re-parse the changed region; we do this by parsing from the
    // beginning of the line of the changed region to the end of
    // the line of the changed region...  Then we check the last
    // style character and keep updating if we have a multi-line
    // comment character...
    start = textbuffer->line_start(pos);
    end = textbuffer->line_end(pos + nInserted - nDeleted);
    text = textbuffer->text_range(start, end);
    style = stylebuf->text_range(start, end);
    last = style[end - start - 1];

    style_parse(text, style, end - start);

    stylebuf->replace(start, end, style);
    ((Fl_Text_Editor*)cbArg)->redisplay_range(start, end);

    if (last != style[end - start - 1]) {
        // The last character on the line changed styles, so reparse the
        // remainder of the buffer...
        free(text);
        free(style);

        end = textbuffer->length();
        text = textbuffer->text_range(start, end);
        style = stylebuf->text_range(start, end);

        style_parse(text, style, end - start);

        stylebuf->replace(start, end, style);
        ((Fl_Text_Editor*)cbArg)->redisplay_range(start, end);
    }

    free(text);
    free(style);
}

//
// 'style_parse()' - Parse text and produce style data.
//

void
style_parse(const char* text, char* style, int length) {
    char            current;
    int             col;
    int             last;
    char            buf[1024], * bufptr;
    const char* temp;

    for (current = *style, col = 0, last = 0; length > 0; length--, text++) {
        if (current == 'A') {
            // Check for directives, comments, strings, and keywords...
            if (col == 0 && *text == '#') {
                // Set style to directive
                current = 'E';
            }
            else if (strncmp(text, "//", 2) == 0) {
                current = 'B';
            }
            else if (strncmp(text, "/*", 2) == 0) {
                current = 'C';
            }
            else if (strncmp(text, "\\\"", 2) == 0) {
                // Quoted quote...
                *style++ = current;
                *style++ = current;
                text++;
                length--;
                col += 2;
                continue;
            }
            else if (*text == '\"') {
                current = 'D';
            }
            // 还判断了这个是不是关键字。但是由于有islower()这个函数，导致输入的是中文的话，会报错（还没找到解决办法）。
            // 只能是删除了这个，删除后可以正常运行，这样就可以了，哈哈
        }
        else if (current == 'C' && strncmp(text, "*/", 2) == 0) {
            // Close a C comment...
            *style++ = current;
            *style++ = current;
            text++;
            length--;
            current = 'A';
            col += 2;
            continue;
        }
        else if (current == 'D') {
            // Continuing in string...
            if (strncmp(text, "\\\"", 2) == 0) {
                // Quoted end quote...
                *style++ = current;
                *style++ = current;
                text++;
                length--;
                col += 2;
                continue;
            }
            else if (*text == '\"') {
                // End quote...
                *style++ = current;
                col++;
                current = 'A';
                continue;
            }
        }

        // Copy style info...
        if (current == 'A' && (*text == '{' || *text == '}')) *style++ = 'G';
        else *style++ = current;
        col++;
        // 想检查输入的是否是字母、数字或者是. 但是这个判断对于中文来说似乎也没有啥意义。所以感觉也可以删除
        // last = isalnum(*text) || *text == '.';

        if (*text == '\n') {
            // Reset column and possibly reset the style
            col = 0;
            if (current == 'B' || current == 'E') current = 'A';
        }
    }
}

// 这个函数不需要实现，做个空函数就行
void style_unfinished_cb(int, void*) {}