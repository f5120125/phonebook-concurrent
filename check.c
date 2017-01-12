#include <stdio.h>
#include <sys/stat.h>//stat, stat(paath, struct stat)
#include <sys/mman.h>//mmap()
#include <fcntl.h>//open(file_name, )
#include <stdbool.h>

#define MAX 16
#define ORIG_FILE_PATH "./dictionary/words.txt"
#define ALIGNMENT_FILE "align.txt"

off_t getFileSize( char *path);

int main(){
	bool consistency=true;
	char orig_buff[MAX];
	char align_buff[MAX];
	FILE *orig_fp = fopen(ORIG_FILE_PATH, "r");
	FILE *align_fp = fopen(ALIGNMENT_FILE, "r");

	int fd = open(ALIGNMENT_FILE, O_RDONLY | O_NONBLOCK);
	off_t new_file_size = getFileSize(ALIGNMENT_FILE);
	char *map = mmap(NULL, new_file_size, PROT_READ, MAP_SHARED, fd, 0);
	char *tmp=map;

	while( fgets(orig_buff, sizeof(orig_buff), orig_fp) ){
		if( strncmp(orig_buff, tmp, sizeof(orig_buff)) != 0){
			consistency=false;
			break;
		}
		tmp+=MAX;
	}
	if(consistency)
		printf("Files are consistent\n");
	else
		printf("Files are not the same\n");
	return 0;
}

off_t getFileSize( char *path){
	struct stat file_stat;
	stat(path, &file_stat);
	return file_stat.st_size;
}
