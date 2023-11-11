#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m;
pthread_cond_t enter, leave;
bool waitForPermissionEnter = false,
     waitForPermissionExit = false,
     carArrive = false,
     carExit = false;

void *carThread(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&m);
        carArrive = true;
        printf("Car waiting to enter.\n");
        pthread_cond_signal(&enter);

        while (waitForPermissionEnter == false)
        {
            pthread_cond_wait(&enter, &m);
        }
        printf("Car in parking lot\n");
        carArrive = false;
        pthread_cond_signal(&enter);

        sleep(5);

        printf("Car waiting to leave\n");
        carExit = true;
        pthread_cond_signal(&leave);

        while (waitForPermissionExit == false)
        {
            pthread_cond_wait(&leave, &m);
        }
        printf("Car left parking lot\n");
        carExit = false;
        pthread_cond_signal(&leave);

        pthread_mutex_unlock(&m);
        sleep(1);
    }
}

void *entryGuardThread(void *arg)
{
    while (1)
    {
        waitForPermissionEnter = false;
        pthread_mutex_lock(&m);

        while (carArrive == false)
        {
            pthread_cond_wait(&enter, &m);
            sleep(1);
        }
        sleep(1);
        printf("Enter Guard: car allowed to enter\n");
        sleep(1);
        waitForPermissionEnter = true;
        pthread_cond_signal(&enter);

        while (carArrive)
        {
            pthread_cond_wait(&enter, &m);
        }

        pthread_mutex_unlock(&m);
    }
}

void *exitGuardThread(void *arg)
{
    while (1)
    {
        waitForPermissionExit = false;
        pthread_mutex_lock(&m);

        while (carExit == false)
        {
            pthread_cond_wait(&leave, &m);
            sleep(1);
        }
        sleep(1);
        printf("Exit Guard: car allowed to leave\n");
        sleep(1);
        waitForPermissionExit = true;
        pthread_cond_signal(&leave);

        while (carExit)
        {
            pthread_cond_wait(&leave, &m);
        }

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