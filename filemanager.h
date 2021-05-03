/**
 * Dat Vo
 * 250983323
 * Oct 3, 2019
 * header for file system
 * */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
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
#include <ctime>
class filemanager
{

public:
	filemanager(const char * name); 				/*filemanager object*/
	~filemanager();									/* destructor*/
	int dump(std::ostream &filestream);				/*dump member*/
	int rename(const char * newName);				/*rename member*/
	int remove();									/*remove member*/
	int compare(filemanager file);					/*compare member*/
    int expand();									/*expand member*/

	const char* getName();							/*returns name character pointer*/	
    mode_t getType();   							/*returns file type as mode_t*/
	int getOwnerID(); 								/*return integer representing user ID of owner */
	int getGroupID(); 								/* sets a new ID of group */
	passwd * getOwner();							/*returns a passwd pointer for owner*/
	group * getGroup();								/*returns a group pointer*/
	std::string getPermissions();					/*returns permission string*/
	int getSize();			 						/*returns total size as integer */
	int getBlocksize();			 					/* sets new blocksize for filesystem I/O */
	std::string getAccessTime();					/* return string of time of last access */
	std::string getModTime(); 						/* return string of time of last modification */
	std::string getStatusTime(); 					/*return string of time of last status change */
	int getErrsv();									/* return error save integer */
    std::vector <filemanager*> getChildren();		/* returns vector of filemanager objects*/

	void setOwnerID(int newID); 					/*sets a new ownerID*/
	void setGroupID(int newID); 					/*return integer representing user ID of group */
	void setPermissions(std::string newPermission);	/*sets a new permission string*/
	void setSize(int newSize);						/*sets new size*/
	void setBlocksize(int newSize);					/*sets new block size*/
	void setErrsv(int err);							/* set new error save value */

	char printType();								/*returns the character symbol for type*/
	std::string typeString();						/*returns a string represenation for type*/
	std::string removeN(char * c);						/*removes \n from a ctime return char pointer*/



private:
	struct stat buf;														/* stat object */
	const char * fmName;													/* name of file*/
	mode_t fileType;   														/* file type and mode */
	int ownerID; 															/* user ID of owner */
	struct passwd * owner;													/* owner structure*/
	int groupID; 															/* group ID of owner */
	struct group * grp;														/* group structure*/
	std::string permissions;												/* permissions*/
	int fileSize;			 												/* total file size */
	int blocksize;			 												/* blocksize for filesystem I/O */
	char* accessTime; 														/* time of last access */
	char* modTime; 															/* time of last modification */
	char* statusTime; 														/* time of last status change */
	int errsv;																/* record of last error*/
    std::vector <filemanager*> children;									/* vector of filemanager objects*/
	std::string unmaskType();												/* helper function to get string of type*/
	std::string unmaskPermision(mode_t mode, std::string permission);		/* helper function to get string of permissions*/

 };
#endif