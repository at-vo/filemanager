/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * used to make a copy of a file from a source to a destination named as parameters to the command
 * */
#include "filemanager.h"
using namespace std;



int main(int argc, char*argv[]){
    if(argc<3){
        cerr << "two arguments needed" << endl;
    }else{
        filemanager* fm = new filemanager(argv[1]); // file manager for main argument
        int check; 
        ofstream file;      //outstream for second file
        file.open(argv[2]);     //open second file
        if (!file.is_open())
        {   //if error
            cerr << "error opening file" << endl;
            fm->setErrsv(errno);
        }else{
            if ((check=fm->dump(file))==0)  //try dump
            {   //if succeed
                cout << "copy successful" << endl;
            }else
            {   //if fail
                fm->setErrsv(ENOTSUP);
                cerr << "error dumping file with error code: "<< check << endl;
            }
        }
        delete fm;  //free
    }

}