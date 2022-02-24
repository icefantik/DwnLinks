#include "dir.h"
#include "href.h"
#include "flink.h"

void selcFile(char *file_exten, char *dir_links) 
{
	DIR *dir;
	struct dirent *ent;
	struct stat st;
	char cwd[MAXDIR];
	char *links_dir = (char*)malloc(MAXDIR * sizeof(char));
	char *path = (char*)malloc(MAXDIR * sizeof(char));
	getcwd(cwd, MAXDIR);
	size_t needed_size_dir = snprintf(NULL, 0,"%s/%s", cwd, dir_links);
	snprintf(links_dir, needed_size_dir,"%s/%s", cwd, dir_links);
	if ((dir = opendir(links_dir)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			sprintf(path, "%s/%s", links_dir, ent->d_name);
			if (stat(path, &st) == 0)	
			{
				if (st.st_mode & S_IFREG) { //check is files
					if (strcmp(fexten(ent->d_name), file_exten) == 0) {
						rdHtmlFile(path);
					}
				}
			} else {
				printf("cannot access path: %s\n", path);
			}
			
			
		}
	}
	free(path);
	free(links_dir);
	closedir(dir);
}
