/*
 ���ͷ�ļ���Ϊȫ�ֱ����Ķ��塣������Ҳ���õ�
*/
#pragma once
#include <FL/Fl_Text_Buffer.H>
#include <string>

extern int changed;
extern Fl_Text_Buffer* textbuffer;
extern int loading;
extern char filename[256];
extern std::string title;
extern Fl_Text_Buffer* stylebuf;