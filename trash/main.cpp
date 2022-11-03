#include "Trash.h"

using namespace std;

void print_error (int er);


int main (int argc, const char * argv[])
{


    Trash trash;
    try
    {
        trash.start(argc, argv);
        trash.exec();
    } 
    catch(int er)
    {
        print_error (er);
    }
}

void print_error (int er)
{
    switch (er)
    {
        case ERNARGS:
        {
            cout << "Invalid number of arguments, type trash help to get information about the utility" << endl;
            exit (EXIT_FAILURE);
        }

        case ERINVALIDCMD:
        {
            cout << "Invalid command, type trash help to get information about the utility" << endl;
            exit (EXIT_FAILURE);
        }

        case ERNOTINSTALL:
        {
            cout << "You have not installed smart trash, type trash help" << endl;
            exit (EXIT_FAILURE);
        }

        case ERFIND:
        {
            cout << "The file or directory does not exist" << endl;
            exit (EXIT_FAILURE);
        }
    }
}