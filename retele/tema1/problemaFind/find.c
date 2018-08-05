#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


void find(char directory[256], char pattern[30]);

_Bool isDotsDirectory(char entryName[256]);
_Bool isDirectory(char entryName[256]);
_Bool isExpectedFile(char entryName[256], char pattern[30]);

int main(int argc, char* argv[])
{

  char directory[256];
  char pattern[30];

  strcpy(directory,argv[2]);
  strcpy(pattern,argv[1]);
  
  //printf("Initialise find.\n");
  find(directory,pattern);
  return 0;
}

void find(char directory[256],char pattern[30]){

  DIR* dir;
  struct dirent* directoryEntry;
  char newPath[1024];

  
  //printf("Opening directory: \n");
  //printf(directory);
  
  dir = opendir(directory);

    if (!dir)
    exit(1);

    //printf("\nDirectory opened!\n");
    
    while ( (directoryEntry = readdir(dir)) != NULL) {
    errno = 0;

    /*printf("Am ajuns aici 1.\n");
    printf(directoryEntry -> d_name);
    printf("\n");*/
    
    if (errno){
	closedir(dir);
	exit(1);
      }
    
    if ( isDotsDirectory(directoryEntry -> d_name) )
	continue;

    /*printf("Am ajuns aici 2.\n");
    printf(directoryEntry -> d_name);
    printf("\n");*/

    strcpy(newPath, directory);
    strcat(newPath, "/");
    strcat(newPath, directoryEntry -> d_name);
    //strcpy( newPath, createNewPath(directory, directoryEntry -> d_name) );

    /*printf("Am ajuns aici 4.\n");
      printf(newPath);*/
      
    if ( isDirectory(directoryEntry-> d_name) )
	  find(newPath,pattern);
    if ( isExpectedFile(directoryEntry -> d_name, pattern) )
      {
	printf(newPath);
	printf("\n");
      }
	
  }//while

  closedir(dir);
}

_Bool isDotsDirectory(char entryName[256])
{
  return strcmp(entryName, ".") == 0 || strcmp(entryName, "..") == 0;
}


_Bool isDirectory(char entryName[256])
{
  return strstr(entryName,".") == NULL;
}

_Bool isExpectedFile(char entryName[256], char pattern[256])
{
  return strstr( entryName, pattern) !=NULL;
}
