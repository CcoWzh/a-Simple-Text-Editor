/*
 这是一个窗口类
*/
#pragma once

#include <string>

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Return_Button.H>

class EditorWindow : public Fl_Double_Window
{
public:
    EditorWindow(int width, int height, std::string& title);
    ~EditorWindow();

    Fl_Window* replace_dlg;
    Fl_Input* replace_find;
    Fl_Input* replace_with;
    Fl_Button* replace_all;
    Fl_Return_Button* replace_next;
    Fl_Button* replace_cancel;

    Fl_Text_Editor* editor;
    char search[256];
};