#ifndef TRASH_H
#define TRASH_H
#define STRING_SIZE 24
#include "File.h"

const string commands[] = {"remove", "list", "help", "recov", "clr", "clrall", "recovall"};

void print_help ();

void remove_content_dir (string path);

class Trash
{
    private:
        string cmd;
        string cmd_arg;
        FileTrash fileTrash;

    public:

        Trash();

        int start(int narg, const char ** args);

        int exec ();
};



#endif