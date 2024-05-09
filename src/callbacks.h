#pragma once

#include <FL/Fl_Widget.H>

void find_cb(Fl_Widget* widget, void* data);
void find2_cb(Fl_Widget* widget, void* data);

void changed_cb(int, int nInserted, int nDeleted, int, const char*, void* data);

void replace_cb(Fl_Widget* widget, void* data);
void replace2_cb(Fl_Widget* widget, void* data);
// 替换文件中出现的所有搜索字符串
void replall_cb(Fl_Widget* widget, void* data);
void replcan_cb(Fl_Widget* widget, void* data);

void exitCallback(Fl_Widget* widget, void* data);
void paste_cb(Fl_Widget* widget, void* data);

void copy_cb(Fl_Widget* widget, void* data);
void cut_cb(Fl_Widget* widget, void* data);
void delete_cb(Fl_Widget* widget, void* data);
void undoCallback(void);

void saveas_cb(void);
void save_cb(void);
void open_cb(Fl_Widget* widget, void* data);
void new_cb(Fl_Widget* widget, void* data);