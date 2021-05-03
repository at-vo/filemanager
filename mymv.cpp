#include <iostream>
#include </home/dvo/Documents/Project/CS3307/filemanager.h>

int main(int argc, char*argv[]){
    if (argc!=2){
        cerr << "two arguments needed" << endl;
    }
    filemanager fm = filemanager(argv[1]);
    int check; 
    if ((check=fm.rename(argv[2]))==0){
        cout << "move successful" << endl;
    }else{
        cerr << "error renaming file with error code: "<<check << endl;

    }
    
}