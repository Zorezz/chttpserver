// this file is for functions containing code that deals with the serving of files for the web server such as extracting the URI of the resource
#include <stdio.h>
#include <string.h>
#include "parser.h"

// return the filename without the first slash
const char* getFilename(char *uri) {
    char fileName[sizeof(uri) + 1];
    int j = 0;
    // set i to 1 to skip the first /
    for (int i = 1; i < strlen(uri) + 1; i++) {
        fileName[j] = uri[i];
        j++;
    }
    return fileName;
}

int getFilesize(char fileName[]) {
	// check file size before allocating memory
	FILE *fp;
	long file_size;
	char *fileBuffer;

    fp = fopen(fileName, "r");

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	// push file pointer back to beginning of file
	rewind(fp);
    fclose(fp);

    return file_size;
}

// check if file exists otherwise send 404
int validateFile(char fileName[]){
    FILE *file;
    // if exists
    if ((file = fopen(fileName, "r"))) {
        fclose(file);
        return 1;
    }
    // if not exists
    return 0;
}
