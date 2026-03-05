//反转链表
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Node
{
    int32_t data;
    struct Node* next;
}Node;

Node* arr[MAX_SIZE];
int32_t top = -1;
Node* head;

void push(Node* data);
void pop();
void Print();
Node* Top();
void Reverse();
void insert(int32_t data);
void PrintList();



int main(void) {
    head = NULL;
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    PrintList();
    Reverse();
    printf("\n");
    PrintList();
    return 0;
}

void push(Node* node) {
    if (top == MAX_SIZE - 1) {
        printf("Error");
        return;
    }
    top++;
    arr[top] = node;
}

void pop() {
    if (top == -1) {
        printf("Error");
        return;
    }
    top--;
}

//从栈底开始打印
void Print() {
    return;
}

Node* Top() {
    return arr[top];
}

//头插
void insert(int32_t data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = head;
    head = temp;
}

void Reverse() {
    Node* temp = head;
    while (temp != NULL) {
        push(temp);
        temp = temp->next;
    }
    temp = Top();
    head = temp;
    pop();
    while (top != -1) {
        temp->next = Top();
        temp = temp->next;
        pop();
    }
    temp->next = NULL;
}

void PrintList() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%" PRId32 "\n", temp->data);
        temp = temp->next;
    }
}