#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void search_directory(const char *path, const char *extension){

	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if(dir == NULL) {
	   perror("opendir");
	   return;
	}

	while((entry = readdir(dir)) != NULL) {
	// Skip "." and ".."
	if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
continue;
}

	char fullpath[1024];
	snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

	struct stat path_stat;
	if(stat(fullpath, &path_stat) == -1) {
	   continue;
	}

	if(S_ISDIR(path_stat.st_mode)) {
	   search_directory(fullpath, extension);
	} else if(S_ISREG(path_stat.st_mode)) {
	   char *dot = strrchr(entry->d_name, '.');

	if(dot != NULL && strcmp(dot + 1, extension) == 0) {
	   printf("%s\n", fullpath);
	}
    }
}
    closedir(dir);
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
	   printf("Usage: %s <start_directory> <extension>\n", argv[0]);
	   return 1;
	}

	search_directory(argv[1], argv[2]);
	return 0;
}
