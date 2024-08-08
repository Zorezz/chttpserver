// functions for dealing with all request types
#include <string.h>
#include "files.h"
#include "parser.h"

const char* send404() {
    const char error[] = "HTTP/1.1 404 Not Found";
    return error;
}

const char* sendGet(char *reqBuffer, char *fileName, char *reply) {
    // temp test to see if the rest works.
    char header[500] =
				"HTTP/1.1 200 OK\n"
				"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
				"Server: CHTTP\n"
				"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
				"ETag: \"56d-9989200-1132c580\"\n"
				"Content-Type: text/html\n"
				"Accept-Ranges: bytes\n"
				"Connection: close\n"
				"\n";
    // extract file to send from request
    char* uri = parseUri(reqBuffer);
    // check if file exists, if not send 404
    if ((validateFile(fileName)) == 0) {
        const char err[] = "HTTP/1.1 404 Not Found\n"
                           "Content-Type: text/html\n\n"
                           "<html>\n"
                           "<head>\n"
                           "<title>Resource Not Found</title>\n"
                           "</head>\n"
                           "</html>";
        memset(reply, '\0', sizeof(reply));
        strcpy(reply, err);
        return reply;
    }

    // read file and insert after header
    else {
        int fileSize = getFilesize(fileName);
        char fileBuff[1000];
        FILE *fp = fopen(fileName, "r");
        fread(fileBuff, sizeof(fileBuff), 1, fp);

        strcpy(reply, header);
        strcat(reply, fileBuff);
        return reply;
    }
}
