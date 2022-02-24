#include "href.h"

void reverse(char*, int);
char* getNameFileLink(char*, int);
char* getExtenFromLink(char*, int);
char *subStr(char*, int, int, char*);
void dwlLink(char *path, char *url);
void rplcSlshLnk(char *name_file);

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void downloadLinks(data_links dt_links)
{
	char path[5000];
	char *exten_file, *name_file; 
	for (int i = 0, len_url; i < dt_links.len_links; ++i) {
		len_url = strlen(dt_links.links[i]);
		exten_file = getExtenFromLink(dt_links.links[i], len_url);	
		name_file = getNameFileLink(dt_links.links[i], len_url);
		rplcSlshLnk(name_file);

		sprintf(path, "%s/%s.%s", DOWNDIR, name_file, exten_file);				 dwlLink(path, dt_links.links[i]);		
	}
}

void dwlLink(char *path, char *url)
{
	CURL *curl;
        CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		FILE *fp = fopen(path,"wb");
        	curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        	res = curl_easy_perform(curl);
        	if (fp == NULL) {
        		printf("Couldn't open %s: Segmentation faild file not create/open.\n", path);
        	} else {
        		fclose(fp);
        	}
		curl_easy_cleanup(curl);
	}
}

void rplcSlshLnk(char *name_file)
{
	for (int index_name = 0; name_file[index_name] != '\0'; ++index_name) {
		if (name_file[index_name] == '/') {
			name_file[index_name] = '\\';
		}	
	}
}

char *getNameFileLink(char* url, int len_url)
{
	int index_slesh = strchr(url, '/') - url + 1;
	char dest[5001];
	char *tmp = subStr(url, index_slesh, len_url, dest);	
	return tmp;
}

char *subStr(char* input, int offset, int len, char* dest)
{
	/*
	int input_len = strlen(input);
	if (offset + len > input_len) {
		return NULL;
	}
	*/
	strncpy(dest, input + offset, len);
	return dest;
}

void reverse(char* str, int len)
{
	char tmp;
	for (int start_index = 0, end_index = len - 1; start_index  < end_index; ++start_index, --end_index) {
		tmp = str[start_index];
		str[start_index] = str[end_index];
		str[end_index] = tmp;
	}
}

char* getExtenFromLink(char* url, int len_url)
{
	int index_exten = 0;
	char* file_exten = (char*)malloc(sizeof(char) * FEXTEN * 2);
	for (int index_url = len_url - 1; url[index_url] != '.' && index_url >= 0; --index_url) 
	{
		if (url[index_url] == '/') {
			free(file_exten);
			return "html";	
		}
		file_exten[index_exten++] = url[index_url];
	}
	file_exten[index_exten] = '\0';
	reverse(file_exten, index_exten);
	//printf("%s\n", file_exten);
	return file_exten;
}

int strHrefIndex(char* strFromHTML, char* href)
{
	int i, j, k, length;
	int tmp = strlen(href) - 1;
	for (i = 0; strFromHTML[i] != '\0'; ++i) 
	{
		for (j = i, k = 0, length = strlen(href)-1; k <= length && strFromHTML[j] == href[k]; ++j, ++k) {
			if (k > 0 && k == tmp) {
				return j + (strlen(TAGHREF) - 1);
			}
		}
	}
	return -1;
}

void rdHtmlFile(char* htmlName)
{
	printf("%s\n", htmlName);
	FILE *file = fopen(htmlName, "r");
	char strFromHTML[LENHTML];
	data_links dt_links;
	dt_links.len_links = 0;
	while(fgets(strFromHTML, sizeof(strFromHTML), file))
	{
		if (strstr(strFromHTML, TAGHREF) != NULL) {
			int hrefStartIndex = strHrefIndex(strFromHTML, TAGHREF), indexLink = 0;
			char link[MAXLINK];
			while (strFromHTML[hrefStartIndex] != '\"') {
				link[indexLink++] = strFromHTML[hrefStartIndex++];
			}
			strcpy(dt_links.links[dt_links.len_links++], link);
			//printf("%s\n", link);
		}
	}
	fclose(file);
	downloadLinks(dt_links);
}

char* fexten(char* nameFile)
{
	int index_fexten = 0;
	char* fext = malloc((HTLEXT + 1) * sizeof(char));
	for (int i = strlen(nameFile) - 1; nameFile[i] != '.' && i >= 0; --i, ++index_fexten) {
		fext[index_fexten] = nameFile[i];
	}
	fext[index_fexten++] = '\0';
	reverse(fext, strlen(fext));
	return fext;
}
