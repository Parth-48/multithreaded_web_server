#include<stdio.h>
#include<windows.h>
#include<winsock2.h>
#include "../include/threadpool.h"
#include "../include/request.h"

SOCKET task_queue[QUEUE_SIZE];

int front=0;
int rear=0;
int count=0;

HANDLE mutex;
HANDLE task_available;
HANDLE queue_space;

DWORD WINAPI worker_thread(void *client_socket_ptr){
    while(1){
        WaitForSingleObject(task_available, INFINITE);

        WaitForSingleObject(mutex, INFINITE);

        SOCKET client_fd = task_queue[front];
        front = (front+1) % QUEUE_SIZE;
        count--;

        ReleaseMutex(mutex);

        ReleaseSemaphore(queue_space,1,NULL);

        handle_request(client_fd);
        closesocket(client_fd);
    }

    return 0;
}

void threadpool_init(){
    mutex = CreateMutex(NULL,FALSE,NULL);
    task_available = CreateSemaphore(NULL,0,QUEUE_SIZE,NULL);
    queue_space = CreateSemaphore(NULL,QUEUE_SIZE,QUEUE_SIZE,NULL);

    for(int i=0; i<THREAD_COUNT; i++){
        CreateThread(NULL,0,worker_thread,NULL,0,NULL);
    }
}

void add_task(SOCKET client_fd){
    WaitForSingleObject(queue_space,INFINITE);

    WaitForSingleObject(mutex, INFINITE);

    task_queue[rear] = client_fd;
    rear = (rear+1) % QUEUE_SIZE;
    count++;

    ReleaseMutex(mutex);

    ReleaseSemaphore(task_available,1,NULL);
}