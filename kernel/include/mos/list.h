#ifndef __LIST_H
#define __LIST_H
#include <mos/types.h>

typedef struct _LinkedListNode
{
    void *data;
    _LinkedListNode *prev;
    _LinkedListNode *next;
} *LinkedList, LinkedListNode;

void List_Init(LinkedList *target);
void List_Size(LinkedList list);
void List_Add(LinkedList list, void *data);
void List_Get(LinkedList list, void *buffer);
void List_Set(LinkedList list, size_t idx, void *data);
void List_Push(LinkedList list, void *data);
void List_Pop(LinkedList list, void *buffer);
void List_Free(LinkedList list);
#endif