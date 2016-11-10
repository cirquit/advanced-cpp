#include <stdlib.h>
#include "deque.h"

// Interface of Standard concept:
Deque * deque__new(){
    Deque * target = (Deque *) malloc(sizeof(Deque));
    target -> sizeFront = 0;
    target -> sizeBack  = 0;
    target -> front     = nullptr;
    target -> back      = nullptr;
    return target;
}

Deque * deque__copy(Deque * other){
    return deque__assign(deque__new(), other);
}

void deque__delete(Deque * d){
    free(d -> front);
    free(d -> back);
    free(d);
}

Deque * deque__assign(Deque * lhs, Deque * rhs){
    if (lhs -> sizeFront != rhs -> sizeFront){
        lhs -> sizeFront = rhs -> sizeFront;
        lhs -> front = (DequeValue *) realloc(lhs -> front, lhs -> sizeFront);
    }
    if (lhs -> sizeBack != rhs -> sizeBack){
        lhs -> sizeBack = rhs -> sizeBack;
        lhs -> back = (DequeValue *) realloc(lhs -> back, lhs -> sizeBack);
    }
    for(int i = 0; i < lhs -> sizeBack; i++) lhs -> back[i] = rhs -> back[i];
    for(int i = 0; i < lhs -> sizeFront; i++) lhs -> front[i] = rhs -> front[i];
    return lhs;
}

int deque__equals(Deque * lhs, Deque * rhs){
    if (lhs -> sizeFront != rhs -> sizeFront) return 0;
    if (lhs -> sizeBack  != rhs -> sizeBack)  return 0;

    for (int i = 0; i < lhs -> sizeBack; i++){
        if (lhs -> back[i] != rhs -> back[i]) return 0;
    }

    for (int i = 0; i < lhs -> sizeFront; i++){
        if (lhs -> front[i] != rhs -> front[i]) return 0;
    }

    return 1;
}

// inplace O(n) with xorswap
Deque * deque__reverse(Deque * d){
  int sizeMax = d -> sizeBack > d -> sizeFront ? d -> sizeBack : d -> sizeFront;
  d -> front = (DequeValue *) realloc(d -> front, sizeMax);
  d -> back  = (DequeValue *) realloc(d -> back, sizeMax);

  for (int i = 0; i < sizeMax; i++){
      d -> front[i] ^= d -> back[i];
      d -> back[i]  ^= d -> front[i];
      d -> front[i] ^= d -> back[i];
  }
  d -> sizeFront ^= d -> sizeBack;
  d -> sizeBack  ^= d -> sizeFront;
  d -> sizeFront ^= d -> sizeBack;
  return d;
}



// Interface of Deque concept:

int deque__size(Deque * d){
    return d -> sizeFront + d -> sizeBack;
}

int deque__empty(Deque * d){
    return deque__size(d) == 0;
}

void deque__push_back(Deque * d, DequeValue value){
    d -> sizeBack += 1;
    d -> back = (DequeValue *) realloc(d -> back, d -> sizeBack);
    d -> back[d -> sizeBack - 1] = value;
}

void deque__push_front(Deque * d, DequeValue value){
    d -> sizeFront += 1;
    d -> front = (DequeValue *) realloc(d -> front, d -> sizeFront);
    d -> front[d -> sizeFront - 1] = value;
}


/*
 * If the back is empty, one could split the front in two parts and fill
 * the back with the first part so the next access would be O(1)
 * */
DequeValue deque__pop_back(Deque * d){

    DequeValue res = 0;

    if (d -> sizeBack != 0){
        res = d -> back[d -> sizeBack - 1];
        d -> sizeBack -= 1;
        d -> back = (DequeValue *) realloc(d -> back, d -> sizeBack);
    } else {
        res = d -> front[0];
        for(int i = 0; i < d -> sizeFront-1; i++){
            d -> front[i] = d -> front[i+1];
        }
        d -> sizeFront -= 1;
        d -> front = (DequeValue *) realloc(d -> front, d -> sizeFront);
    }

    return res;
}

/*
 * If the front is empty, one could split the back in two parts and fill
 * the front with the first part so the next access would be O(1)
 * */
DequeValue deque__pop_front(Deque * d){

    DequeValue res = 0;

    if (d -> sizeFront != 0){
        res = d -> front[d -> sizeFront - 1];
        d -> sizeFront -= 1;
        d -> front = (DequeValue *) realloc(d -> front, d -> sizeFront);
    } else {
        res = d -> back[0];
        for(int i = 0; i < d -> sizeBack-1; i++){
            d -> back[i] = d -> back[i+1];
        }
        d -> sizeBack -= 1;
        d -> back = (DequeValue *) realloc(d -> back, d -> sizeBack);
    }

    return res;
}
















