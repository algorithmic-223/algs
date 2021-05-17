/**
 * @file       functions.c
 * @author     Horak
 * @date       2019.6
 * @brief      Implementation of function.h header file
 * ****************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

#include "vector.h"
#include "mymalloc.h"






Vector = Vector()



Vector_t *Vector_Create(uint64_t initial_size, uint32_t alloc_step) {
    Vector_t* vector = (Vector_t*)myMalloc(sizeof(Vector_t));
    
    if (vector == NULL){
        return NULL;
    }
    
    vector->size = initial_size;
    vector->free_cells = initial_size;
    vector->alloc_step = alloc_step;
    
    
    vector->items = (uint64_t*)myMalloc(initial_size * sizeof(uint64_t));
    if (vector->items == NULL){
        myFree(vector);
        return NULL;
    }
    
    if (initial_size * sizeof(uint64_t) > UINT32_MAX || alloc_step * sizeof(uint32_t) > UINT32_MAX){
        return NULL;
    }
    
    return vector;
}




Vector_t *Vector_Copy(const Vector_t *const original) {
    if (original == NULL) {
        return NULL;
        
    }

    Vector_t* copy = myMalloc(sizeof (Vector_t));
    if (copy == NULL) {
        return NULL;
    }

    
    uint64_t firstItemSize = sizeof (original->items[0]);
   
    copy->items = myMalloc(original->size * firstItemSize);
    if (copy->items == NULL) {
        myFree(copy);
        return NULL;
    }

    

    for (uint64_t i = 0; i < original->size - original->free_cells; i++) {
        copy->items[i] = original->items[i];
    }
    copy->alloc_step = original->alloc_step;
    copy->free_cells = original->free_cells;
    copy->size = original->size;
    return copy;
}

void Vector_Clear(Vector_t *const vector) { // Should be OK
    if (vector == NULL) {
        return;
    }
    
    myFree(vector->items);
    vector->items = NULL;
    vector->size = 0;
    vector->free_cells = 0;
}




uint64_t Vector_Length(const Vector_t *const vector) {
    if (vector == NULL) {
        return UINT64_MAX;
    }
    
    return vector->size - vector->free_cells;
}

bool Vector_At(const  Vector_t *const vector, uint64_t position, uint64_t *const value) {
    if (vector == NULL || value == NULL){
        return false;
    }

    uint64_t len = vector->size - vector->free_cells;
    
    if (position > len){ // >=
        return false;
    }
    
    
    *value = vector->items[position];
    return true;
}



void Vector_Append(Vector_t *const vector, uint64_t value) {
    if (vector == NULL) {
        return;
    }
    
    uint64_t step = vector->alloc_step;
    uint64_t vectorSize = vector->size - vector->free_cells;
    uint64_t stepSum = (vector->size + vector->alloc_step);
    
    if (vector->free_cells == 0) {
        uint64_t newSize = sizeof (vector->items[0]) * stepSum;
        uint64_t *newPointer = myRealloc(vector->items, newSize);
        
        if (newPointer == NULL) {
            myFree(newPointer);
            return;
        }

        vector->items = newPointer;
        vector->size += step;
        vector->free_cells = step;
    }

    vector->items[vectorSize] = value;
    vector->free_cells--;
}










bool Vector_Remove(Vector_t *const vector, uint64_t position) {
  
    
    if (vector == NULL) {
        return false;
    }
    
    uint64_t len = vector->size - vector->free_cells;
    
    if (position >= len){
        return false;
    }
    
   
   
    for (unsigned i = position; i < len; i++) {
        vector->items[i] = vector->items[i + 1];
    }
    
    vector->free_cells++;
    return true;
}



bool Vector_Contains(const Vector_t *const vector, uint64_t value) {
    bool contains = false;
    if (vector == NULL || vector->size == 0) {
        return false;
    };
  
   
        for (unsigned i = 0; i < Vector_Length(vector); i++){
            if (vector->items[i] == value) {
                contains = true;
            }
        }

    
    return contains;
}




uint64_t Vector_IndexOf(const Vector_t *const vector, uint64_t value, uint64_t from) {
    
    bool goodConditions = vector != NULL && from <= vector->size-vector->free_cells;

    if (goodConditions){
        uint64_t totalSize = vector->size;
        uint64_t free = vector->free_cells;
        uint64_t vectorSize = totalSize - free;
        
        for (unsigned i = from; i < vectorSize; i++){
            if (vector->items[i] == value){
                return i;
            }
        }
    }
    
    return UINT64_MAX;
}


void Vector_Fill(const Vector_t *const vector, uint64_t value, uint64_t start_position, uint64_t end_position) {
    
    
    
    if (vector == NULL || start_position >= end_position){
        return;
    }
    
    uint64_t totalSize = vector->size;
    uint64_t free = vector->free_cells;
    uint64_t vectorSize = totalSize - free;
    bool allowLoop = end_position < vectorSize;
    
    if (end_position >= vectorSize) {
        for (uint64_t i = start_position; i <= vectorSize; i++) {
            vector->items[i] = value;
        }
    }
    
    if (start_position < vectorSize && allowLoop) {
        for (uint64_t i = start_position; i <= end_position; i++) {
            vector->items[i] = value;
        }
    }
    
    
}



void Vector_Destroy(Vector_t **const vector) {
    if (vector == NULL){
        return;
    }
   
    myFree((*vector)->items);
    myFree(*vector);
    *vector = NULL;
}


/*if (vector != NULL && start_position > end_position) {
    for (uint64_t i = start_position; i < end_position; i++){
        vector->items[i] = value;
    }
}*/
