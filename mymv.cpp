/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * used to move and rename files around
 * */
#include "filemanager.h"
using namespace std;


int main(int argc, char*argv[]){
    if (argc!=2)
    {   //check args
        cerr << "two arguments needed" << endl;
    }
    filemanager* fm = new filemanager(argv[1]); //filemanager for file
    int check; 
    if ((check=fm->rename(argv[2]))==0) //try rename
    {   //if succeed
        cout << "move successful" << endl;
    }else
    {   // if fail
        fm->setErrsv(errno);
        cerr << "error renaming file with error code: "<<check << endl;

    }
    delete fm;  //free
    
}