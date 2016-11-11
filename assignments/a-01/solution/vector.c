#include <stdlib.h>
#include <math.h>
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
    v -> data = nullptr;
    free(v);
}

Vector * vector__assign(Vector * lhs, Vector * rhs){
    if (lhs == rhs) return lhs;
    lhs -> size  = rhs -> size;
    lhs -> data = (VectorValue *) realloc(lhs -> data,
                                          lhs -> size * sizeof(VectorValue));
    for (int i = 0; i < lhs -> size; i++){ // memcopy
        lhs -> data[i] = rhs -> data[i];
    }
    return lhs;
}

int vector__equals(Vector * lhs, Vector * rhs){
    if (lhs == rhs) return 1;
    if (lhs -> size != rhs -> size) return 0;
    for (int i = 0; i < lhs -> size; i++){
        if (lhs -> data[i] != rhs -> data[i]) return 0;
    }
    return 1;
}

// inplace O(n)
Vector * vector__reverse(Vector * v){
    int         k      = 0;
    int         bounds = floor(v -> size / 2);

    for(int i = 0; i < bounds; i++){
        k    = v -> size - 1 - i;
        v -> data[i] ^= v -> data[k];
        v -> data[k] ^= v -> data[i];
        v -> data[i] ^= v -> data[k];
    }

    return v;
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

// O(1)
void vector__push_back(Vector * v, VectorValue value){
    v -> size += 1;
    v -> data = (VectorValue *) realloc(v -> data,
                                        v -> size * sizeof(VectorValue));
    v -> data[v -> size - 1] = value;
}

// O(n)
void vector__push_front(Vector * v, VectorValue value){
     v -> size += 1;
     v -> data = (VectorValue *) realloc(v -> data,
                                         v -> size * sizeof(VectorValue));
     for(int i = v -> size - 1; i > 0; i--){
         v -> data[i] = v -> data[i-1];
     }
     v -> data[0] = value;
}

// O(1)
VectorValue vector__pop_back(Vector * v){
    VectorValue target = v -> data[v -> size - 1];
    v -> size -= 1;
    v -> data = (VectorValue *) realloc(v -> data,
                                        v -> size * sizeof(VectorValue));
    return target;
}

// O(n)
VectorValue vector__pop_front(Vector * v){
    VectorValue target = v -> data[0];
    for(int i = 0; i < v -> size - 1; i++){
        v -> data[i] = v -> data[i+1];
    }
    v -> size -= 1; // hier auskommentieren um den trace zu sehen
    v -> data = (VectorValue *) realloc(v -> data,
                                        v -> size * sizeof(VectorValue));
    return target;
}

VectorValue vector__at(Vector * v, int offset){
    return v -> data[offset];
}


