#include "Trash.h"

void Trash::start (int narg, const char ** args)
{
    if (narg < 2 || narg > 3)  throw (ERNARGS);

    string start_cmd (args[1]);
    string start_arg ((narg == 3) ? args[2] : "");

    for (int i = 0; i < sizeof (commands) / STRING_SIZE; i++)
    {
        if (start_cmd == commands[i])
        {
            cmd = start_cmd;
            cmd_arg = start_arg;
            return;
        }
    }

    throw (ERINVALIDCMD);
}

Trash::Trash()
{
    // string trash_path = set_path (getenv ("HOME"), ".SmartTrash");
    // //setenv ("TRASHPATH", trash_path.c_str(), 1);
}

void Trash::exec()
{
    if (cmd == "remove")
    {
        if (rename (set_path (getenv ("PWD"), cmd_arg.c_str()).c_str(), 
            set_path (getenv ("TRASHPATH"), cmd_arg.c_str()).c_str()) < 0)
        {
            if (!is_setup_trash())
                throw (ERNOTINSTALL);
            else
                throw (ERFIND);
        }

        fileTrash.add_value (cmd_arg, set_path (getenv ("PWD"), cmd_arg.c_str()));
    }

    if (cmd == "list")
    {
        fileTrash.print();
    }

    if (cmd == "recov")
    {
        int index = atoi (cmd_arg.c_str());


        pair <string, string> this_object = fileTrash.getObject (index);
        
        if (rename (set_path (getenv ("TRASHPATH"), this_object.first.c_str()).c_str(), this_object.second.c_str()) < 0)
            return throw (ERNOTINSTALL);

        fileTrash.remove_value (this_object.first);
    }

    if (cmd == "clr")
    {
        int index = atoi (cmd_arg.c_str());
        pair <string, string> this_object = fileTrash.getObject (index);

        DIR * dir = opendir (set_path (getenv ("TRASHPATH"), this_object.first.c_str()).c_str());
        if (dir) 
        {
            remove_content_dir (set_path (getenv("TRASHPATH"), this_object.first.c_str()));
            closedir (dir);
        }
        else
            if (!is_setup_trash()) throw (ERNOTINSTALL);
                else 
                    if (errno == ENOENT) throw (ERFIND);

        if (remove (set_path (getenv ("TRASHPATH"), this_object.first.c_str()).c_str()) < 0)
        {
            if (!is_setup_trash())
                throw (ERNOTINSTALL);
            else 
                throw (ERFIND);
        }
        
        fileTrash.remove_value (this_object.first);
    }

    if (cmd == "clrall")
    {
        remove_content_dir (getenv ("TRASHPATH"));
        fileTrash.clear();
    }

    if (cmd == "recovall")
    {
        map <string, string> this_map = fileTrash.getData();
        map <string, string>::iterator it_map = this_map.begin();

        while (it_map != this_map.end())
        {
            if (rename (set_path (getenv ("TRASHPATH"), it_map->first.c_str()).c_str(), it_map->second.c_str()) < 0)
                throw (ERNOTINSTALL);
            it_map++;
        }

        return fileTrash.clear();
    }

    if (cmd == "help")
    {
        print_help();
    }
}

void print_help ()
{
    string help_manual = "trash <command> <argument>"
    "\n\ntrash remove <name file> - Adding a file or directory to the trash"
    "\n\ntrash list - Displaying the contents of the trash and the indexes of each item on the screen"
    "\n\ntrash recov <index> - Restores the file whose sequence number is specified in index"
    "\n\ntrash recovall - Restores the entire contents of the trash"
    "\n\ntrash clr <index> - Permanently removes an item from the trash whose index number is stored in index"
    "\n\ntrash clrall - Permanently deletes all contents of the trash"
    "\n\ntrash help - Displays the manual";

    cout << help_manual << endl;
}

void remove_content_dir (string path)
{
    DIR * path_dir = opendir (path.c_str());
    if (!path_dir) throw (ERNOTINSTALL);

    struct dirent * info_file = readdir (path_dir);

    while (info_file)
    {
        if (info_file->d_name[0] != '.')
        {
            if (info_file->d_type == DT_DIR)
                remove_content_dir (set_path (path.c_str(), info_file->d_name));

            if (remove (set_path (path.c_str(), info_file->d_name).c_str()) < 0) throw (ERNOTINSTALL);
        }

        info_file = readdir (path_dir);
    }
}

bool is_setup_trash()
{     
    char * s = getenv ("TRASHPATH");

    DIR* _dir = opendir (getenv ("TRASHPATH"));

    bool res = _dir;

    closedir (_dir);

    return res;
}

