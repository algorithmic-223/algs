#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[255];
    struct Node * left;
    struct Node * right;
} Node;


typedef struct _Tree {
    Node *root;
    unsigned int count;
} Tree;

int main(int argc, const char * argv[]) {
    Tree tree;
    tree.root = NULL;
    tree.count = 0;
    
    if (tree.count == 0){
        Node *node = malloc(sizeof(Node));
        strcpy(node->name, "Filip");
        node->left = NULL;
        node->right = NULL;
        tree.root = node;
        tree.count++;
    }
    
    Node *node = malloc(sizeof(Node));
    strcpy(node->name, "Filip");
    
    
    Node* next = tree.root;
    Node* last = NULL;
    int cmp;
    
    while(next != NULL){
        cmp = strcmp(&next->name, node->name);
        
        if (cmp == 0){
            printf("NO INSERTION");
          //  return false;
        }
        
        if (cmp < 0){
            last = next;
            next = next->right;
        } else if (cmp > 0) {
            last = next;
            next = next->left;
        }
    }
    
    Node *nodeA = malloc(sizeof(Node));
    
    strcpy(node->name, "Filip");
    node->left = NULL;
    node->right = NULL;
    
    cmp = strcmp(&last->name, &node->name);
    
    if (cmp > 0){
        last->left = node;
    } else {
        last->right = node;
    }
    
    
    tree.count++;
    
    
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
