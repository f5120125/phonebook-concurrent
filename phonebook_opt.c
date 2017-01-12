#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "phonebook_opt.h"
#include "debug.h"


entry *findName(char lastname[], entry *pHead)
{
    size_t len = strlen(lastname);
    while (pHead != NULL) {
        if (strncasecmp(lastname, pHead->lastName, len) == 0
                //&& (pHead->lastName[len] == '\n' ||
                    //pHead->lastName[len] == '\0')) {
					){
            pHead->lastName = (char *) malloc(sizeof(char) *
                                              MAX_LAST_NAME_SIZE);
            memset(pHead->lastName, '\0', MAX_LAST_NAME_SIZE);
            strcpy(pHead->lastName, lastname);
            //pHead->dtl = (pdetail) malloc(sizeof(detail));
            return pHead;
        }
        //dprintf("find string = %s\n", pHead->lastName);
        pHead = pHead->pNext;
    }
    return NULL;
}

/*
void findName(void *args){
	find_name_args *argPtr = (find_name_args *)args;
	size_t length = strlen(argPtr->lastName);

	entry *entryPtr = argPtr->entryList;
	
	while( entryPtr != NULL){
		if( strncasecmp(argPtr->lastName, entryPtr->lastName, length) ==0 ){
			pthread_exit(NULL);

		}
		entryPtr = entryPtr->pNext;
	}
			pthread_exit(NULL);
}
*/








thread_args *init_thread_args(char *startPtr, char *endPtr, int tid, int num_thread,
                       entry *entryStart)
{
    thread_args *argPtr = (thread_args *) malloc(sizeof(thread_args));

    argPtr->startPtr = startPtr;
    argPtr->endPtr = endPtr;
    argPtr->tid = tid;
    argPtr->num_thread = num_thread;

    argPtr->entryHead = (argPtr->entryTail = entryStart);

    return argPtr;
}

void append(void *arg)
{
    struct timespec start, end;
    //double cpu_time;

    clock_gettime(CLOCK_REALTIME, &start);

    thread_args *argPtr = (thread_args *) arg;

    int count = 0;
    entry *entryPtr = argPtr->entryHead;
    for (char *strPtr = argPtr->startPtr; 
			strPtr < argPtr->endPtr;
            strPtr += MAX_LAST_NAME_SIZE * argPtr->num_thread, entryPtr += argPtr->num_thread,count++) {
        argPtr->entryTail->pNext = entryPtr;
        argPtr->entryTail = argPtr->entryTail->pNext;

        argPtr->entryTail->lastName = strPtr;
        dprintf("thread %d append string = %s\n",
                argPtr->tid, argPtr->entryTail->lastName);
        argPtr->entryTail->pNext = NULL;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    //cpu_time = diff_in_second(start, end);

    //dprintf("thread take %lf sec, count %d\n", cpu_time, count);

    pthread_exit(NULL);
}

void show_entry(entry *pHead)
{
    while (pHead != NULL) {
        printf("lastName = %s\n", pHead->lastName);
        pHead = pHead->pNext;
    }
}

/*static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}*/
