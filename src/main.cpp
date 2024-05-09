#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Menu_Item.H>

#include "other.h"
#include "EditorWindow.h"
#include "callbacks.h"
#include "highlight.h"

// �ı��༭����Ҫ����ȫ�ֱ���������һЩ�¼�
int changed = 0;
Fl_Text_Buffer* textbuffer = 0;
char filename[256] = "";
std::string title = "Untitled";
int loading = 0;
Fl_Text_Buffer* stylebuf = 0;

// �������ǵ��ı��༭�������ǽ�Ϊ�����롢ע�͡��ؼ��ֺ�Ԥ������ָ���7����ʽ��
// ����<FL/Fl_Text_Display.H>ͷ�ļ�
Fl_Text_Display::Style_Table_Entry styletable[] = {     // Style table
  { FL_BLACK,      FL_COURIER,        FL_NORMAL_SIZE }, // A - Plain
  { FL_DARK_GREEN, FL_COURIER_ITALIC, FL_NORMAL_SIZE }, // B - Line comments
  { FL_DARK_GREEN, FL_COURIER_ITALIC, FL_NORMAL_SIZE }, // C - Block comments
  { FL_BLUE,       FL_COURIER,        FL_NORMAL_SIZE }, // D - Strings
  { FL_DARK_RED,   FL_COURIER,        FL_NORMAL_SIZE }, // E - Directives
  { FL_DARK_RED,   FL_COURIER_BOLD,   FL_NORMAL_SIZE }, // F - Types
  { FL_BLUE,       FL_COURIER_BOLD,   FL_NORMAL_SIZE }  // G - Keywords
};

// ��һ��Ŀ��Ҫ������ʹ�ò˵����Ͷ���༭����Ҫִ�е�ÿ�����ܵĲ˵�
// Fl_Menu_Item�ṹ���ڶ���˵����еĲ˵�����Ŀ
static void buildMenu(Fl_Menu_Bar* menu, Fl_Window* window)
{
    Fl_Menu_Item menuItems[] =
    {
        {"&File", 0, 0, 0, FL_SUBMENU},
            {"&New file", 0, new_cb},
            {"&Open file", FL_COMMAND + 'o', open_cb},
            {"&Save file", FL_COMMAND + 's', (Fl_Callback*)save_cb},
            {"&Save file as", FL_COMMAND + FL_SHIFT + 's', (Fl_Callback*)saveas_cb, 0, FL_MENU_DIVIDER},
            {"&Exit", FL_COMMAND + 'q', exitCallback, 0},
            { 0 },
        {"&Edit", 0, 0, 0, FL_SUBMENU },
            {"&Undo", FL_COMMAND + 'z', (Fl_Callback*)undoCallback, 0, FL_MENU_DIVIDER},
            {"&Cut", FL_COMMAND + 'x', cut_cb, window},
            {"&Copy", FL_COMMAND + 'c', copy_cb, window},
            {"&Paste", FL_COMMAND + 'v', paste_cb, window},
            {"&Delete", 0, delete_cb},
            { 0 },
        {"&Search", 0, 0, 0, FL_SUBMENU},
            {"&Find", FL_COMMAND + 'f', find_cb, window},
            {"&Find again", FL_COMMAND + 'g', find2_cb, window},
            {"&Replace", FL_COMMAND + 'r', replace_cb, window},
            {"&Replace again", FL_COMMAND + 't', replace2_cb, window},
            { 0 },
        { 0 },
    };
    menu->copy(menuItems);
}

Fl_Window* newView()
{
    EditorWindow* window = new EditorWindow(800, 600, title);

    window->begin();
    // һ�������˲˵������ǾͿ��Դ���Fl_Menu_Bar���������˵����������
    Fl_Menu_Bar* menuBar = new Fl_Menu_Bar(0, 0, 800, 30);
    buildMenu(menuBar, window);

    window->editor = new Fl_Text_Editor(10, 30, 780, 560);
    window->editor->buffer(textbuffer);
    window->editor->highlight_data(stylebuf, styletable,
        sizeof(styletable)/sizeof(styletable[0]),
        'A', style_unfinished_cb, 0);
    window->editor->textfont(FL_COURIER);
    window->end();

    window->resizable(window->editor);
    window->editor->linenumber_width(60);

    textbuffer->add_modify_callback(changed_cb, window);
    // �������ܣ��ı�������ʾ
    textbuffer->add_modify_callback(style_update, window->editor);
    textbuffer->call_modify_callbacks();
    return window;
}

int main(int argc, char** argv) {
    textbuffer = new Fl_Text_Buffer;
    style_init();

    Fl_Window* window = newView();

    window->show(1, argv);

    if (argc > 1) load_file(argv[1], -1);

    return Fl::run();
}