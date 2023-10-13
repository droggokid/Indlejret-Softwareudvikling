#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m;
pthread_cond_t c;
bool waitForPermissionEnter, waitForPermissionExit, carArrive, carExit = false;

void *carThread(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&m);
        carArrive = true;
        printf("Car waiting to enter.\n");
        pthread_cond_signal(&c);

        while (waitForPermissionEnter == false)
        {
            pthread_cond_wait(&c, &m);
        }
        carArrive = false;
        printf("Car in parking lot\n");
        usleep(5000);
        printf("Car waiting to leave\n");
        carExit = true;
        pthread_cond_signal(&c);

        while (waitForPermissionExit == false)
        {
            pthread_cond_wait(&c, &m);
        }
        carExit = false;
        printf("Car left parking lot\n");
        pthread_mutex_unlock(&m);
        usleep(1000);
    }
}

void *entryGuardThread(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&m);

        while (carArrive == false)
        {
            pthread_cond_wait(&c, &m);
        }
        printf("Enter Guard: car allowed to enter\n");
        waitForPermissionEnter = true;
        pthread_cond_signal(&c);

        pthread_mutex_unlock(&m);
    }
}

void *exitGuardThread(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&m);

        while (carExit == false)
        {
            pthread_cond_wait(&c, &m);
        }
        printf("Exit Guard: car allowed to leave\n");
        waitForPermissionExit = true;
        pthread_cond_signal(&c);

        pthread_mutex_unlock(&m);
    }
}

int main()
{
    pthread_t car1, exitGuard, enterGuard;

    pthread_mutex_init(&m, NULL);

    pthread_create(&enterGuard, NULL, entryGuardThread, NULL);
    pthread_create(&exitGuard, NULL, exitGuardThread, NULL);
    pthread_create(&car1, NULL, carThread, NULL);

    pthread_join(enterGuard, NULL);
    pthread_join(exitGuard, NULL);
    pthread_join(car1, NULL);

    return 0;
}