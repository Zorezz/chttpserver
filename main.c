// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8088
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *hello = "Hello from server";

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
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
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
		// get the uri to then send the correct file
		if ( buffer[4] == '/' ) {
			// implement a check for the actual URI and sending the correct file
			if ( buffer[5] != ' ') {
			 	printf("Not implemented yet!");
				close(new_socket);
				return 0;
			}
			// if it asks for a / we will just send it the index.html file
			else {
			printf("Sending index.html file");
			char *header =
				"HTTP/1.1 200 OK\n"
				"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
				"Server: CHTTP\n"
				"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
				"ETag: \"56d-9989200-1132c580\"\n"
				"Content-Type: text/html\n"
				"Accept-Ranges: bytes\n"
				"Connection: close\n"
				"\n";

			// check file size before allocating memory
			FILE *fp;
			long file_size;
			char *fileBuffer;

			fp = fopen("index.html", "r");

			fseek(fp, 0, SEEK_END);
			file_size = ftell(fp);
			// push file pointer back to beginning of file
			rewind(fp);

			fileBuffer = (char*) malloc(file_size + 1);

			fread(fileBuffer, file_size, 1, fp);

			char reply[50000];
			strcpy(reply, header);
			strcat(reply, fileBuffer);

			fclose(fp);
			free(fileBuffer);


			// write to socket the file
			write(new_socket, reply, strlen(reply));
			}
		}
	}
        close(new_socket);
    }
    return 0;
}
