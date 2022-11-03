#include "File.h"

FileTrash::FileTrash() {
    setenv ("TRASHPATH", set_path (getenv ("HOME"), ".SmartTrash").c_str(), 1);
    string file_trash_path = set_path (getenv ("TRASHPATH"), ".list_trash");
    setenv ("LISTTRASH", file_trash_path.c_str(), 1);

    fd = open (file_trash_path.c_str(), O_RDWR | O_CREAT);

    int count;
    struct stat info_stat;

    fstat (fd, &info_stat);
    int size = (int) info_stat.st_size;

    char * buf = new char [size];
    char * pbuf = buf;

    while (size > 0)
    {
        count = read (fd, pbuf, size);

        size -= count;
        pbuf += size;
    }

    string data_file (buf);

    /////////////////////

    int row = 0, index_row = 0;

    while (row < data_file.length())
    {
        if (data_file[row + index_row] == '\n')
        {
            string this_row (data_file.begin() + row, data_file.begin() + row + index_row);

            string::iterator it_slash;
            string::iterator offset = this_row.begin();

            while (1)
            {
                it_slash = find (offset, this_row.end(), '\\');

                if (this_row[it_slash - this_row.begin()] == '\\' && this_row[it_slash - this_row.begin() + 1] != '/')
                    offset = it_slash + 1;
                else break;
            }

            string this_name (this_row.begin(), it_slash);
            string this_path (it_slash + 1, this_row.end());

            dataTrash[this_name] = this_path;

            row += index_row + 1;
            index_row = 0;
        }
        else
            index_row++;
    }
}

void FileTrash::close_file()
{
    close (fd);
}

string FileTrash::get_path_obj(string name)
{
    return dataTrash[name];
}

void FileTrash::add_value (string name, string path)
{
    fd = open (getenv ("LISTTRASH"), O_RDWR);
    if (fd < 0)
        throw (ERNOTINSTALL);

    lseek (fd, 0, SEEK_END);

    int count;
    string push_data = name + "\\" + path + "\n";

    const char * buf = push_data.c_str();

    int size = push_data.length();

    while (size > 0)
    {
        count = write (fd, buf, size);

        size -= count;
        buf += count;
    }

    dataTrash[name] = path;
}

void FileTrash::remove_value (string name)
{
    map <string, string>::iterator it_map = dataTrash.begin();

    fd = open (getenv ("LISTTRASH"), O_RDWR | O_TRUNC);
    if (fd < 1) throw (ERNOTINSTALL);

    int offset = 0;

    while (it_map != dataTrash.end())
    {

        if (it_map->first != name)
        {
            int count;
            string push_data = it_map->first + "\\" + it_map->second + "\n";

            const char * buf = push_data.c_str();

            int size = push_data.length();

            while (size > 0)
            {
                count = write (fd, buf, size);

                size -= count;
                buf += count;
            }
        }

        it_map++;
    }

    dataTrash.erase (name);
}

map <string, string>& FileTrash::getData()
{
    return dataTrash;
}

pair <string, string> FileTrash::getObject(int index)
{
    map <string, string>::iterator it_map = dataTrash.begin();
    int i = 0;

    while (it_map != dataTrash.end())
    {

        if (i == index)
        {
            return pair <string, string> (it_map->first, it_map->second);
        }

        i++;
        it_map++;
    }

    throw (ERFIND);
}

void FileTrash::clear()
{
    fd = open (getenv ("LISTTRASH"), O_RDWR | O_TRUNC);
    if (fd < 1)
        throw (ERNOTINSTALL);

    dataTrash.clear();
}

void FileTrash::print()
{
    int index = 0;
    map <string, string>::iterator it_map = dataTrash.begin();

    while (it_map != dataTrash.end())
    {
        cout << it_map->first << "\tindex = " << index << endl;
        it_map++;
        index++;
    }
}

string set_path (const char * root, const char * obj)
{
    string return_temp (root);
    return_temp += "/";
    return_temp.append (obj);

    return return_temp;
}
