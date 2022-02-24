#ifndef __HREF__
#define __HREF__

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <locale.h>
#include <string.h>
#include <curl/curl.h>
#include "flink.h"

#define LENHTML 20000
#define MAXLINK 500
#define HTLEXT 5
#define TAGHREF "href"
#define DOWNDIR "Download"
#define FEXTEN 101
#define FNAME 101


void downloadLinks(data_links);
int strHrefIndex(char*, char*);
void rdHtmlFile(char*);
char* fexten(char*);

#endif
