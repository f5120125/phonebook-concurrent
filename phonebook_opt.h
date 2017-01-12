#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include <pthread.h>
#include <time.h>

#define MAX_LAST_NAME_SIZE 16

#define OPT 1


typedef struct _detail {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail;

typedef detail *pdetail;

typedef struct __PHONE_BOOK_ENTRY {
    char *lastName;
    struct __PHONE_BOOK_ENTRY *pNext;
    pdetail dtl;
} entry;

entry *findName(char lastname[], entry *pHead);
//void findName(void *args);
typedef struct _append_a {
    char *startPtr;
    char *endPtr;
    int tid;
    int num_thread;
    //entry *entryStart;
    entry *entryHead;
    entry *entryTail;
} thread_args;

typedef struct _find_name_args{
	entry *entryList;
	char *lastName;
}find_name_args;




thread_args *init_thread_args(char *startPtr, char *endPtr, int tid, int num_thread, entry *entryStart);

void append(void *arg);

void show_entry(entry *pHead);

//static double diff_in_second(struct timespec t1, struct timespec t2);

#endif
