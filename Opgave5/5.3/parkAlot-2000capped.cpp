#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define CAP 1

int cars = 3;
int freeSpaces = CAP;
pthread_mutex_t m;
pthread_cond_t enter, leave, spaces;
bool waitForPermissionEnter = false,
     waitForPermissionExit = false,
     carArrive = false,
     carExit = false;

void *carThread(void *arg)
{
    int *id = static_cast<int *>(arg);
    while (1)
    {
        pthread_mutex_lock(&m);
        carArrive = true;
        printf("Car %d waiting to enter.\n", *id);
        pthread_cond_signal(&enter);

        while (waitForPermissionEnter == false)
        {
            pthread_cond_wait(&enter, &m);
        }
        printf("Car %d in parking lot\n", *id);
        carArrive = false;
        pthread_cond_signal(&enter);

        srand(time(0));
        int time = rand() % (1 - 10 + 1) + 10; // tilfældigt helt tal mellem [a;b]

        pthread_mutex_unlock(&m);
        sleep(time);
        pthread_mutex_lock(&m);

        printf("Car %d waiting to leave\n", *id);
        carExit = true;
        pthread_cond_signal(&leave);

        while (waitForPermissionExit == false)
        {
            pthread_cond_wait(&leave, &m);
        }
        printf("Car %d left parking lot\n", *id);
        carExit = false;
        pthread_cond_signal(&leave);

        pthread_mutex_unlock(&m);
        sleep(time);
    }
}

void *entryGuardThread(void *arg)
{
    while (1)
    {
        waitForPermissionEnter = false;
        pthread_mutex_lock(&m);
        if (freeSpaces > 0)
        {
            while (carArrive == false)
            {
                pthread_cond_wait(&enter, &m);
                sleep(1);
            }
            freeSpaces--;
            printf("Enter Guard: Car allowed to enter. Free Spaces: %d\n", freeSpaces);
            waitForPermissionEnter = true;
            pthread_cond_signal(&enter);
            sleep(1);

            while (carArrive)
            {
                pthread_cond_wait(&enter, &m);
            }

            waitForPermissionEnter = false;
            pthread_cond_signal(&enter);
        }
        else
        {
            printf("Parking lot full\n");
            while (freeSpaces == 0)
            {
                pthread_cond_wait(&spaces, &m);
            }
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
        printf("Exit Guard: car allowed to leave. Free Spaces: %d\n", freeSpaces);
        sleep(1);
        waitForPermissionExit = true;
        pthread_cond_signal(&leave);
        freeSpaces++;
        pthread_cond_signal(&spaces);

        while (carExit)
        {
            pthread_cond_wait(&leave, &m);
        }

        pthread_mutex_unlock(&m);
    }
}

int main()
{
    pthread_t exitGuard, enterGuard;
    pthread_t carArray[cars];
    int carIDs[cars];

    pthread_mutex_init(&m, NULL);

    pthread_create(&enterGuard, NULL, entryGuardThread, NULL);
    pthread_create(&exitGuard, NULL, exitGuardThread, NULL);

    for (int i = 0; i < cars; i++)
    {
        carIDs[i] = i+1;
        pthread_create(&carArray[i], NULL, carThread, &carIDs[i]);
    }

    pthread_join(enterGuard, NULL);
    pthread_join(exitGuard, NULL);

    for (int i = 0; i < cars; i++)
    {
        pthread_join(carArray[i], NULL);
        
    }

    return 0;
}