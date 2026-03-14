#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#include "../include/request.h"

#define BUFFER_SIZE 1024

void handle_request(SOCKET client_fd){
    
    char buffer[BUFFER_SIZE];

    recv(client_fd,buffer,BUFFER_SIZE,0);

    printf("Request received: \n%s\n" ,buffer);

    char method[50];
    char path[100];

    sscanf(buffer, "%s %s",method,path);

    if(strcmp(path,"/")==0)
    strcpy(path,"/index.html");

    char fullpath[200] = "www";
    strcat(fullpath,path);

    FILE *file = fopen(fullpath,"r");

    if(file==NULL){

        char response[] = "HTTP/1.1 404 Not Found\r\n"
                        "Content-Type: text/html\r\n\r\n"
                        "<h1>404 File Not Found</h1>";

                        send(client_fd,response,strlen(response),0);
                        return;
    }

    char header[] = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n\r\n";

                    send(client_fd,header,strlen(header),0);

                    char filebuffer[1024];
                    int bytes;

                    while((bytes=fread(filebuffer,1,1024,file))>0)
                    send(client_fd,filebuffer,bytes,0);
    
    fclose(file);
}