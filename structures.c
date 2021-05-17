//
//  main.c
//  InsertIntoStructs
//
//  Created by Filip Vabroušek on 17.05.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>





typedef struct Item {
    char name[255];
    struct Item * left;
    struct Item * right;
} Item;


typedef struct _Structure {
    Item **items;
} Structure;



void insert(char name [], Structure * structure){
    if (structure == NULL){
        return;
    }
    
    
    Item *newNode = malloc(sizeof(Item));
           strcpy(newNode->name, "Test");
           newNode->left = NULL;
           newNode->right = NULL;

    
   
    structure->items[0] = newNode;
    
    printf("NAME IS %s", structure->items[0]->name);    
    
}

int main(int argc, const char * argv[]) {
    Structure structure;
    int size = 3;
    
    structure.items = malloc(size * sizeof(Item**));
    
    for (size_t i = 0; i < size; i++){
        structure.items[i] = NULL;
    }
    
    
    insert("Test", &structure);

    return 0;
}
