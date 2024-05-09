#include "EditorWindow.h"
#include "callbacks.h"

// “替代”对话框
EditorWindow::EditorWindow(int width, int height, std::string& title)
    : Fl_Double_Window(width, height, title.c_str())
{
    replace_dlg = new Fl_Window(300, 105, "Replace");
    replace_find = new Fl_Input(80, 10, 210, 25, "Find:");
    replace_with = new Fl_Input(80, 40, 210, 25, "Replace:");
    // 替换文字，回调replall_cb函数
    replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
    replace_all->callback((Fl_Callback*)replall_cb, this);

    replace_next = new Fl_Return_Button(105, 70, 120, 25, "Replace Next");
    replace_next->callback((Fl_Callback*)replace2_cb, this);

    replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");
    replace_cancel->callback((Fl_Callback*)replcan_cb, this);
    replace_dlg->end();
    editor = 0;
    *search = (char)0;
}

EditorWindow::~EditorWindow()
{
    delete replace_dlg;
}