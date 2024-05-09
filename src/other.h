/*
  #pragma once是预处理指令，在头文件的最开始加入这条预处理指令，可以保证头文件只被编译一次
  #本文件实现一些基础功能，如，存文件、读文件等
*/

#pragma once

#include <string>
#include <FL/Fl_Widget.H>

int check_save();
void load_file(char* newfile, int ipos);
void save_file(char* newfile);
void set_title(Fl_Window* widget);