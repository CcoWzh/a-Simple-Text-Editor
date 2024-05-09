#include "callbacks.h"
#include <cstdlib> // exit
#include <string>

#include "EditorWindow.h"
#include "variables.h"
#include "other.h"

#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Text_Editor.H>

void find2_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    if (window->search[0] == '\0')
    {
        find_cb(widget, data);
        return;
    }

    window->editor->insert_position(0);

    int pos = window->editor->insert_position();
    int found = textbuffer->search_forward(pos, window->search, &pos);

    if (found)
    {
        textbuffer->select(pos, pos + strlen(window->search));
        window->editor->insert_position(pos + strlen(window->search));
        window->editor->show_insert_position();
    }
    else fl_alert("No occurrences of \'%s\' found!", window->search);
}

void find_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    const char* value = fl_input("Search String:", window->search);

    if (value != NULL)
    {
        strcpy(window->search, value);
        find2_cb(widget, data);
    }
}

// 用户改变文本的内容时，回调这个函数
void changed_cb(int, int nInserted, int nDeleted, int, const char*, void* data)
{
    if ((nInserted || nDeleted) && !loading) changed = 1;
    EditorWindow* window = (EditorWindow*)data;
    set_title(window);
    if (loading) window->editor->show_insert_position();
}

void replace_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    window->replace_dlg->show();
}

void replace2_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    const char* find = window->replace_find->value();
    const char* replace = window->replace_with->value();

    if (find[0] == '\0')
    {
        window->replace_dlg->show();
        return;
    }

    window->replace_dlg->hide();

    window->editor->insert_position(0);

    int pos = window->editor->insert_position();
    int found = textbuffer->search_forward(pos, find, &pos);

    if (found)
    {
        textbuffer->select(pos, pos + strlen(find));
        textbuffer->remove_selection();
        textbuffer->insert(pos, replace);
        textbuffer->select(pos, pos + strlen(replace));

        window->editor->insert_position(pos + strlen(replace));
        window->editor->show_insert_position();
    }
    else fl_alert("No occurrences of \'%s\' found!", find);
}

void replall_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    const char* find = window->replace_find->value();
    const char* replace = window->replace_with->value();

    find = window->replace_find->value();

    if (find[0] == '\0')
    {
        window->replace_dlg->show();
        return;
    }

    window->replace_dlg->hide();

    window->editor->insert_position(0);
    int times = 0;

    for (int found = 1; found;)
    {
        int pos = window->editor->insert_position();
        found = textbuffer->search_forward(pos, find, &pos);

        if (found)
        {
            textbuffer->select(pos, pos + strlen(find));
            textbuffer->remove_selection();
            textbuffer->insert(pos, replace);

            window->editor->insert_position(pos + strlen(replace));
            window->editor->show_insert_position();
            times++;
        }
    }

    if (times) fl_message("Replaced %d occurrences.", times);
    else fl_alert("No occurrences of \'%s\' found!", find);
}

void replcan_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    window->replace_dlg->hide();
}

void exitCallback(Fl_Widget* widget, void* data)
{
    exit(0);
}

void paste_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    Fl_Text_Editor::kf_paste(0, window->editor);
}

void copy_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    Fl_Text_Editor::kf_copy(0, window->editor);
}

void cut_cb(Fl_Widget* widget, void* data)
{
    EditorWindow* window = (EditorWindow*)data;
    Fl_Text_Editor::kf_cut(0, window->editor);
}

void delete_cb(Fl_Widget* widget, void* data)
{
    textbuffer->remove_selection();
}

void undoCallback(void)
{
    textbuffer->undo();
}

void saveas_cb(void)
{
    char* newfile;

    newfile = fl_file_chooser("Save File As?", "*", filename);
    if (newfile != nullptr) save_file(newfile);
}

void save_cb(void)
{
    if (filename[0] == '\0')
    {
        saveas_cb();
        return;
    }
    else save_file(filename);
}

void open_cb(Fl_Widget* widget, void* data)
{
    if (!check_save()) return;

    char* newfile = fl_file_chooser("Open File?", "*", filename);
    if (newfile != nullptr) load_file(newfile, -1);
}

void new_cb(Fl_Widget* widget, void* data)
{
    if (!check_save()) return;

    filename[0] = '\0';
    textbuffer->select(0, textbuffer->length());
    textbuffer->remove_selection();
    changed = 0;
    textbuffer->call_modify_callbacks();
}