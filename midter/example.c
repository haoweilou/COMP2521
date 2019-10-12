#include <stdio.h>
#include <stdlib.h> 

typedef struct node *Node;
struct node {
    int val;
    Node next;
    Node prev;
};

typedef struct list *List;
struct list {
    Node first;
    Node last;
};

// todo
void deleteValue (List L, int val);
void reverse (List L);
int isPalindrome (List L);
void removeDuplicates(List L);
List risingConcat(List L1);
// completed
List createListFromArray (int a[], int size);
void printList (List L);
List newList (void);
Node newNode (int val);
void freeList (List L);

int main (int argc, char * argv[]) {

    int a[6] = {1,2,3,4,5,1};
    List L = createListFromArray(a, 6);
    //printList(L);
    deleteValue(L,1);
    printList(L);
    reverse(L);
    printList(L);
    // Add your own test cases
    freeList(L);
    return 0;
}

// functions that you may want to try

// deletes all instances of val from the list 
// think about the cases you need to cover
// e.g.
// List: 1 1 3 1 1 4 1 val: 1 ==> 3 4 
// List: 3 3 3 val: 1 ==> 3 3 3  
// Note: modifies the list, so does not return anything
void deleteValue (List L, int val) {
    Node curr = L->first;
    while ( curr != NULL)
    {
        if(val == curr->val){
            if (curr == L->first)
            {
                L->first = curr->next;
                L->first->prev = NULL;
                free(curr);
                curr = L->first;
            }
            else if (curr == L->last)
            {
                L->last = curr->prev;
                L->last->next = NULL;
                free(curr);
                curr = L->last;
            }
            else
            {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                Node temp = curr->next;
                free(curr);
                curr = temp;
            }
        }
        curr = curr->next;
    }
    
}

// reverse a list
// see if you can do this recursively 
// Note: modifies the list, so does not return anything
void reverse (List L) {
    Node curr = L->last;
    Node last = NULL;
    while(curr != NULL){
        curr->next = curr->prev;
        curr->prev = last;
        last = curr;
        curr = curr->prev;
    }
}

// is linked list a palindrome?
// return 0 if true
// return -1 if false
int isPalindrome (List L) {
    return -1;
}
//Remove any duplicate elements from the list
void removeDuplicates(List L) {
}
/* 
    Create a new list by that copies L1, except that
    each rising slope has been replaced by a single node that
    contains the sum total of the rising slope.
    
    A rising slope is defined as a sequence of at least 3 nodes, 
    where node1.value < node2.value < node3.value ...
    
    1->2->3->4->NULL is a rising slope and needs to be replaced by a single node 10->NULL
    
    e.g. 
    List = 1->2->3->2->1->5->6->7->3->9->1->NULL
    Returns 6->2->19->3->9->1->NULL
*/
List risingConcat(List L1) {
    return 0;
}

List createListFromArray (int a[], int size) {
    List L = newList();
    if (size == 0) return L;
    L->first = L->last = newNode(a[0]);
    Node curr = L->first;
    for (int i = 1; i < size; i++) {
        curr->next = newNode (a[i]);
        curr->next->prev = curr;
        curr = curr->next;
        L->last = curr;
    }
    return L;
}

void printList (List L) {
    Node curr = L->first;
    while (curr != NULL) {
        printf ("%d -> ", curr->val);
        curr = curr->next;
    }
    printf ("NULL\n");
}

List newList (void) {
    List l = malloc (sizeof (struct list));
    l->first = NULL;
    l->last = NULL;
    return l;
}

Node newNode (int val) {
    Node n = malloc (sizeof (struct node));
    n->val = val;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void freeList (List L) {
    Node curr = L->first;
    while (curr != NULL) {
        Node tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(L);
}
