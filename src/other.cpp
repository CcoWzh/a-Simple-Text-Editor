#include "variables.h"
#include "other.h"
#include "callbacks.h"
#include <FL/Fl_File_Chooser.H>

int check_save()
{
    if (!changed) return 1;

    int result = fl_choice("The current file has not been saved.\n"
        "Would you like to save it now?",
        "Cancel", "Save", "Discard");

    if (result == 1)
    {
        save_cb();
        return !changed;
    }

    return (result == 2) ? 1 : 0;
}

void load_file(char* newfile, int ipos)
{
    loading = 1;
    int insert = (ipos != -1);
    changed = insert;
    if (!insert) strcpy(filename, "");
    int result;
    if (!insert) result = textbuffer->loadfile(newfile);
    else result = textbuffer->insertfile(newfile, ipos);
    if (result)
        fl_alert("Error reading from file \'%s\':\n%s.", newfile, strerror(errno));
    else
        if (!insert) strcpy(filename, newfile);
    loading = 0;
    textbuffer->call_modify_callbacks();
}

void save_file(char* newfile)
{
    if (textbuffer->savefile(newfile))
        fl_alert("Error writing to file \'%s\':\n%s.", newfile, strerror(errno));
    else
        strcpy(filename, newfile);
    changed = 0;
    textbuffer->call_modify_callbacks();
}

void set_title(Fl_Window* widget)
{
    if (filename[0] == '\0') title.assign("Untitled");
    else
    {
        char* slash;
        slash = strrchr(filename, '/');
#ifdef WIN32
        if (slash == NULL) slash = strrchr(filename, '\\');
#endif
        if (slash != NULL) title.assign(slash + 1);
        else title.assign(filename);
    }

    if (changed) title.append(" (modified)");
    widget->label(title.c_str());
}
