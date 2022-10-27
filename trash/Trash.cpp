#include "Trash.h"

int Trash::start (int narg, const char ** args)
{
    if (narg < 2 || narg > 3)
    {
        cout << "Invalid use trash, write \"trash help\"" << endl;
        return -1;
    }

    string start_cmd (args[1]);
    string start_arg ((narg == 3) ? args[2] : "");

    for (int i = 0; i < sizeof (commands) / STRING_SIZE; i++)
    {
        if (start_cmd == commands[i])
        {
            cmd = start_cmd;
            cmd_arg = start_arg;
            return 0;
        }
    }

    return -1;
}

Trash::Trash()
{
    string trash_path = set_path (getenv ("HOME"), ".SmartTrash");
    setenv ("TRASHPATH", trash_path.c_str(), 1);
}

int Trash::exec()
{
    if (cmd == "remove")
    {
        rename (set_path (getenv ("PWD"), cmd_arg.c_str()).c_str(), set_path (getenv ("TRASHPATH"), cmd_arg.c_str()).c_str());
        fileTrash.add_value (cmd_arg, set_path (getenv ("PWD"), cmd_arg.c_str()));

        return 0;
    }

    if (cmd == "list")
    {
        fileTrash.print();
        return 0;
    }

    if (cmd == "recov")
    {
        int index = atoi (cmd_arg.c_str());

        pair <string, string> this_object = fileTrash.getObject (index);
        
        rename (set_path (getenv ("TRASHPATH"), this_object.first.c_str()).c_str(), this_object.second.c_str());
        fileTrash.remove_value (this_object.first);

        return 0;
    }

    if (cmd == "clr")
    {
        int index = atoi (cmd_arg.c_str());
        pair <string, string> this_object = fileTrash.getObject (index);

        fileTrash.remove_value (this_object.first);
        remove (set_path (getenv ("TRASHPATH"), this_object.first.c_str()).c_str());

        return 0;
    }

    if (cmd == "clrall")
    {
        fileTrash.clear();

        remove_content_dir (getenv ("TRASHPATH"));

        return 0;
    }

    if (cmd == "recovall")
    {
        map <string, string> this_map = fileTrash.getData();
        map <string, string>::iterator it_map = this_map.begin();

        while (it_map != this_map.end())
        {
            rename (set_path (getenv ("TRASHPATH"), it_map->first.c_str()).c_str(), it_map->second.c_str());
            it_map++;
        }

        fileTrash.clear();

        return 0;
    }

    if (cmd == "help")
    {
        print_help();
        return 0;
    }

    return -1;
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

    struct dirent * info_file = readdir (path_dir);

    while (info_file)
    {
        if (info_file->d_name[0] != '.')
        {
            if (info_file->d_type == DT_DIR)
                remove_content_dir (set_path (path.c_str(), info_file->d_name));

            remove (set_path (path.c_str(), info_file->d_name).c_str());
        }

        info_file = readdir (path_dir);
    }
}

