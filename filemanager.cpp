#include "filemanager.h"
using namespace std;

/**
 * constructor
 * */
filemanager::filemanager(const char * name)
{
	fmName = name;
	if (-1==stat(fmName, &buf)){
		errsv = errno;
		cerr << "error calling stat() on file with error code:" << errsv << endl;
	}else{
		stat(fmName, &buf);
		fileType = buf.st_mode;
		size = buf.st_size;
		ownerID = buf.st_uid;
		owner = getpwuid(buf.st_uid);
		groupID = buf.st_gid;
		group = getgrgid(buf.st_gid);
		permissions = unmaskPermision(buf.st_mode); // get last 9 digits of st_mode
		size = buf.st_size;
		blocksize = buf.st_blksize;
		accessTime = ctime(buf.st_atim);
		modTime = ctime(buf.st_mtim);
		statusTime = ctime(buf.st_ctim);
		errsv = 0;
		cout << "filemanager created!" << endl;
	}
}

/**
 * dump member
 * */
int filemanager::dump(ofstream &filestream)
{
	if (!S_ISREG(type))
	{
	errsv = ENOTSUP;
	//cerr << "error renaming file with error code: "<<errsv << endl;
	return errsv;
	}else{
		ifstream fileIn;
		fileIn.open(fmName);
		if (!fileIn.is_open()){
			errsv = errno;
			//cerr << "error opening file with error code: " << errsv <<endl;
			return errsv;
		}else{
			char line [blocksize];
			fileIn.read(line,blocksize);
			while(!fileIn.eof()){
				filestream<<line;
				fileIn.read(line,blocksize);
			}
			filestream.close();
			fileIn.close();
		}
	}
	return 0;
}

/**
 * rename member
 * */
int filemanager::rename(const char * newName)
{
	if (-1==std::rename(fmName, newName)){
		errsv = errno;
		return errsv;
	}
		std::rename(fmName, newName);
	return 0;
}

/**
 * remove member
 * */
int filemanager::remove()
{
	if (-1==unlink(fmName)){
		errsv = errno;
		//cerr << "error unlinking file with error code: " << errsv << endl; 
		return errsv;
	}
	unlink(fmName);
	return 0;
}

/**
 * compare member
 * */
int filemanager::compare(filemanager file)
{
	ifstream mainFile, cmpFile;
	mainFile.open(fmName);
	cmpFile.open(file.getName);
	if (!mainFile.is_open()){
		errsv = errno;
		//cerr << "error opening file with error code: " << errsv <<endl;
		return errno;
	}else{
		char mainBlock [blocksize];
		char cmpBlock [blocksize];
		do{
			mainFile.read(mainBlock,blocksize);
			cmpFile.read(cmpBlock,blocksize);
			if(0!=memcmp(mainBlock, cmpBlock, size))
			{
				return -1;
			}
		}while(!mainFile.eof());
		cmpFile.close();
		mainFile.close();
	}

	return 0;

}

/**
 * expand method
 * */
int filemanager::expand()
{
	if (!S_IFDIR(type))
	{
		errsv = ENOTSUP;
		return errsv;
	}else{
		DIR * dirPt=opendir(fmName);
		if (dirPt == NULL)
		{
			errsv = errno;
			return errno;
		}else{
			struct dirent * read;
			while((read = readdir(dirPt))!=NULL){
				filemanager cpy = filemanager(read->d_name);
				children.push_back(cpy);
			}
		}
		closedir(dirPt);
	}
	return 0;
}

char* filemanager::unmaskPermision(mode_t mode){
	    
	/* mode_t rwx = buf.st_mode;
	if(rwx & S_IRUSR) { permission.push_back('r'); }else{ permission.push_back('-');}
	if(rwx & S_IWUSR) { permission.push_back('w'); }else{ permission.push_back('-');}
	if(rwx & S_IXUSR) { permission.push_back('x'); }else{ permission.push_back('-');}
	if(rwx & S_IRGRP) { permission.push_back('r'); }else{ permission.push_back('-');}
	if(rwx & S_IWGRP) { permission.push_back('w'); }else{ permission.push_back('-');}
	if(rwx & S_IXGRP) { permission.push_back('x'); }else{ permission.push_back('-');}
	if(rwx & S_IROTH) { permission.push_back('r'); }else{ permission.push_back('-');}
	if(rwx & S_IWOTH) { permission.push_back('w'); }else{ permission.push_back('-');}
	if(rwx & S_IXOTH) { permission.push_back('x'); }else{ permission.push_back('-');} */

	strmode(mode,)
    
}

/*********************************************************************************
 * 
 * Getters And Setters
 * 
 * *******************************************************************************/

	const char* filemanager::getName(){
		return fmName;
	}
	
    void filemanager::setType(string newType){
		type = newType;
	}
    string getType(){
		return type;
	} 

    void filemanager::setOwnerID(int newID){
		ownerID = newID;
	}
	int filemanager::getOwnerID(){
		return ownerID;
	} 

	void filemanager::setGroupID(int newID){
		groupID = newID;
	}

	int filemanager::getGroupID(){
		return groupID;
	}

	void filemanager::setPermissions(string newPermission){
		permissions = newPermission;
	}
	string filemanager::getPermissions(){
		return permissions;
	}
	
	void filemanager::setSize(int newSize){
		fileSize = newSize;
	}
	int filemanager::getSize(){
		return size;
	}		 

	int filemanager::setBlocksize(int newSize){
		blocksize = newSize;
	}
	int filemanager::getBlocksize(){
		return blocksize;
	}		 
	void filemanager::setErrsv(int err){
		errsv = err;
	}
	int filemanager::getErrsv(){
		return errsv;
	}

	string getAccessTime(){
		return accessTime;
	}
	
	vector<filemanager> filemanager::getChildren(){
		return children;
	}

/**
 * Destructor
 * */
filemanager::~filemanager()
{	
	children.clear();
	cout<< "filemanager destroyed" << endl;
}