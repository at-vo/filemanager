/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * source code for filesystem object that is used for handling files
 * */

#include "filemanager.h"
using namespace std;

/**
 * constructor
 * */
filemanager::filemanager(const char * name)
{
	fmName = name;
	if (-1==stat(fmName, &buf))		// perform stat call and assignment
	{	//if fails
		errsv = ENOTSUP;
		cerr << "error calling stat() on file: "<< fmName<<" with error code:" << errsv << endl;
	}else{
		stat(fmName, &buf);		// call stat and assign to buf
		fileType = buf.st_mode;
		fileSize = buf.st_size;
		ownerID = buf.st_uid;
		owner = getpwuid(buf.st_uid);
		groupID = buf.st_gid;
		grp = getgrgid(buf.st_gid);
		permissions = unmaskPermision(buf.st_mode,permissions); // get last 9 digits of st_mode
		fileSize = buf.st_size;
		blocksize = buf.st_blksize;
		accessTime = ctime(&buf.st_atim.tv_sec);		// get time and call ctime on it for proper date
		modTime = ctime(&buf.st_mtim.tv_sec);
		statusTime = ctime(&buf.st_ctim.tv_sec);
		errsv = 0;	//errsv =0 upon successful handle of method
		//cout << "filemanager created!" << endl;
	}
}

/**
 * Destructor
 * */
filemanager::~filemanager()
{	
	children.clear();		//removes all references to children
	//cout<< "filemanager destroyed" << endl;
}

/**
 * dump member
 * */
int filemanager::dump(ostream &filestream)
{
	if (!S_ISREG(fileType))
	{	//if not a regular file type
	errsv = ENOTSUP;
	return errsv;
	}else{
		ifstream fileIn;		//filestream in
		fileIn.open(fmName);	
		if (!fileIn.is_open()){
			errsv = errno;
			return errsv;
		}else{
			char line[blocksize];		//char buffer of size blocksize
			do{
				fileIn.read(line,blocksize);	//read each block
				filestream<<line;	//throw read line into outstream
			}while(!fileIn.eof());
			fileIn.close();
			errsv=0;
		}
	}
	errsv=0;
	return 0;
}

/**
 * rename member
 * */
int filemanager::rename(const char * newName)
{
	if (-1==std::rename(fmName, newName))	//renames named file
	{	// if fail
		errsv = errno;
		return errsv;
	}
		std::rename(fmName, newName);
	errsv=0;
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
	if((unlink(fmName))==-1)//unlinks named file
	{	//if fail
		errsv = errno;
		return errsv;
	}
	//otherwise
	errsv=0;
	return 0;
}

/**
 * compare member
 * */
int filemanager::compare(filemanager file)
{
	ifstream mainFile, cmpFile;
	mainFile.open(fmName);
	cmpFile.open(file.getName());
	if (!mainFile.is_open()){
		errsv = errno;
		//cerr << "error opening file with error code: " << errsv <<endl;
		return errno;
	}else{
		char mainBlock [blocksize];		//create char buffer blocks
		char cmpBlock [blocksize];
		do{
			mainFile.read(mainBlock,blocksize);		//read in from both files into the char blocks
			cmpFile.read(cmpBlock,blocksize);
			if(0!=memcmp(mainBlock, cmpBlock, fileSize))	//check if the blocks are the same
			{	//if not
				return -1;	
			}
		}while(!mainFile.eof());	//condition for end of file
		cmpFile.close();		//close both files
		mainFile.close();
	}
	errsv=0;
	return 0;

}

/**
 * expand method
 * */
int filemanager::expand()
{
	if (!S_ISDIR(fileType))
	{	//error handle
		errsv = ENOTSUP;
		return errsv;
	}else{
		DIR * dirPt=opendir(fmName);	//set directory pointer to the named directory
		if (dirPt == NULL)
		{	//error check for null pointer
			errsv = errno;
			return errno;
		}else{
			struct dirent * read;	// dirent structure pointer 
			while((read = readdir(dirPt))!=NULL){
				filemanager* cpy = new filemanager(read->d_name);	//assign the copy of the file object to a pointer
				children.push_back(cpy);		// add copy to vector
			}
		}
		closedir(dirPt);
	}
	errsv=0;
	return 0;
}




/*********************************************************************************
 * 
 * Getters And Setters
 * 		types defined generally in header file
 * 
 * *******************************************************************************/

	const char* filemanager::getName(){
		return fmName;
	}
    mode_t filemanager::getType(){
		return fileType;
	}
	int filemanager::getOwnerID(){
		return ownerID;
	} 

	int filemanager::getGroupID(){
		return groupID;
	}
	passwd * filemanager::getOwner(){
		return owner;
	}
	group * filemanager::getGroup(){
		return grp;
	}
	string filemanager::getPermissions(){
		return permissions;
	}
	int filemanager::getSize(){
		return fileSize;
	}		 
	int filemanager::getBlocksize(){
		return blocksize;
	}		 
	int filemanager::getErrsv(){
		return errsv;
	}
	string filemanager::getAccessTime(){
		return removeN(accessTime);
	}
	string filemanager::getModTime(){
		return removeN(modTime);

	}
	string filemanager::getStatusTime(){
		return removeN(statusTime);

	}
	vector<filemanager*> filemanager::getChildren(){
		return children;
	}


	void filemanager::setSize(int newSize){
		filemanager::fileSize = newSize;
	}
	void filemanager::setBlocksize(int newSize){
		blocksize = newSize;
	}
	void filemanager::setOwnerID(int newID){
		ownerID = newID;
	}
		void filemanager::setGroupID(int newID){
		groupID = newID;
	}
		void filemanager::setPermissions(string newPermission){
		permissions = newPermission;
	}
		void filemanager::setErrsv(int err){
		errsv = err;
	}
/*********************************************************************************
 * Helper methods
 * *******************************************************************************/

/**
 * unmask permission 
 * helper function that unmasks mode and adds to end of string
 * */
string filemanager::unmaskPermision(mode_t mode, string perm){
	    
	if(mode & S_IRUSR) { perm.push_back('r'); }else{ perm.push_back('-');}
	if(mode & S_IWUSR) { perm.push_back('w'); }else{ perm.push_back('-');}
	if(mode & S_IXUSR) { perm.push_back('x'); }else{ perm.push_back('-');}
	if(mode & S_IRGRP) { perm.push_back('r'); }else{ perm.push_back('-');}
	if(mode & S_IWGRP) { perm.push_back('w'); }else{ perm.push_back('-');}
	if(mode & S_IXGRP) { perm.push_back('x'); }else{ perm.push_back('-');}
	if(mode & S_IROTH) { perm.push_back('r'); }else{ perm.push_back('-');}
	if(mode & S_IWOTH) { perm.push_back('w'); }else{ perm.push_back('-');}
	if(mode & S_IXOTH) { perm.push_back('x'); }else{ perm.push_back('-');} 
    return perm;
}

/**
 * unmask permission 
 * helper function that removes the 
 * \n character at the end of ctime for times
 * */
string filemanager::removeN(char * c){
	string s(c);
	s.resize(s.length()-1);
	return s;
}

char filemanager::printType(){
		char c;
		// sets each type to its respective character representation
		if (S_ISREG(fileType))
			{c = '-';}
		else if (S_ISBLK(fileType))
			{c = 'b';}
		else if (S_ISCHR(fileType))
			{c = 'c';}
		else if (S_ISFIFO(fileType))
			{c = 'p';}
		else if (S_ISDIR(fileType))
			{c = 'd';}
		else if (S_ISLNK(fileType))
			{c = 'l';}
		else if (S_ISSOCK(fileType))
			{c = 's';}
		else{c = '?';}
		return c;
	}
	
	string filemanager::typeString()
	{	// sets each type to its respective string representation
		string c;
		if (S_ISREG(fileType))
			{c = "regular file";}
		else if (S_ISDIR(fileType))
			{c = "directory";}
		else if (S_ISBLK(fileType))
			{c = "block device";}
		else if (S_ISCHR(fileType))
			{c = "character device";}
		else if (S_ISFIFO(fileType))
			{c = "pipe";}
		else if (S_ISLNK(fileType))
			{c = "symlink";}
		else if (S_ISSOCK(fileType))
			{c = "socket";}
		else
		{
			c = "unknown?";
		}
		return c;
	}