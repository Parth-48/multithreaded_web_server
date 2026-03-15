#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#include "../include/request.h"
#include<time.h>

#define BUFFER_SIZE 1024

const char* get_mime_type(char *path){
    char *ext = strrchr(path,'.');

    if(ext==NULL) return "text/plain";

    if(strcmp(ext,".html")==0) return "text/html";

    if(strcmp(ext,".css")==0) return "text/css";

    if(strcmp(ext,".js")==0) return "application/javascript";

    if(strcmp(ext,".png")==0) return "image/png";

    if(strcmp(ext,".jpg")==0 || strcmp(ext,".jpeg")==0) return "image/jpeg";

    if(strcmp(ext,".gif")==0) return "image/gif";

    return "text/plain";
}

void log_request(char *method, char *path, int status){
    FILE *log = fopen("logs/server.log","a");

    if(log==NULL) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(log, "[%02d:%02d:%02d] %s %s %d \n" ,
    t->tm_hour,
    t->tm_min,
    t->tm_sec,
    method,
    path,
    status);

    fclose(log);
}

void handle_request(SOCKET client_fd){
    
    char buffer[BUFFER_SIZE];

    recv(client_fd,buffer,BUFFER_SIZE,0);

    printf("Request received: \n%s\n" ,buffer);

    char method[50];
    char path[100];
    char version[20];

    sscanf(buffer, "%s %s %s",method,path,version);
    printf("Method: %s\n" ,method);
    printf("Path: %s\n" ,path);
    printf("Version: %s\n" ,version);

    if(strcmp(path,"/")==0)
    strcpy(path,"/index.html");

    char fullpath[200] = "www";
    strcat(fullpath,path);

    FILE *file = fopen(fullpath,"rb");

    if(file==NULL){

        FILE *error_file = fopen("www/404.html","rb");
        char header[] = "HTTP/1.1 404 Not Found\r\n"
                        "Content-Type: text/html\r\n\r\n";

                        send(client_fd,header,strlen(header),0);

                        char buffer[1024];
                        int bytes;
                        while((bytes = fread(buffer,1,sizeof(buffer),error_file))>0)
                        send(client_fd,buffer,bytes,0);
                        fclose(error_file);

                        log_request(method,path,404);

                        closesocket(client_fd);
                        return;
    }
    
    char header[256];
    const char *mime = get_mime_type(path);

    sprintf(header, "HTTP/1.1 200 OK\r\n" 
                    "Content-Type: %s\r\n\r\n",mime);

    send(client_fd,header,strlen(header),0);

    char filebuffer[1024];
    int bytes;

    while((bytes=fread(filebuffer,1,1024,file))>0)
    send(client_fd,filebuffer,bytes,0);
    
    fclose(file);

    log_request(method,path,200);
    closesocket(client_fd);
}