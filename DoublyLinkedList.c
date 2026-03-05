#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct Node {
    int32_t data;
    struct Node* prev;
    struct Node* next;
}Node;

Node* head;

Node* CreateNode(int32_t data);
void Print();
void InsertAtHead(int32_t data);
void InsertAtTail(int32_t data);
void ReversePrint();

int main(void) {
    head = NULL;
    InsertAtHead(1);
    InsertAtHead(2);
    InsertAtHead(3);
    InsertAtHead(4);
    InsertAtTail(5);
    Print();
    printf("\n");
    ReversePrint();
    return 0;
}

Node* CreateNode(int32_t data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("malloc memory failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void Print() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%" PRId32 "\n", temp->data);
        temp = temp->next;
    }
}

void InsertAtHead(int32_t data) {
    Node* newNode = CreateNode(data);
    if (!newNode) {
        printf("malloc memory failed!");
        exit(1);
    }
    if (head == NULL) {
        head = newNode;
        return;
    }
    head->prev = newNode;
    newNode->next = head;
    head = newNode; 
}

void InsertAtTail(int32_t data) {
    Node* newNode = CreateNode(data);
    if (!newNode) {
        printf("malloc memory failed!");
        exit(1);
    }
    if (head == NULL) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void ReversePrint() {
    Node* temp = head;
    if (temp == NULL) {
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (temp != NULL) {
        printf("%" PRId32 "\n", temp->data);
        temp = temp->prev;
    }
}