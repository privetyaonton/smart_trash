#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "error.h"

using namespace std;

string set_path (const char * root, const char * obj);

class FileTrash
{
    private:
        int fd;
        map <string, string> dataTrash;

    public:
        FileTrash ();

        void close_file ();

        string get_path_obj (string name);

        void add_value (string name, string path);

        void remove_value (string name);

        map <string, string>& getData ();

        pair <string, string> getObject (int index);

        void clear ();

        void print ();
};



#endif