#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#include "../include/request.h"

#define BUFFER_SIZE 1024

void handle_request(int client_socket){
    
    char buffer[BUFFER_SIZE];

    recv(client_socket,buffer,BUFFER_SIZE,0);

    printf("Request received: \n%s\n" ,buffer);

    char method[50];
    char path[100];

    sscanf(buffer, "%s %s",method,path);

    if(strcmp(path,"/")==0)
    strcpy(path,"/index.html");

    char file_path[200] = "www";
    strcat(file_path,path);

    FILE *file = fopen(file_path,"r");

    if(file==NULL){

        char response[] = "HTTP/1.1 404 Not Found\r\n"
                        "Content-Type: text/html\r\n\r\n"
                        "<h1>404 File Not Found</h1>";

                        send(client_socket,response,strlen(response),0);
    }
    else{
        char header[] = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n\r\n";

                        send(client_socket,header,strlen(header),0);

                        char file_buffer[1024];
                        int bytes;

                        while((bytes=fread(file_buffer,1,1024,file))>0)
                        send(client_socket,file_buffer,bytes,0);
        
        fclose(file);
    }
}