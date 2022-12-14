-------------------------------------------------------------------------Kuyruklar (Queues)-------------------------------------------------------------------------------//

#include <stdio.h> 
#include <string.h>  
#include <stdlib.h> 
#include <conio.h> 
#include <ctype.h> 
#include <stdbool.h>

#define SIZE 100  
#define STACK_SIZE 100  
#define QUEUE_SIZE 100  

struct node {  
    int data;  
    struct node *next;  
};

typedef struct {  
    struct node *top;  
    int cnt;  
}stack;  

typedef struct {  
    int cnt;  
    struct node *front;  
    struct node *rear;  
}queue;

void initialize_stack(stack *stk) {  
    stk -> top = NULL;  
    stk -> cnt = 0;  
}

void initialize_queue(queue *q) {  
    q -> cnt = 0;   
    q -> front = q -> rear = NULL;  
} 

bool isEmpty_stack(stack *stk) {  
    return(stk -> cnt == 0);  
}  

bool isFull_stack(stack *stk) {  
    return(stk -> cnt == STACK_SIZE);  
}

void push(stack *stk, int c) {  
    if(!isFull_stack(stk)) {  
        struct node *temp = (struct node *)malloc(sizeof(struct node));  
        temp -> data = c;  
        temp -> next = stk -> top;  
        stk -> top = temp;  
        stk -> cnt++;  
    } 
    else  
        printf("Stack dolu\n");  
}  
int pop(stack *stk) {  
    if(!isEmpty_stack(stk)) {  
        struct node *temp = stk -> top;  
        stk -> top = stk -> top -> next;  
        int x = temp -> data;  
        free(temp);  
        stk -> cnt--;  
        return x;  
    }  
}

int isEmpty_queue(queue *q) {  
    return(q -> cnt == 0);  
}  

int isFull_queue(queue *q) {  
    return(q -> cnt == QUEUE_SIZE);  
}  

void enqueue(queue *q, int x) {  
    if(!isFull_queue(q)) {  
        struct node *temp = (struct node *)malloc(sizeof(struct node));  
        temp -> next = NULL;  
        temp -> data = x;  
        if(isEmpty_queue(q))  
            q -> front = q -> rear = temp;  
    else
        q -> rear = q -> rear -> next = temp;  
    q -> cnt ++;  
    }  
}

int dequeue(queue *q) {  
    if(!isEmpty_queue(q)) {  
        struct node *temp = q -> front;  
        int x = temp -> data;  
        q -> front = temp -> next;  
        free(temp);  
        q -> cnt--;  
        return x;  
    }  
}

int main() {  
    char ifade[SIZE];  
    queue q;  
    stack s;  
    int i = 0, mismatches = 0;  
    initialize_stack(&s);  
    initialize_queue(&q);  
    printf("Bir ifade giriniz...\n");  
    gets(ifade);  
    for(i = 0; i != strlen(ifade); i++) {  
        if(isalpha(ifade[i])) {  
            enqueue(&q, tolower(ifade[i]));  
            push(&s, tolower(ifade[i]));  
        }  
    }  
    while(!isEmpty_queue(&q)) {  
        if(pop(&s) != dequeue(&q)) {  
        mismatches = 1;  
        break;  
        }  
    }  
    if(mismatches == 1)  
        printf("Girdiginiz ifade palindrom degildir!\n");  
    else  
        printf("Girdiginiz ifade bir palindromdur!\n");  
}

//------------------------------------------------------------------------- A??A??LAR(Trees) -------------------------------------------------------------------------------//

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

typedef struct node BTREE;

BTREE *new_node(int key)
{
    BTREE *p = (BTREE *)malloc(sizeof(BTREE));
    p -> data = key;
    p -> left = NULL;
    p -> right = NULL;
    return(p);
}

BTREE *insert(BTREE *root, int data) // a??a??a eleman ekleme
{
    if(root != NULL) // ilk eleman bo?? de??ilse
    {
        if(data < root -> data) // eklenecek eleman??n k??????k veya b??y??k oldu??u kontrol edilir.
            root -> left = insert(root -> left, data); // k??????kse sol tarafa
        else
            root -> right = insert(root -> right, data); // b??y??kse sa?? tarafa
    }
    else
        root = new_node(data); // eleman yoksa d??md??z eklenir
    return(root);
}

// preorder: ??lk ??nce k??k yaz??l??r, devam??nda sol tarafa ge??ilir, e??er solda eleman yoksa sa?? tarafa ge??ilir.
void preorder(BTREE *root) // preorder s??ralama
{
    if(root != NULL)
    {
        printf("%d ", root -> data);
        preorder(root -> left);
        preorder(root -> right);
    }
}

// inorder: sol taraf yaz??l??r sonra k??k sonra sa?? taraf
void inorder(BTREE *root) // postorder s??ralama
{
    if(root != NULL)
    {
        inorder(root -> left);
        printf("%d ", root -> data);
        inorder(root -> right);
    }
}

// postorder: sol taraf sonra sa?? taraf sonra k??k 
void postorder(BTREE *root) // postorder s??ralama
{
    if(root != NULL)
    {
        postorder(root -> left);
        postorder(root -> right);
        printf("%d ",root -> data);
    }
}