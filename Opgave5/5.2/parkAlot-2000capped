#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#DEFINE CAP 1

int freeSpaces = CAP;
pthread_mutex_t m;
pthread_cond_t enter, leave;
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
        sleep(1);
    }
}

void *entryGuardThread(void *arg)
{
    while (1)
    {
        waitForPermissionEnter = false;
        pthread_mutex_lock(&m);
        if (freeSpaces >= CAP)
        {
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
            freeSpaces--;

            while (carArrive)
            {
                pthread_cond_wait(&enter, &m);
            }
        }
        else
        {
            printf("Parking lot full");
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
        freeSpaces++;

        while (carExit)
        {
            pthread_cond_wait(&leave, &m);
        }

        pthread_mutex_unlock(&m);
    }
}

int main()
{
    pthread_t car1, car2, car3, exitGuard, enterGuard;
    pthread_mutex_init(&m, NULL);

    int ID1 = 1;
    int ID2 = 2;
    int ID3 = 3;

    pthread_create(&enterGuard, NULL, entryGuardThread, NULL);
    pthread_create(&exitGuard, NULL, exitGuardThread, NULL);

    pthread_create(&car1, NULL, carThread, &ID1);
    pthread_create(&car2, NULL, carThread, &ID2);
    pthread_create(&car3, NULL, carThread, &ID3);

    pthread_join(enterGuard, NULL);
    pthread_join(exitGuard, NULL);
    pthread_join(car1, NULL);
    pthread_join(car2, NULL);
    pthread_join(car3, NULL);

    return 0;
}