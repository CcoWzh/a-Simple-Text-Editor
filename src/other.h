/*
  #pragma once��Ԥ����ָ���ͷ�ļ����ʼ��������Ԥ����ָ����Ա�֤ͷ�ļ�ֻ������һ��
  #���ļ�ʵ��һЩ�������ܣ��磬���ļ������ļ���
*/

#pragma once

#include <string>
#include <FL/Fl_Widget.H>

int check_save();
void load_file(char* newfile, int ipos);
void save_file(char* newfile);
void set_title(Fl_Window* widget);