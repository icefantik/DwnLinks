#ifndef __DIR__
#define __DIR__

#include <string.h>
#include <sys/dir.h>
#include <dirent.h>
//#include <direct.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

#define DIRLINKS "Links"
#define MAXDIR 500
#define CWDDIR 255
#define MAXPATH 901

void selcFile(char*, char*);

#endif
