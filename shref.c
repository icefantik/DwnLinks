#include "shref.h"
#include <string.h>

void rslash(char *name_file) // replace slash link name
{
        for (int index_name = 0; name_file[index_name] != '\0'; ++index_name) {
                if (name_file[index_name] == '/') {
                        name_file[index_name] = '\\';
                }
        }
}

char *fnlink(char* url, int len_url) // get name file link
{
        int index_slesh = strchr(url, '/') - url + 1;
        char dest[5001];
        char *tmp = substr(url, index_slesh, len_url, dest);
        return tmp;
}

char *substr(char* input, int offset, int len, char* dest)
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

