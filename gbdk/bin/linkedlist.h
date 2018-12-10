#ifndef LinkedList_h
#define LinkedList_h
#include "leaders.h"

typedef enum{FALSE, TRUE} bool;
typedef struct LinkedList{
	leaders * value;
	struct LinkedList * next;
}LinkedList;
#endif