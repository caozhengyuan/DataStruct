#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct Node
{
    int32_t data;
    struct Node* next;
}Node;

Node* top;

void Push(int32_t data);
void Pop();
int32_t Top();
void Print();

int main(void) {
    top = NULL;
    Push(1);
    Push(2);
    Push(3);
    Push(4);
    Print();
    Pop();
    printf("\n");
    Print();
    int32_t element = Top();
    printf("%" PRId32 "\n", element);
    return 0;
}

void Push(int32_t data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (!temp) {
        printf("malloc memory failed!");
        exit(1);
    }
    temp->data = data;
    temp->next = top;
    top = temp;
}

void Pop() {
    if (top == NULL) {
        printf("There are no elements\n");
        return;
    }
    Node* temp = top;
    top = top->next;
    free(temp);
}

int32_t Top() {
    if (top == NULL) {
        printf("Stack is empty!");
        exit(1);
    }
    return top->data;
}

//从栈顶开始打印
void Print() {
    Node* temp = top;
    while (temp != NULL) {
        printf("%" PRId32 "\n", temp->data);
        temp = temp->next;
    }
}