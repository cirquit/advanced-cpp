#include <stdlib.h>
#include "stack.h"

// Interface of Standard concept:

Stack * stack__new(){
    Stack * target = (Stack *) malloc(sizeof(Stack));
    target -> size = 0;
    target -> data = nullptr;
    return (Stack *) target;
}

Stack * stack__copy(Stack * other){
    Stack * target = stack__new();
    return stack__assign(target, other);
}

void stack__delete(Stack * s){
    free(s -> data);
    free(s);
}

Stack * stack__assign(Stack * lhs, Stack * rhs){
    if (lhs -> size != rhs -> size){
        lhs -> size = rhs -> size;
        lhs -> data = (StackValue *) realloc(lhs -> data, lhs -> size);
    }
    for (int i = 0; i < lhs -> size; i++){
        lhs -> data[i] = rhs -> data[i];
    }
    return lhs;
}

int stack__equals(Stack * lhs, Stack * rhs){
    if (lhs -> size != rhs -> size) return 0;
    for(int i = 0; i < lhs -> size; i++){
        if (lhs -> data[i] != rhs -> data[i]) return 0;
    }
    return 1;
}

// Interface of Stack concept:

int stack__size(Stack * s){
    return s -> size;
}

int stack__empty(Stack * s){
    return s -> size == 0;
}

void stack__push(Stack * s, StackValue value){
    s -> size += 1;
    s -> data = (StackValue *) realloc(s -> data, s -> size);
    s -> data[s -> size-1] = value;
}

/*
 * One could just decrement the size and not use the realloc for
 * performance reasons, but then the memory would not be freed until the
 * Stack is not used and fully freed
 * */

StackValue stack__pop(Stack * s){
    StackValue res = s -> data[s -> size-1];
    s -> size -= 1;
    s -> data = (StackValue *) realloc(s -> data, s -> size);
    return res;
}
