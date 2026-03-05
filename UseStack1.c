//反转字符串
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
char arr[MAX_SIZE];
int32_t top = -1;

void push(char data);
void pop();
void Print();
char Top();
void Reverse(char* str, int32_t length);

int main(void) {
    char str[100];
    printf("请输入字符串!\n");
    fgets(str, sizeof(str), stdin);
    Reverse(str, strlen(str) - 1);
    printf("%s\n", str);

    return 0;
}

void push(char data) {
    if (top == MAX_SIZE - 1) {
        printf("Error");
        return;
    }
    top++;
    arr[top] = data;
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
    for (int i = 0; i < top + 1; i++) {
        printf("%" PRId32 "\n", arr[i]);
    }
}

char Top() {
    return arr[top];
}

void Reverse(char* string, int32_t length) {
    for (int i = 0; i < length; i++) {
        push(string[i]);
    }
    for (int i = 0; i < length; i++) {
        string[i] = Top();
        pop();
    }
}