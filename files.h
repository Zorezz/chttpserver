// this file is for functions containing code that deals with the serving of files for the web server such as extracting the URI of the resource
#include <stdio.h>
#include <string.h>

char* getFilename(char *buffer) {
	char *err = "Error";
	// check to make sure request is valid before continuing
	if (buffer[4] != '/') {
		printf("Not a correct request dropping");
		return err;
	}
	
	// do an initial loop to find the size of the uri to get good size of char array
	for (int i = 5; i < strlen(buffer); i++) {
		if (buffer[i] == ' ') {
			break;	
		}	
		char fileName[i];
	
	
}
