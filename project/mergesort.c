
// C code for linked list merged sort 
#include <stdio.h> 
#include <stdlib.h> 
  

struct Node { 
    int data;
    int no; 
    struct Node* next; 
}; 
  
struct Node* SortedMerge(struct Node* a, struct Node* b); 
void FrontBackSplit(struct Node* source, 
                    struct Node** frontRef, struct Node** backRef); 
  
void MergeSort(struct Node** headRef) 
{ 
    struct Node* head = *headRef; 
    struct Node* a; 
    struct Node* b; 
  
  
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    
    FrontBackSplit(head, &a, &b); 
  
   
    MergeSort(&a); 
    MergeSort(&b); 
  
    
    *headRef = SortedMerge(a, b); 
} 
  

struct Node* SortedMerge(struct Node* a, struct Node* b) 
{ 
    struct Node* result = NULL; 
  
  
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
  
    
    if (a->data <= b->data) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return (result); 
} 
  
void FrontBackSplit(struct Node* source, 
                    struct Node** frontRef, struct Node** backRef) 
{ 
    struct Node* fast; 
    struct Node* slow; 
    slow = source; 
    fast = source->next; 
  
    
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 
  

void printList(struct Node* node) 
{ 
    while (node != NULL) { 
        printf("%d ", node->data); 
	printf(" %c ",node->no);
        node = node->next; 
	printf("\n");
    } 
} 
  

void push(struct Node** head_ref, int new_data,char new) 
{
    
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
  
   
    new_node->data = new_data; 
    new_node->no=new;
  
   
    new_node->next = (*head_ref); 
  
   
    (*head_ref) = new_node; 
} 
  

int main() 
{ 
    
    struct Node* res = NULL; 
    struct Node* a = NULL;
    int i;char j; 
    struct Node* ptr=a;
	for(int k=0;k<5;k++){
    printf("\nenter the node data and letter :");
    scanf("%d %c",&i,&j);
	push(&a,i,j);
	}
    
  
    MergeSort(&a); 
  
    printf("Sorted Linked List is: \n"); 
    printList(a); 
  
    getchar(); 
    return 0; 
} 

