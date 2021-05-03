#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <vector>
#include <fstream>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <dirent.h>
#include <string.h>
using namespace std;

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
class filemanager
{

public:
	filemanager(const char * name);
	int dump(ofstream &filestream);
	int rename(const char * newName);
	int remove();
	int compare(const char * file);
    int expand();
    void printChildren(bool flag);

	const char* getName();
	
    string getType();   /* file type and mode */

    void setOwnerID(); 
	int getOwnerID(); /* user ID of owner */

	void setGroupID(); 
	int getGroupID(); /* user ID of group */

	void setPermissions();
	int getPermissions();
	
	void setSize();
	int getSize();			 /* total size, in bytes */

	int setBlocksize();
	int getBlocksize();			 /* blocksize for filesystem I/O */

	char* accessTime; /* time of last access */
	char* timespec modTime; /* time of last modification */
	char* timespec statusTime; /* time of last status change */

	void setErrsv();
	int getErrsv();

    vector <filemanager> getChildren();

	~filemanager();

private:
	struct stat buf;
	const char * fmName;
	mode_t type;   /* file type and mode */
	int ownerID; /* user ID of owner */
	struct passwd * owner;
	int groupID; /* group ID of owner */
	struct group * group;
	mode_t permissions;
	int size;			 /* total size, in bytes */
	int blocksize;			 /* blocksize for filesystem I/O */
	string accessTime; /* time of last access */
	string modTime; /* time of last modification */
	string statusTime; /* time of last status change */
	int errsv;
    vector <struct stat> children;
	string unmaskType();
	char* unmaskPermision(mode_t mode);

 };
#endif