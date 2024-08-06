// functions for dealing with all request types
#include "files.h"


const char* send404() {
    const char error[] = "HTTP/1.1 404 Not Found";
    return error;
}

const char* sendGet() {

}
