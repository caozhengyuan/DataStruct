#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX 3

int32_t queue[MAX];
int32_t front = -1;
int32_t rear = -1;

void Enqueue(int32_t data);
void Dequeue();
bool isFUll();
bool isEmpty();
void Print();

int main() {
    Enqueue(1);
    Enqueue(2);
    Enqueue(3);
    Dequeue();
    Enqueue(4);
    Print();
}

void Enqueue(int32_t data) {
    if (isEmpty()) {
        rear++;
        front++;
        queue[rear] = data;
        return;
    }
    if (isFUll()) {
        printf("Queue is full\n");
        return;
    }
    rear++;
    rear = rear % MAX;
    queue[rear] = data;
}

void Dequeue() {
    if (isEmpty()) {
        printf("There are no elements!\n");
        return;
    }
    if (front == rear) {
        front = -1;
        rear = -1;
    }
    else {
        front++;
        front = front % MAX;
    }
}

bool isEmpty() {
    return front == -1;
}

bool isFUll() {
    int32_t temp = (rear + 1) % MAX;
    if (temp == front) {
        return true;
    }
    return false;
}

void Print() {
    int32_t temp = front;
    while (temp != rear) {
        printf("%" PRId32 "\n", queue[temp]);
        temp++;
        temp = temp % MAX;
    }
    printf("%" PRId32 "\n", queue[rear]);
}