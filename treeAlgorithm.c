#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data; //node will store an integer
    struct node *right_child; // right child
    struct node *left_child; // left child
};

struct node* search(struct node *root, int x)
{
    if(root==NULL || root->data==x) //if root->data is x then the element is found
        return root;
    else if(x>root->data) // x is greater, so we will search the right subtree
        return search(root->right_child, x);
    else //x is smaller than the data, so we will search the left subtree
        return search(root->left_child,x);
}

//function to find the minimum value in a node
struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) // node with minimum value will have no left child
        return find_minimum(root->left_child); // left most element will be minimum
    return root;
}

//function to create a node
struct node* new_node(int x)
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node *root, int x)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(x);
    else if(x>root->data) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child,x);
    return root;
}

// funnction to delete a node
struct node* delete(struct node *root, int x)
{
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (x>root->data)
        root->right_child = delete(root->right_child, x);
    else if(x<root->data)
        root->left_child = delete(root->left_child, x);
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {
            struct node *temp;
            if(root->left_child==NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            struct node *temp = find_minimum(root->right_child);
            root->data = temp->data;
            root->right_child = delete(root->right_child, temp->data);
        }
    }
    return root;
}

void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %d ", root->data); // printing data at root
        inorder(root->right_child);// visiting right child
    }
}

int main()
{
    /*
                   20
                 /    \
                /      \
               5       30
             /   \     /\
            /     \   /  \
           1      15 25  40
                /          \
               /            \
              9             45
            /   \          /
           /     \        /
          7      12      42
    */
    struct node *root;
    root = new_node(20);
    insert(root,5);
    insert(root,1);
    insert(root,15);
    insert(root,9);
    insert(root,7);
    insert(root,12);
    insert(root,30);
    insert(root,25);
    insert(root,40);
    insert(root, 45);
    insert(root, 42);

    inorder(root);
    printf("\n");

    root = delete(root, 1);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25   40
                /           \
               /             \
              9              45
            /   \           /
           /     \         /
          7      12       42
    */

    root = delete(root, 40);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  45
                 /       /
                /       /
               9       42
             /   \
            /     \
           7      12
    */

    root = delete(root, 45);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  42
                 /
                /
               9
             /   \
            /     \
           7      12
    */
    root = delete(root, 9);
    inorder(root);
    /*
                   20
                 /    \
                /      \
               5       30
                 \     /\
                  \   /  \
                  15 25  42
                 /
                /
               12
             /
            /
           7
    */
    printf("\n");

    return 0;
}













































#include "tree.h"
#include "mymalloc.h"

void print_postorder(TreeNode* node, TreeNodeProc proc) {
    if (node != NULL){
        print_postorder(node->left, proc);
        print_postorder(node->right, proc);
        (*proc)(node);
    } else {
        return;
    }
}

/**
 * @brief print_inorder Recursive function that calls itself with the left node
 * first, then processes the current node with the function that is passed in
 * argument and then it calls itself with the right node
 * @param node  Pointer at node
 * @param proc  function that is called by each node
 */
void print_inorder(TreeNode* node, TreeNodeProc proc) {
    if (node != NULL){
        print_inorder(node->left, proc);
        (*proc)(node);
        print_inorder(node->right, proc);
        
    } else {
        return;
    }
}

/**
 * @brief print_preorder    Recursive function that processes node first, then
 * it calls itself with the left and then right node
 * @param node  Pointer at node
 * @param proc  function that is called by each node
 */
void print_preorder(TreeNode* node, TreeNodeProc proc) {
    if (node != NULL){
        (*proc)(node);
        print_preorder(node->left, proc);
        print_preorder(node->right, proc);
       
    } else {
        return;
    }
}


bool Tree_Init(Tree* const root) {
    if (root == NULL){
        return false;
    }
    
    root->root = NULL;
    root->itemsCount = 0;
    return true;
}


void Tree_Clear_Recursive(TreeNode* const node){
    if (node != NULL){
        Tree_Clear_Recursive(node->left);
        Tree_Clear_Recursive(node->right);
        myFree(node);
    }
    
    
 
    
}



void Tree_Clear(Tree* const root) {
    if (root == NULL){
        return;
    }
    
    
  
    Tree_Clear_Recursive(root->root);
    root->itemsCount = 0;
    root->root = NULL;
   
}



bool Tree_Insert(Tree* const root, const Data_t data) {
  
    if (root == NULL){
        return false;
    }
    
    if (root->itemsCount == 0){
        TreeNode *node = myMalloc(sizeof(TreeNode));
        
        if (node == NULL){
            return false;
        }
        
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        root->root = node;
        root->itemsCount++;
        return true;
    } else {
        TreeNode* next = root->root;
        TreeNode* last = NULL;
        int cmp;
        
        while(next != NULL){
            cmp = Data_Cmp(&next->data, &data);
            
            if (cmp == 0){
                return false;
            }
            
            if (cmp < 0){
                last = next;
                next = next->right;
            } else {
                last = next;
                next = next->left;
            }
        }
        
        TreeNode *node = myMalloc(sizeof(TreeNode));
        
        if (node == NULL){
            return false;
        }
        
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        
        cmp = Data_Cmp(&last->data, &data);
        
        if (cmp > 0){
            last->left = node;
        } else {
            last->right = node;
        }
        
        
        root->itemsCount++;
        return true;
        
        
    }
    
    return false;
}

void Tree_Delete(Tree* const root, const Data_t data) {
    if(root == NULL) {
        return;
    }
    
    TreeNode* node = root->root;
    
    if (node == NULL){
        return;
    }
    
    
    TreeNode* delete = NULL;
    TreeNode** last = NULL;
    int cmp = 0;
    
    
    while(node != NULL){
        cmp = Data_Cmp(&node->data, &data);
        
        if (cmp < 0){
            last = &node->right;
            node = node->right;
        } else if (cmp > 0){
            last = &node->left;
            node = node->left;
        } else {
            
            
            
                        if(node->left == NULL && node->right == NULL){
                            if(last!=NULL){*last = NULL;}
                            myFree(node);
                        }
                     
                        else if(node->left != NULL && node->right != NULL){
                            TreeNode* rightmost = node->left;
                            TreeNode* pred = NULL;
                            while(rightmost->right != NULL){
                                pred = rightmost;
                                rightmost = rightmost->right;
                            }
                            node->data = rightmost->data;
                            if(pred){
                                pred->right = rightmost->left;
                            }
                            else {
                                node->left = rightmost->left;
                            }
                            myFree(rightmost);
                        } else{
                            if(node->left != NULL){
                                delete = node->left;
                                node->data = node->left->data;
                                node->right = node->left->right;
                                node->left = node->left->left;
                                myFree(delete);
                            } else{
                                delete = node->right;
                                node->data = node->right->data;
                                node->left = node->right->left;
                                node->right = node->right->right;
                                myFree(delete);
                            }
                        }
                        root->itemsCount--;
                        return;
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
        }
            
            
            
        }
    }
    



const Data_t* Tree_Get_Data(const TreeNode* const node) {
    if (node == NULL){
        return NULL;
    }
    
    return &node->data;
}






TreeNode *Tree_Find_Node(Tree root, const Data_t data) {
    TreeNode* next = root.root;
    int compare;
    
    if (next == NULL){
        return NULL;
    }
    
    
    while (next != NULL){
        compare = Data_Cmp(&data, &next->data);
        
        if (compare > 0){
            next = next->left;
            if (next == NULL){
                return NULL;
            }
            
            compare = Data_Cmp(&next->data, &data);
        } else if (compare < 0){
            next = next->right;
            if (next == NULL){
                return NULL;
                
            }
            compare = Data_Cmp(&next->data, &data);
        } else {
            break;
        }
    }
    
    
    if (next == NULL){
        return NULL;
    } else {
        return next;
    }
    
}

size_t Tree_Get_Count(Tree root) {
    return root.itemsCount;
}




void Tree_Process(Tree root, TreeNodeProc proc, TreeProcessMode mode) {
    switch(mode){
        case procPREORDER:
            print_preorder(root.root, proc);
            break;
        case procPOSTORDER:
            print_postorder(root.root, proc);
            break;
        case procINORDER:
            print_inorder(root.root, proc);
            break;
    }
}



void Tree_Print(TreeNode* node, TreeNode* previous, int spaces) {
 
    if (node == NULL || previous == NULL){
        return;
    }
    
    spaces += 6;
    Tree_Print(node->right, node, spaces);
    printf("\n");
    
    for (int i = 6; i < spaces; i++){
        printf(" ");
    }
    
    if (previous == node){
        printf("---%s", node->data.name);
    } else if (node == previous->left){
        printf("|\n");
        
        for (int i = 6; i < spaces; i++){
            printf(" ");
        }
        
        printf("---%s", node->data.name);
        
        
    } else {
        printf("---%s", node->data.name);
        for (int i = 6; i < spaces; i++){
            printf(" ");
            printf("|");
        }
    }
    
    Tree_Print(node->left, node, spaces);
    
}
