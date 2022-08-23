#ifndef __HREF__
#define __HREF__

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <locale.h>
#include <string.h>
#include <curl/curl.h>
#include "flink.h"
#include "shref.h"
#include "dir.h"

#define LENHTML 20000
#define MAXLINK 500
#define HTLEXT 5
#define TAGHREF "href"
#define FEXTEN 101
#define FNAME 101

void frdHtml(char*);
char* fexten(char*);

#endif
