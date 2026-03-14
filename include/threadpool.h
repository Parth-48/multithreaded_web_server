#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <winsock2.h>

#define THREAD_COUNT 4
#define QUEUE_SIZE 100

void threadpool_init();
void add_task(SOCKET client_fd);

#endif