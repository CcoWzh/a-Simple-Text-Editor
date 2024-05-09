/*
 ���ļ�ʵ���ı��ĸ���
*/
#pragma once

#include "variables.h"
#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>

void style_init(void);
void style_update(int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg);
void style_parse(const char* text, char* style, int length);
void style_unfinished_cb(int, void*);