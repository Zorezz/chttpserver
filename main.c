// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>

#include "requests.h"

// global variables and defines
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
#define PORT 8088

void * socketThread(int clientSocket) {
    char clientMessage[2000];
    char reply[10000];
    int reqType;

    int newSocket = clientSocket;
    recv(newSocket, clientMessage, 2000, 0);
    //printf("%s", clientMessage);
    // parse the request for request type
    //reqType = parseReqType(&clientMessage);
    reqType = 0;
    printf("%d", reqType);
    // eventually change this to a switch case.
    if (reqType == 0) {
       // Send message to client socket
        pthread_mutex_lock(&lock);
        char* token = parseUri(clientMessage);
        char fileName[200];
        int j = 0;
        for (int i = 1; i < (strlen(token) + 1); i++) {
            fileName[j] = token[i];
            j++;
        }

        if (token[1] == NULL) {
            sendGet(clientMessage, "index.html", &reply);
        }
        else {
            sendGet(clientMessage, fileName, &reply);
        }
        pthread_mutex_unlock(&lock);
        send(newSocket, reply, strlen(reply), 0);
        printf("Exit socketThread\n");
        close(newSocket);
    }
    else {
        printf("not implemented yet\n");
    }
}

int main(int argc, char const *argv[])
{
    int server_fd, newSocket; long valread;
    struct sockaddr_in address;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    pid_t pid[50];

    // Creating socket file descriptor
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);


    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 50) == 0)
        printf("Listening\n");
    else
        printf("Error in listen\n");
        pthread_t tid[60];
        int i = 0;
    while(1)
    {
        addr_size = sizeof serverStorage;
        newSocket = accept(server_fd, (struct sockaddr *) &serverStorage, &addr_size);
        int pid_c = 0;

        if ((pid_c = fork()) == 0) {
            printf("Creating new process");
            socketThread(newSocket);
        }
        else {
            pid[i++] = pid_c;
            if (i >= 49) {
                i = 0;
                while (i < 50) {
                    waitpid(pid[i++], NULL, 0);
                }
                i = 0;
            }
        }
    }
    return 0;
}
