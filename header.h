// functions for generating the HTTP header
#include <openssl/sha.h>
#include <stdio.h>
#include <time.h>


// function hashes file from a file buffer and then returns the hash.
const char* etypeHeader(char *buffer) {
    // read file and hash it into sha1 for ETYPE Header
    unsigned char sha1_digest[SHA_DIGEST_LENGTH];

        SHA1(buffer, strlen(buffer), sha1_digest);
        // for debug purposes
        /*for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
            printf("%02x", sha1_digest[i]);
        } */

    return sha1_digest;
}

// returns the current date in format: Thu, 19 Feb 2009 12:27:04 GMT
const char* dateHeader() {
    time_t t  = time(NULL);
    struct tm *tm = gmtime(&t);
    char dateStr[64];
    size_t ret = strftime(dateStr, sizeof(dateStr), "%a, %d %b %Y %X GMT", tm);

    return ret;
}
