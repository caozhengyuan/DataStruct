#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node {
    int32_t data;
    struct Node* next;
}Node;

Node* head;

void Print();
void PrintR(Node* p);
void HeadInsert(int32_t data);
void TailInsert(int32_t data);
void ChooseInsert(int32_t data, int32_t position);
void Reverse();
void ReverseR(Node* p);
void Delete(int32_t position);

int main(void) {
    head = NULL;
    HeadInsert(1);
    HeadInsert(2);
    HeadInsert(3);
    HeadInsert(4);
    TailInsert(5);
    ChooseInsert(6,1);
    Delete(1);
    Delete(3);
    Reverse();
    ReverseR(head);
    Print();
    printf("\n");
    PrintR(head);

    return 0;
}

void Print() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%" PRId32 "\n", temp->data);
        temp = temp->next;
    }
}

void HeadInsert(int32_t data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (!temp) {
        printf("malloc memory failed!");
        exit(1);
    }
    temp->data = data;
    temp->next = head;
    head = temp;
}

void TailInsert(int32_t data) {
    Node* temp1 = (Node*)malloc(sizeof(Node));
    if (!temp1) {
        printf("malloc memory failed!");
        exit(1);
    }
    temp1->data = data;
    temp1->next = NULL;
    if (head == NULL) {
        head = temp1;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = temp1;
}

void ChooseInsert(int32_t data, int32_t position) {
    Node* temp = head;
    if (position == 1) {
        Node* temp1 = (Node*)malloc(sizeof(Node));
        if (!temp1) {
        printf("malloc memory failed!");
        exit(1);
    }
        temp1->data = data;
        temp1->next = head;
        head = temp1;
        return;
    }

    for (int i = 0; i < position - 2; i++) {
        temp = temp->next;
    }
    Node* temp2 = (Node*)malloc(sizeof(Node));
    if (!temp2) {
        printf("malloc memory failed!");
        exit(1);
    }
    temp2->data = data;
    temp2->next = temp->next;
    temp->next = temp2;
}

void Delete(int32_t position) {
    Node* temp = head;
    if (position == 1) {
        head = temp->next;
        return;
    }

    for (int i = 0; i < position - 2; i++) {
        temp = temp->next;
    }
    Node* disapear = temp->next;
    temp->next = temp->next->next;
    free(disapear);
}

void Reverse() {
    Node* prev;
    Node* current;
    Node* next;
    prev = NULL;
    current = head;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

void ReverseR(Node* p) {
    if (p == NULL || p->next == NULL) {
        head = p;
        return;
    }
    ReverseR(p->next);
    Node* q = p->next;
    q->next = p;
    p->next = NULL;
}

void PrintR(Node* p) {
    if (p == NULL) {
        return;
    }
    PrintR(p->next);
    printf("%" PRId32 "\n", p->data);
}