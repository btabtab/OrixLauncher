#ifndef TOASTERDSP
#define TOASTERDSP

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/*
pthread_t* getToasterThreadID()
{
    static pthread_t toasterDSP_thread_ID;
    return toasterDSP_thread_ID;
}
*/

typedef struct Chirp
{
    int length;
    int frequency;
}
Chirp;

void* playChirp(Chirp chirp)
{
//    for(int i = 0; i != chirp.data_length; i++)
    {
        // _beep(chirp.frequency, chirp.length);
    }
  //  pthread_exit(NULL);
    return NULL;
}
/*
void creatToasterThread(void *(*function_pointer)(void *), Chirp* chirp)
{
    pthread_create(getToasterThreadID(), NULL, function_pointer, chirp);
}
*/
#endif