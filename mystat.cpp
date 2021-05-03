/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * outputs all of the information on the file named as a parameter to this command
 * */
#include "filemanager.h"
using namespace std;


int main(int argc, char*argv[]){
    if(argc>2)
    {   //arg check
        cerr << "too many arguments" << endl;
    }else{
        filemanager* fm = new filemanager(argv[1]);
        //  just print statements
        cout << "file:" << fm->getName()<<endl;
        cout<<"size: "<< fm->getSize()<< "\tblocks: "<<fm->getBlocksize()<< "\ttype:"<<fm->typeString()<<endl;
        cout<<"Uid:(" << fm->getOwnerID()<<"/\t"<<fm->getOwner()->pw_name<<")\t"
            <<"Gid:("<< fm->getGroupID()<<"/\t"<<fm->getGroup()->gr_name<<")"<<endl;
		cout<<"Permissions:"<<fm->getPermissions()<<endl;
        cout<<"Access Date:"<<fm->getAccessTime()<<endl;
        cout<<"Modify Date:"<<fm->getModTime()<<endl;
        cout<<"Status Date:"<<fm->getStatusTime()<<endl;
    }

}