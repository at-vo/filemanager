/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * display the contents of all of the files given as parameters to the command to the terminal
 * */
#include "filemanager.h"
using namespace std;


int main(int argc, char*argv[]){
    if(argc<2)
    {   //check args
        cerr << "at least one argument needed" << endl;
    }else{
        for (int i = 1; i < argc; ++i)
        {
            int check;
            filemanager* fm = new filemanager(argv[i]); 
            if ((check=fm->dump(cout))!=0)  //dump into terminal
            {
                fm->setErrsv(ENOTSUP);      //set error to enotsup
                cerr << "error dumping file with error code: "<< check << endl;
            }
            delete fm;  //free
        }
    }

}