
  
    heap = Heap()
    heap.ct = 0;
    heap.max = CONSTANT
    heap.arr = malloc(4 * sizeof(Insert_type));
    
    if (heap.array == NULL){
       printf("Not enough memeory");
    }


void ADDLTInHeap(pointer * , DT data){
    
    if (heap == NULL){
        return;
    }
    
    heap->array[Heap_Count(*heap)] = data;
    heap->count++;
}

void ADDLTT(tHeap *heap, DT data) {
    
    heap->array[Heap_Count(*heap)] = data;
    heap->count++;
    
    int compare = strcmp(&heap->array[0]->prop,&heap->array[1]->prop);
    if(compare > 0){
        Swap(heap, 0, 1);
    }
}


void TwoOrMore(tHeap *heap, Data_t insertData){
    
    if (heap == NULL){
        return;
    }
    
    if(Heap_Count(*heap) == heap->maxItems){
        heap->maxItems *=2;
        heap->array = REAL(heap->array, heap->maxItems * sizeof (Data_t));
    }
    heap->array[Heap_Count(*heap)] = insertData;
    heap->count++;
    
    int node = Heap_Count(*heap)/2;
    int cmp;
    
    for(int i = node; i > 0; i--){
        if(Heap_Count(*heap) % 2 == 0 && i == node){
              cmp = Data_Cmp(&heap->array[i-1],&heap->array[(i*2)-1]);
              if(cmp > 0){
                  Heap_Swap(heap, i-1, (i*2)-1);
              }
        } else{
            cmp = Data_Cmp(&heap->array[i-1],&heap->array[(i*2)-1]);
            if(cmp > 0){
                Heap_Swap(heap, i-1, (i*2)-1);
            }
            
            cmp = Data_Cmp(&heap->array[i-1],&heap->array[i*2]);
            if(cmp > 0){
                Heap_Swap(heap, i-1, i*2);
            }
        }

    }
    cmp = Data_Cmp(&heap->array[0], &heap->array[1]);
    if(cmp > 0){
       Heap_Swap(heap, 0, 1);
    }
    cmp = Data_Cmp(&heap->array[0], &heap->array[2]);
    if(cmp > 0){
       Heap_Swap(heap, 0, 2);
    }
}


bool Heap_Insert(tHeap *heap, Data_t insertData){ // TEST
    if (heap == NULL){
        return false;
    }
    
    if (Heap_Count(*heap) < 1){
        insertLessThanOne(heap, insertData);
    } else if (Heap_Count(*heap) < 2){
        insertLessThanTwo(heap, insertData);
    } else {
        TwoOrMore(heap, insertData);
    }
    
    return true;
}
