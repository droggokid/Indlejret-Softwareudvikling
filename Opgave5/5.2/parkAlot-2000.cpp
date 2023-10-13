#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m;
pthread_cond_t c;
bool waitForPermissionEnter, waitForPermissionExit, carArrive = false;

void *CarThread(void *arg)
{
    pthread_mutex_lock(&m);
    bool carArrive = true;
    pthread_cond_signal(&c);
    
    while (waitForPermissionEnter == false){
        pthread_cond_wait(&c,&m);
    }

    usleep(500);

    bool carArrive = false;
    pthread_cond_signal(&c);
    
    while (waitForPermissionExit == false){
        pthread_cond_wait(&c,&m);
    }

    pthread_mutex_unlock(&m);
    pthread_exit(NULL);
    return NULL;
    //enterPL;
    //carsInPL++;
    //carWaiting = false;
    //condSignal(c);
    //unlock(m);

   
}

void entryGuardThread()
{
    pthread_mutex_lock(&m);

    while(carArrive == false){
        pthread_cond_wait(&c,&m);
    }
    waitForPermissionEnter = true;
    pthread_cond_signal(&c);

    while(carWaiting){
        condWait(c,m);

    closeEntryGate();
    entryGateOpen = false;

    unlock(m);
}

void exitGuardThread()
{
    lock(m);

    while(!carWaiting){
        condWait(c,m);
    }

    openExitGate();
    exitGateOpen = true;

    condSignal(c);
    while(carWaiting){
        condWait(c,m);

    closeEntryGate();
    entryGateOpen = false;

    unlock(m);
}

int main() {
    pthread_t car1;

    pthread_create(&car1, NULL, CarThread, NULL);

    pthread_join(car1, NULL); 

    return 0;
}