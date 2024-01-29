#include <stdio.h>
#include <stdlib.h>

// static creation

typedef struct node {
    int data;
    struct node* next;
} node;

// ---------------------------------------------------------------------------

// function definitions

node* addback(node* head, int data) {
    node* current = head;
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    if (head == NULL) 
    {
        // add first node.
        head = temp;
    } 
    else 
    {
        // add one node at the end of the node.
        while (current->next != NULL)
            current = current->next;
        current->next = temp;
    }

    return head;
}

node* find(node* head, int data) {
    node* current = head;
    if (current == NULL) 
    {
        return head;
    }
    else 
    {
        while (current != NULL) {
            if (current->data == data)
                return current;
            current = current->next;
        }
    }
    return head;
}

node* delnode(node* head, node* pelement) {
    node* current = head;

    // If the list is empty, nothing to delete.
    if (head == NULL) {
        return head;
    } 

    // If the element to be deleted is the first node.
    if (current == pelement) {
        head = current->next;
        free(current);
        return head;
    }

    // Traverse the list to find the node before the node to be deleted.
    while (current->next != NULL && current->next != pelement) {
        current = current->next;
    }

    // If the node to be deleted is found.
    if (current->next == pelement) {
        node* nextNode = current->next;
        current->next = current->next->next;
        free(nextNode);
    }

    return head;
}

void display(node* head) {
    node* current = head;
    if (head == NULL)
    {
        printf("Empty LinkedList.\n");
        return;
    }
    else {
        printf("[");
        while (current != NULL) {
            printf("%d", current->data);
            if (current->next != NULL)
                printf(", ");
            current = current->next;
        }
        printf("]\n\n");
    }
}

void freelist(node* head) {
    node* current = head;
    node* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    printf("List freed successfully.\n");
}

// ---------------------------------------------------------------------------


// ==========================================================================
int main(int argc, char* argv[]) {
    node* head = NULL;

    // put value in linked list
    for (int i = 0; i <= 10; i++) 
        head = addback(head, i + 2);
    
    for (int i = 0; i <= 10; i++) 
        head = addback(head, i + 55);
    
    // print linked list
    display(head);
    
    // find the element you want to delete
    node* find_node = find(head, 60);
    // printf("%d\n", find_node->data);
    head = delnode(head, find_node);
    find_node = find(head, 10);
    head = delnode(head, find_node);
    find_node = find(head, 65);
    head = delnode(head, find_node);
    find_node = find(head, 5);
    head = delnode(head, find_node);
    find_node = find(head, 2);
    head = delnode(head, find_node);

    // print linked list
    display(head);

    freelist(head);

    display(head);

    return 0;
}

// ============================================================================
