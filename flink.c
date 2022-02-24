#include "flink.h"

data_links getLinksFromFile(char *path_file)
{
	data_links dt_links;
	FILE *file = fopen(path_file, "r");
	char ftmpLinks[1000];
	for (dt_links.len_links = 0; fgets(ftmpLinks, sizeof(ftmpLinks), file); ++dt_links.len_links) {
		strcpy(dt_links.links[dt_links.len_links], ftmpLinks);
	}
	fclose(file);
	return dt_links;
}
