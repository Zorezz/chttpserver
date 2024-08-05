// functions for generating the HTTP header
#include <openssl/sha.h>


const char* etypeHeader(char *buffer) {
    // read file and hash it into sha1 for ETYPE Header
    unsigned char sha1_digest[SHA_DIGEST_LENGTH];

        SHA1(buffer, strlen(buffer), sha1_digest);

        // for debug purposes
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
            printf("%02x", sha1_digest[i]);
        }
}
