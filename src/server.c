#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#include "../include/server.h"
#include "../include/request.h"
#include "../include/threadpool.h"

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024

void start_server(int port){

    WSADATA wsa;
    SOCKET server_fd, client_fd;

    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);

    char buffer[BUFFER_SIZE];

    WSAStartup(MAKEWORD(2,2), &wsa);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_fd == INVALID_SOCKET){
        printf("Socket creation failed\n");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Bind failed\n");
        return;
    }

    listen(server_fd, 10);

    printf("Server running on port %d... \n", port);

    threadpool_init();
    
    while(1){

        printf("Waiting for client... \n");

        client_fd = accept(server_fd,NULL,NULL);

        if(client_fd == INVALID_SOCKET){
            printf("Client connection failed\n");
            continue;
        }

        if(client_fd != INVALID_SOCKET){
            add_task(client_fd);
        }

    }

    closesocket(server_fd);
    WSACleanup();

}

