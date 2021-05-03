#include <iostream>
#include </home/dvo/Documents/Project/CS3307/filemanager.h>
#include <fstream>

int main(int argc, char*argv[]){
    if(argc!=2){
        cerr << "two arguments needed" << endl;
    }else{
        filemanager fm = filemanager(argv[1]);
        int check; 
        ofstream file;
        file.open(argv[2]);
        if (!file.is_open()){
            cerr << "error opening file" << endl;
        }else{
            if ((check=fm.dump(file))==0){
                cout << "copy successful" << endl;
            }else{
                cerr << "error dumping file with error code: "<< check << endl;
            }
        }
    }

}