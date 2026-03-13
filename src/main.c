#include<stdio.h>
#include "../include/server.h"

#define PORT 8080

int main(){

    printf("Starting web server... \n");

    start_server(PORT);

    return 0;
}