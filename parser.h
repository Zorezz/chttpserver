// functions for parsing the HTTP request
#include <string.h>


// returns an int with the type of request
/*
    INVALID REQUEST - -1
    GET     - 0
    HEAD    - 1
    POST    - 2
    PUT     - 3
    DELETE  - 4
    CONNECT - 5
    OPTIONS - 6
    TRACE   - 7
    PATCH   - 8
*/
int parseReqType(char *requestBuff) {
    int file_size = sizeof(requestBuff);
    char* tokenBuff;

    tokenBuff = strtok(requestBuff, " ");

    // the evil if else spam
    if(strcmp(tokenBuff, "GET") == 0) {
            return 0;
    }
    else if(strcmp(tokenBuff, "HEAD") == 0) {
        return 1;
    }
    else if(strcmp(tokenBuff, "POST") == 0) {
        return 2;
    }
    else if(strcmp(tokenBuff, "PUT") == 0) {
        return 3;
    }
    else if(strcmp(tokenBuff, "DELETE") == 0) {
        return 4;
    }
    else if(strcmp(tokenBuff, "CONNECT") == 0) {
        return 5;
    }
    else if(strcmp(tokenBuff, "OPTIONS") == 0) {
        return 6;
    }
    else if(strcmp(tokenBuff, "TRACE") == 0) {
        return 7;
    }
    else if(strcmp(tokenBuff, "PATCH") == 0) {
        return 8;
    }
    // if anything else not a valid request return -1
    else {
        return -1;
    }
}
