#include <stdlib.h>
#include "vector.h"


/*
 * My interpretation of the vector definition on cppreference.com
 * We allocate additional memory for future use and zero it
 *
 * Invariant:
 *   - end < size
 *   - start <= end
 *   - start >= 0
 *   - [0,start-1] = 0
 *   - [end, size] = 0
 *   - [start,end[ = filled by the user
 * */
Vector * vector__new(){
    Vector * target = (Vector *) malloc(sizeof(Vector));
    target -> size  = 100;
    target -> end   = 50;
    target -> start = 50;
    target -> data = (VectorValue *) malloc(target -> size * sizeof(VectorValue));
    for(int i = 0; i < target -> size; i++) target -> data[i] = 0;
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
    lhs -> data = (VectorValue *) realloc(lhs -> data, rhs -> size);
    for (int i = 0; i < rhs -> size; i++){
        lhs -> data[i] = rhs -> data[i];
    }
    lhs -> size  = rhs -> size;
    lhs -> start = rhs -> start;
    lhs -> end   = rhs -> end;
    return lhs;
}

int vector__equals(Vector * lhs, Vector * rhs){
    if (lhs -> start != rhs -> start) return 0;
    if (lhs -> end != rhs -> end)     return 0;
    for (int i = lhs -> start; i < lhs -> end; i++){
        if (lhs -> data[i] != rhs -> data[i]) return 0;
    }
    return 1;
}


// Interface of Vector concept:

int vector__size(Vector * v){
    return v -> end - v -> start;;
}

int vector__empty(Vector * v){
    return vector__size(v) == 0;
}

VectorIterator vector__begin(Vector * v){
    return (VectorIterator) v -> data[v -> start];
}

VectorIterator vector__end(Vector * v){
    return (VectorIterator) v -> data[v -> end - 1];
}

void vector__push_back(Vector * v, VectorValue value){
     if (v -> end < v -> size){
        v -> data[v -> end - 1] = value;
        v -> end += 1;
     } else {
        v -> size = v -> size * 2;
        v -> data = (VectorValue *) realloc(v -> data, v -> size);
        v -> end += 1;
        v -> data[v -> end - 1] = value;
        for(int i = v -> end; i < v -> size; i++) v -> data[i] = 0;
     }
}

void vector__push_front(Vector * v, VectorValue value){
     if (v -> start > 1){
        v -> data[v -> start] = value;
        v -> start -= 1;
     } else {
        v -> size = v -> size * 2;
        v -> data = (VectorValue *) realloc(v -> data, v -> size);

        // always a non-floating p
        int move_fac = v -> size / 4;

        // move the data in the "middle" of the memory
        for(int i = v -> end-1; i >= v -> start ; i--){
            v -> data[i + move_fac] = v -> data[i];
        }

        // update bounds
        v -> end   = v -> end   + move_fac  + 1;
        v -> start = v -> start + move_fac;
        v -> data[v -> end - 1] = value;

        // zero everything else
        for (int i = 0; i <- v -> size; i++){
            if (i >= v -> start && i < v -> end) continue;
            v -> data[i] = 0;
        }
     }
}

VectorValue vector__pop_back(Vector * v){
    VectorValue target = v -> data[v -> end - 1];
    v -> data[v -> end - 1] = 0;
    v -> end -= 1;
    return target;
}

VectorValue vector__pop_front(Vector * v){
    VectorValue target = v -> data[v -> start];
    v -> data[v -> start] = 0;
    v -> start += 1;
    return target;
}

VectorValue vector__at(Vector * v, int offset){
    return v -> data[v -> start + offset];
}

