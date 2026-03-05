#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

int32_t capacity = 2;
int32_t top = -1;

void push(int32_t data, int32_t** arr);
void pop();
void Print(int32_t* arr);
int32_t Top(int32_t* arr);

int main(void) {
    int32_t* arr = (int32_t*)malloc(capacity * sizeof(int32_t));
    push(1, &arr);
    push(2, &arr);
    push(3, &arr);
    push(4, &arr);
    Print(arr);
    pop();
    printf("\n");
    Print(arr);
    int32_t element = Top(arr);
    printf("%" PRId32 "\n", element);
    free(arr);
    return 0;
}

void push(int32_t data, int32_t** arr) {
    if (top == capacity - 1) {
        int32_t* temp = (int32_t*)realloc(*arr, 2 * capacity * sizeof(int32_t));
        if (!temp) {
            printf("realloc failed!");
            exit(1);
        }
        capacity *= 2;
        top++;
        *arr = temp;
        (*arr)[top] = data;
        return;
    }
    top++;
    (*arr)[top] = data;
}

void pop() {
    if (top == -1) {
        printf("Error");
        return;
    }
    top--;
}

//从栈底开始打印
void Print(int32_t* arr) {
    for (int i = 0; i < top + 1; i++) {
        printf("%" PRId32 "\n", arr[i]);
    }
}

int32_t Top(int32_t* arr) {
    return arr[top];
}