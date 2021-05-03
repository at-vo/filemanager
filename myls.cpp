#include "filemanager.h"
int main(int argc, char *argv[])
{
    bool ifL = false; // sets flag for -l. default to false
    char *in = NULL;
    if (argc > 3)
    { // check for correct arguments
        cerr << "too many arguments" << endl;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            string currArg = argv[i]; // get current argument
            if (currArg.compare("-l") == 0 || currarg.compare("-L"))
            {               // if equals -l
                ifL = true; // then set flag to true
            }
            else
            {
                in = &argv[i];
            }
        }
        switch (argc)
        {
        case (1):
        {
            filemanager fm = new filemanager(".");
            fm.expand();
            vector<filemanager> path = fm.getChildren();
            for (int i = 0; i < path.size(); ++i)
            {
                cout << path[i].getName() << endl;
            }
        }
        break;
        case (2):
        {
            if (ifL == true)
            { // then implement -l
                filemanager fm = new filemanager(".");
                fm.expand();
                vector<filemanager> path = fm.getChildren();
                for (int i = 0; i < path.size(); ++i)
                {
                    cout << path[i].getType() << path[i].getPermissions()
                         << path[i].getBlocksize() << path[i].getGroupID()
                         << path[i].getOwnerID() << path[i].getSize()
                         << path[i].getAccessTime() << path[i].getName() << endl;
                }
            }
            else
            {
                filemanager fm = new filemanager(in);
                if (S_ISREG(fm.getType())) //if reg file
                {
                    cout << fm.getName() << endl;
                }
                else if (S_ISDIR(fm.getType()))
                {
                    fm.expand();
                    vector<filemanager> path = fm.getChildren();
                    for (int i = 0; i < path.size(); ++i)
                    {
                        cout << path[i].getName() << endl;
                    }
                }
                else
                {
                    fm.setErrsv = ENOTSUP;
                    cerr << "invalid file type error code" << fm.getErrsv() << endl;
                }
            }
        }
        break;
        case (3):
        {
            if (ifL == true)
            { // then implement -l
                filemanager fm = filemanager(in);
                if (S_ISREG(fm.getType()))
                { //if reg file
                    cout << path[i].getType() << path[i].getPermissions()
                         << path[i].getBlocksize() << path[i].getGroupID()
                         << path[i].getOwnerID() << path[i].getSize()
                         << path[i].getAccessTime() << path[i].getName() << endl;
                }
                else if (S_ISDIR(fm.getType()))
                { // if directory
                    fm.expand();
                    vector<filemanager> path = fm.getChildren();
                    for (int i = 0; i < path.size(); ++i)
                    {
                        cout << path[i].getType() << path[i].getPermissions()
                             << path[i].getBlocksize() << path[i].getGroupID()
                             << path[i].getOwnerID() << path[i].getSize()
                             << path[i].getAccessTime() << path[i].getName() << endl;
                    }
                }
            }
        }
        break;
        }
    }