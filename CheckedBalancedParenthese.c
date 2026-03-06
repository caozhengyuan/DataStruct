#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int32_t top = -1;
char stack[50];

void Pop();
char Top();
void Push(char data);
bool CheckedBalancedParenthese(char* arr, int32_t length);
bool CheckAtSome(char pa);
bool NotPair(char data);

int main(void) {
    char math[10] = "2+3*4-6*7";
    return 0;
}

void Push(char data) {
    top++;
    stack[top] = data;
}
void Pop() {
    if (top == -1) {
        printf("Error");
        return;
    }
    top--;
}

char Top() {
    return stack[top];
}

bool CheckedBalancedParenthese(char* arr, int32_t length) {
    top = -1;
    for (int i = 0; i < length; i++) {
        if (CheckAtSome(arr[i])) {
            Push(arr[i]);
        }
        else {
            if (top == -1 || NotPair(arr[i])) {
                printf("Error\n");
                return false;
            }
            else {
                Pop();
            }
        }
    }
    if (top == -1) {
        return true;
    }
        return false;
}

bool CheckAtSome(char pa) {
            switch (pa)
            {
            case '(':
                return true;
            case '[':
                return true;
            case '{':
                return true;
            default:
                return false;
            } 
}

bool NotPair(char data) {
    switch (data)
    {
    case ')':
    if (Top() != '(') {
        return true;
    }
    return false;
    case ']':
    if (Top() != '[') {
        return true;
    }
    return false;
    case '}':
    if (Top() != '{') {
        return true;
    }
    return false;
    default:
    return true;
    }
}