#include <stdlib.h>
#include "vector.h"


/*
 * My interpretation of the vector definition on cppreference.com
 * We allocate additional memory for future use and zero it
 *
 * Invariant:
 *   - size >= 0
 * */
Vector * vector__new(){
    Vector * target = (Vector *) malloc(sizeof(Vector));
    target -> size = 0;
    target -> data = nullptr;
    return target;
}

Vector * vector__copy(Vector * other){
    return vector__assign(vector__new(), other);
}

void vector__delete(Vector * v){
    free(v -> data);
    free(v);
}

Vector * vector__assign(Vector * lhs, Vector * rhs){
    lhs -> size  = rhs -> size;
    lhs -> data = (VectorValue *) realloc(lhs -> data, lhs -> size);
    for (int i = 0; i < rhs -> size; i++){
        lhs -> data[i] = rhs -> data[i];
    }
    return lhs;
}

int vector__equals(Vector * lhs, Vector * rhs){
    if (lhs -> size != rhs -> size) return 0;
    if (lhs -> size != rhs -> size) return 0;
    for (int i = 0; i < lhs -> size; i++){
        if (lhs -> data[i] != rhs -> data[i]) return 0;
    }
    return 1;
}


// Interface of Vector concept:

int vector__size(Vector * v){
    return v -> size;
}

int vector__empty(Vector * v){
    return vector__size(v) == 0;
}

VectorIterator vector__begin(Vector * v){
    return (VectorIterator) v -> data;
}

VectorIterator vector__end(Vector * v){
    return (VectorIterator) v -> data + v -> size;
}

// always O(1)
void vector__push_back(Vector * v, VectorValue value){
    v -> size += 1;
    v -> data = (VectorValue *) realloc(v -> data, v -> size);
    v -> data[v -> size - 1] = value;
}

// always O(n)
void vector__push_front(Vector * v, VectorValue value){
     v -> size += 1;
     v -> data = (VectorValue *) realloc(v -> data, v -> size);
     for(int i = 1; i < v -> size; i++){
         v -> data[i] = v -> data[i-1];
     }
     v -> data[0] = value;
}

// always O(1)
VectorValue vector__pop_back(Vector * v){
    VectorValue target = v -> data[v -> size - 1];
    v -> size -= 1;
    v -> data = (VectorValue *) realloc(v -> data, v -> size);
    return target;
}

// always O(n)
VectorValue vector__pop_front(Vector * v){
    VectorValue target = v -> data[0];
    for(int i = 0; i < v -> size; i++){
        v -> data[i] = v -> data[i+1];
    }
    v -> data = (VectorValue *) realloc(v -> data, v -> size);
    return target;
}

VectorValue vector__at(Vector * v, int offset){
    return v -> data[offset];
}

