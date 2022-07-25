#include "href.h"

void reverse(char*, int);
char* getNameFileLink(char*, int);
char* getExtenFromLink(char*, int);
char *subStr(char*, int, int, char*);
void dwlink(char *path, char *url);
void rplcSlshLnk(char *name_file);

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

// download list links and save file
void dwlstlinks(data_links dt_links)
{
	char path[5000]; // path to witch file save
	char *exten_file, *name_file; 
	for (int i = 0, len_url; i < dt_links.len_links; ++i) {
		len_url = strlen(dt_links.links[i]);
		exten_file = getExtenFromLink(dt_links.links[i], len_url);	
		name_file = getNameFileLink(dt_links.links[i], len_url);
		rplcSlshLnk(name_file);

		sprintf(path, "%s/%s.%s", DOWNDIR, name_file, exten_file);
		dwlink(path, dt_links.links[i]);		
	}
}

// download file on link from href
void dwlink(char *path, char *url)
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

int strHrefIndex(char* str_from_html, char* href)
{
	int i, j, k, length;
	int tmp = strlen(href) - 1;
	for (i = 0; str_from_html[i] != '\0'; ++i) 
	{
		for (j = i, k = 0, length = strlen(href)-1; k <= length && str_from_html[j] == href[k]; ++j, ++k) {
			if (k > 0 && k == tmp) {
				return j + (strlen(TAGHREF) - 1);
			}
		}
	}
	return -1;
}

void rdHtmlFile(char* html_name)
{
	//printf("%s\n", htmlName);
	FILE *file = fopen(html_name, "r");
	char str_from_html[LENHTML];
	data_links dt_links;
	dt_links.len_links = 0;
	while(fgets(str_from_html, sizeof(str_from_html), file))
	{
		if (strstr(str_from_html, TAGHREF) != NULL) {
			int href_start_index = strHrefIndex(str_from_html, TAGHREF), index_link = 0;
			char link[MAXLINK];
			while (str_from_html[href_start_index] != '\"') {
				link[index_link++] = str_from_html[href_start_index++];
			}
			strcpy(dt_links.links[dt_links.len_links++], link);
			//printf("%s\n", link);
		}
	}
	fclose(file);
	dwlstlinks(dt_links);
}

char* fexten(char* name_file)
{
	int index_fexten = 0, len_fname = strlen(name_file);
	char* fext = malloc(len_fname * sizeof(char)); // string file extension
	for (int i = len_fname - 1; name_file[i] != '.' && i >= 0; --i, ++index_fexten) {
		fext[index_fexten] = name_file[i];
	} // get formation extension in href
	fext[index_fexten++] = '\0'; // end symbol extension
	reverse(fext, strlen(fext)); // revers extension
	return fext;
}
