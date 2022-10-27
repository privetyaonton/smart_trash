#include "Trash.h"

using namespace std;

int main (int argc, const char * argv[])
{
    Trash trash;
    trash.start(argc, argv);
    trash.exec();
}