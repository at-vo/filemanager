/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * removes the given files listed as parameters to this command
 * */
#include "filemanager.h"
using namespace std;

int main(int argc, char*argv[]){
    if(argc<2)
    {   //args check
        cerr << "at least one argument needed" << endl;
    }else{
        for (int i = 1; i < argc; i++)
        {
            filemanager* fm = new filemanager(argv[i]);    //filemanager object for argument
            fm->remove();   //unlinks
            delete fm;  //free
        }
    }

}