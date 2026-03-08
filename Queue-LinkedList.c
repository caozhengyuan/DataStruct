#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct Node
{
    int32_t data;
    struct Node* next;
}Node;

Node* front = NULL;
Node* rear = NULL;

void Enqueue(int32_t data);
void Dequeue();
void Print();

int main() {
    Enqueue(1);
    Enqueue(2);
    Enqueue(3);
    Enqueue(4);
    Print();
    printf("\n");
    Dequeue();
    Print();
    return 0;
}

void Enqueue(int32_t data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("falied to malloc!\n");
        return;
    }
    temp->data = data;
    temp->next = NULL;
    if (front == NULL) {
        front = temp;
        rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

void Dequeue() {
    if (front == NULL) {
        printf("queue is empty\n");
        return;
    }
    Node* temp = front;
    front = front->next;
    free(temp);

    if (front == NULL) {
        rear = NULL;
    }
}

void Print() {
    Node* temp = front;
    while (temp != NULL) {
        printf("%" PRId32 "\n", temp->data);
        temp = temp->next;
    }
}