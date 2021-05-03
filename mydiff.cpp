/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * compares two files named as parameters to this command with one another and reports if they are the same or different
 * */
#include "filemanager.h"
using namespace std;

int main(int argc, char*argv[]){
    if(argc<3){ // check if enough args
        cerr << "two arguments needed" << endl;
    }else{
        int check;  //used to check if its the same based on compare
        filemanager* file1 = new filemanager(argv[1]);      //file object for each argument
        filemanager* file2 = new filemanager(argv[2]);
        if((check=file1->compare(*file2))==-1)
        {   //if compare not same
            cerr<<"files not the same"<<endl;
 
        }else if(check==0)
        {   //if same
            cout<< "files are the same!"<<endl;
        }
        delete file1, file2;    //free

    }

}