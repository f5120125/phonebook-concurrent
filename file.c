#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUFF_SIZE 20

void file_align(char *orig_path, char *align_path, int size)
{
    FILE *orig_fp = fopen(orig_path, "r");
    FILE *align_fp = fopen(align_path, "w+");

    char read_buff[MAX_BUFF_SIZE];

    char *write_buff = (char *) malloc(sizeof(char) * size);

    while (fgets(read_buff, sizeof(read_buff), orig_fp)) {
        memset(write_buff, '\0', size);
		strcpy(write_buff, read_buff);
        fwrite(write_buff, size, 1, align_fp);
    }

    fclose(orig_fp);
    fclose(align_fp);
}

off_t fsize(char *path)
{
    struct stat st;
    stat(path, &st);
    return st.st_size;
}
