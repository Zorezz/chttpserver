// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "requests.h"

#define PORT 8088
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);


    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\nWaiting for new connection...\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
	// implement GET request
	if (strncmp( buffer, "GET", 3 ) == 0) {
			/* char *header =
				"HTTP/1.1 200 OK\n"
				"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
				"Server: CHTTP\n"
				"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
				"ETag: \"56d-9989200-1132c580\"\n"
				"Content-Type: text/html\n"
				"Accept-Ranges: bytes\n"
				"Connection: close\n"
				"\n"; */
            char reply[10000];
            char* token = parseUri(buffer);
            char fileName[20];
            int j = 0;
            for (int i = 1; i < (strlen(token) + 1); i++) {
                fileName[j] = token[i];
                j++;
            }

            if (token[1] == NULL) {
                sendGet(buffer, "index.html", &reply);
            }
            else {
                sendGet(buffer, fileName, &reply);
            }


			write(new_socket, reply, strlen(reply));
        }
        close(new_socket);
    }
    return 0;
}
