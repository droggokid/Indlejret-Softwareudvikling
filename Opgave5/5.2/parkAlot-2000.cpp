#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m;
pthread_cond_t c;
bool waitForPermissionEnter, waitForPermissionExit, carArrive, carExit = false;

void *CarThread(void *arg)
{
    pthread_mutex_lock(&m);
    carArrive = true;
    pthread_cond_signal(&c);

    while (waitForPermissionEnter == false)
    {
        pthread_cond_wait(&c, &m);
    }
    carArrive = false;

    usleep(5000);

    bool carExit = true;
    pthread_cond_signal(&c);

    while (waitForPermissionExit == false)
    {
        pthread_cond_wait(&c, &m);
    }

    pthread_mutex_unlock(&m);
    pthread_exit(NULL);
    return NULL;
    // enterPL;
    // carsInPL++;
    // carWaiting = false;
    // condSignal(c);
    // unlock(m);
}

void *entryGuardThread(void *arg)
{
    pthread_mutex_lock(&m);

    while (carArrive == false)
    {
        pthread_cond_wait(&c, &m);
    }
    waitForPermissionEnter = true;
    pthread_cond_signal(&c);

    pthread_mutex_unlock(&m);
}

void *exitGuardThread(void *arg)
{
    pthread_mutex_lock(&m);

    while (carExit == false)
    {
        pthread_cond_wait(&c, &m);
    }

    waitForPermissionExit = true;
    pthread_cond_signal(&c);

    pthread_mutex_unlock(&m);
}

int main()
{
    pthread_t car1, exitGuardThread, enterGuardThread;

    pthread_mutex_init(&m, NULL);

    pthread_create(&car1, NULL, CarThread, NULL);

    pthread_join(car1, NULL);

    return 0;
}