#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} NodeT;

NodeT *search(NodeT *head, int givenKey) {
    NodeT* cur=head;
    while(cur!=NULL){
        if (cur->key==givenKey)
            break;
        cur=cur->next;
    }
    return cur;
}

void print_list(NodeT *head){
    NodeT* cur=head;
    printf("List:");
    while(cur!=NULL){
        printf("%d ", cur->key);
        cur=cur->next;
    }
    printf("\n");
}

void insert_first(NodeT **head, NodeT **tail, int givenKey) {
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    node->key=givenKey;
    node->next=*head;
    *head=node;
    if (node->next==NULL)
        *tail=node;
}

void insert_last(NodeT **head, NodeT **tail, int givenKey) {
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    node->key=givenKey;
    if (*tail==NULL){
        *head=node;
        *tail=node;
    }
    else{
        (*tail)->next=node;
        *tail=node;
        node->next=NULL;
    }
}

void insert_after_key(NodeT** head, NodeT** tail, int afterKey, int givenKey){
    NodeT* node = *head;
    NodeT* newnode = (NodeT*)malloc(sizeof(NodeT));
    while(node->key!=afterKey)
        node=node->next;
    newnode->key=givenKey;
    newnode->next=node->next;
    node->next=newnode;
}

void delete_first(NodeT** head, NodeT** tail){
    if (*head==NULL) return;
    NodeT* n = *head;
    *head=(*head)->next;
    if (*head==NULL)
        *tail=NULL;
    free(n);
}

void delete_last(NodeT** head, NodeT** tail){
    if (*head==NULL) return;
    if (*head==*tail){
        *head=NULL;
        *tail=NULL;
        return;
    }
    NodeT* node = *head;
    while(node->next!=*tail)
        node=node->next;
    *tail=node;
    free((*tail)->next);
    (*tail)->next=NULL;
}

void delete_key(NodeT** first, NodeT** last, int givenKey){
    if (*first==NULL) return;
    if ((*first)->key==givenKey){
            if (*first==*last)
                *last=NULL;
            *first=NULL;
            return;
    }
    NodeT* node = *first;
    NodeT* temp;
    while(node->next!=NULL){
        if (node->next->key==givenKey)
            break;
        node=node->next;
    }
    if (node!=NULL){
        temp=node->next;
        node->next=node->next->next;
    }
    free(temp);
}

void flip_list(NodeT** first, NodeT** last){
    if (*first==NULL) return;
    if (*first==*last) return;
    NodeT* prev = NULL;
    NodeT* nod = *first;
    NodeT* next = NULL;
    while(nod!=NULL){
        next = nod->next;
        nod->next = prev;
        prev = nod;
        nod = next;
    }
    *first=prev;
}

int main() {
    NodeT *first = NULL;
    NodeT *last  = NULL;

    insert_first(&first, &last, 1);
    insert_first(&first, &last, 3);
    insert_last(&first, &last, 15);
    insert_last(&first, &last, 18);
    insert_last(&first, &last, 33);
    insert_first(&first, &last, 51);
    insert_after_key(&first, &last, 51, 55);
    print_list(first);
    delete_first(&first, &last);
    print_list(first);
    delete_last(&first, &last);
    print_list(first);
    delete_key(&first, &last, 15);
    if (search(first, 5)==NULL)
        printf("Element 5 not found\n");
    else printf("Element 5 found\n");
    print_list(first);
    printf("Flipping\n");
    flip_list(&first, &last);
    print_list(first);
    return 0;
}
