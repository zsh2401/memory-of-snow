#include <mos/list.h>
#include <mos/mm.h>
void List_Init(LinkedList* target){
    LinkedListNode* ptr = (LinkedListNode*)kmalloc(sizeof(LinkedListNode))
    *target = ptr;
}