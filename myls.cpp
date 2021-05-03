/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * this will list the contents of the directory and for other types of files
 * */
#include "filemanager.h"
using namespace std;
int main(int argc, char *argv[])
{
    bool ifL = false; // sets flag for -l. default to false
    string in; // keep track of current argument
    if (argc > 3)
    { // check for correct arguments
        cerr << "too many arguments" << endl;
    }
    else
    {
        for (int i = 1; i < argc; i++)
            { // check each argument
                string currArg = argv[i]; // get current argument
                if (currArg.compare("-l") == 0 || currArg.compare("-L")==0)
                {               // if equals -l
                    ifL = true; // then set flag to true
                }
                else
                {
                    in = currArg; //assign argument
                }
            }
       if (argc==1)
        {   // if only ./myls called
            filemanager* fm = new filemanager(".");     //make new filemanager
            fm->expand(); // populate children
            vector<filemanager*> path = fm->getChildren();      //get the children
            for (int i = 0; i < path.size(); ++i)   
            {   //check each child
                cout << path[i]->getName() << endl;     //print only child name
            }
            delete fm; //free file manager object
        }
        else if(argc==2)
        {   // for two arguments
            if (ifL == true)
            { // then implement -l
                filemanager* fm = new filemanager(".");
                fm->expand();
                vector<filemanager*> path = fm->getChildren();
                for (int i = 0; i < path.size(); ++i)
                {   // print out each child's information
                    cout << path[i]->printType()<< path[i]->getPermissions()
                             << " "<<path[i]->getBlocksize() << " "<<path[i]->getGroup()->gr_name
                             << " "<<path[i]->getOwner()->pw_name << " "<<path[i]->getSize()
                             << " "<<path[i]->getAccessTime() << " "<<path[i]->getName() << endl;
                }
                delete fm;
            }
            else
            {   // if theres no -l
                filemanager*fm = new filemanager(in.c_str());
                if (S_ISREG(fm->getType())) 
                {   //if reg file
                    cout << fm->getName() << endl;
                }
                else if (S_ISDIR(fm->getType()))
                {   //if directory
                    fm->expand();
                    vector<filemanager*> path = fm->getChildren();
                    for (int i = 0; i < path.size(); ++i)
                    {
                        cout << path[i]->getName() << endl;
                    }
                }
                else
                {
                    fm->setErrsv(ENOTSUP);
                    cerr << "invalid file type error code" << fm->getErrsv() << endl;
                }
                delete fm;
            }
        }
        else if(argc==3)
        {   // if 3 arguments
            filemanager* fm = new filemanager(in.c_str());
            if (S_ISREG(fm->getType()))
            { //if reg file
                cout << fm->printType() <<fm->getPermissions()
                            << " "<<fm->getBlocksize() << " "<<fm->getGroup()->gr_name
                            << " "<<fm->getOwner()->pw_name << " "<<fm->getSize()
                            << " "<<fm->getAccessTime() << " "<<fm->getName() << endl;
            }
            else if (S_ISDIR(fm->getType()))
            { // if directory
                fm->expand();
                vector<filemanager*> path = fm->getChildren();
                for (int i = 0; i < path.size(); ++i)
                {
                    cout << path[i]->printType() << path[i]->getPermissions()
                            << " "<<path[i]->getBlocksize() << " "<<path[i]->getGroup()->gr_name
                            << " "<<path[i]->getOwner()->pw_name << " "<<path[i]->getSize()
                            << " "<<path[i]->getAccessTime() << " "<<path[i]->getName() << endl;
                }
            }
            delete fm;
            
        }
    }
}

    
