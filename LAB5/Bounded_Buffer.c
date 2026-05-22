#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 15

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

HANDLE empty;
HANDLE full;
HANDLE mutex;

// PRODUCER THREAD
DWORD WINAPI producer(LPVOID arg)
{
    for(int item = 0; item < MAX_ITEMS; item++)
    {
        WaitForSingleObject(empty, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buffer[in] = item;

        printf("Produced: %d at buffer[%d]\n",
               item, in);

        in = (in + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);
        ReleaseSemaphore(full, 1, NULL);

        Sleep(200);
    }

    return 0;
}

// CONSUMER THREAD
DWORD WINAPI consumer(LPVOID arg)
{
    for(int i = 0; i < MAX_ITEMS; i++)
    {
        WaitForSingleObject(full, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        printf("Consumed: %d from buffer[%d]\n",
               buffer[out], out);

        out = (out + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);
        ReleaseSemaphore(empty, 1, NULL);

        Sleep(400);
    }

    return 0;
}

int main()
{
    HANDLE prodThread;
    HANDLE consThread;

    empty = CreateSemaphore(NULL,
                            BUFFER_SIZE,
                            BUFFER_SIZE,
                            NULL);

    full = CreateSemaphore(NULL,
                           0,
                           BUFFER_SIZE,
                           NULL);

    mutex = CreateMutex(NULL,
                        FALSE,
                        NULL);

    prodThread = CreateThread(NULL,
                              0,
                              producer,
                              NULL,
                              0,
                              NULL);

    consThread = CreateThread(NULL,
                              0,
                              consumer,
                              NULL,
                              0,
                              NULL);

    WaitForSingleObject(prodThread, INFINITE);
    WaitForSingleObject(consThread, INFINITE);

    CloseHandle(empty);
    CloseHandle(full);
    CloseHandle(mutex);

    return 0;
}
