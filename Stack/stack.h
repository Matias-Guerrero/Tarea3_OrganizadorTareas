#ifndef Stack_h
#define Stack_h

#include "../List/list.h"

typedef List Stack;

#define stack_create() createList()

#define stack_push(stack, data) pushFront(stack, data)

#define stack_pop(stack) popFront(stack)

#define stack_top(stack) firstList(stack)

#endif /* Stack_h */