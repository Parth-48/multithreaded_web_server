#include<stdio.h>
#include<windows.h>
#include<winsock2.h>
#include "../include/threadpool.h"
#include "../include/request.h"

SOCKET task_queue[QUEUE_SIZE];

int front=0;
int rear=0;

HANDLE mutex;
HANDLE task_available;

DWORD WINAPI worker_thread(void *client_socket_ptr){
    while(1){
        WaitForSingleObject(task_available, INFINITE);

        WaitForSingleObject(mutex, INFINITE);

        SOCKET client_fd = task_queue[front];
        front = (front+1) % QUEUE_SIZE;

        ReleaseMutex(mutex);

        handle_request(client_fd);
        closesocket(client_fd);
    }
}

void threadpool_init(){
    mutex = CreateMutex(NULL,FALSE,NULL);
    task_available = CreateSemaphore(NULL,0,QUEUE_SIZE,NULL);

    for(int i=0; i<THREAD_COUNT; i++){
        CreateThread(NULL,0,worker_thread,NULL,0,NULL);
    }
}

void add_task(SOCKET client_fd){
    WaitForSingleObject(mutex, INFINITE);

    task_queue[rear] = client_fd;
    rear = (rear+1) % QUEUE_SIZE;

    ReleaseMutex(mutex);

    ReleaseSemaphore(task_available,1,NULL);
}