#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int32_t top = -1;
int32_t buf = -1;
int32_t eva = -1;
char stack[50];
char buffer[50];
int32_t evalue[50];

void Pop();
char Top();
void Push(char data);
bool CheckedBalancedParenthese(char* arr, int32_t length);
bool CheckAtSome(char pa);
bool NotPair(char data);
void InfixToPostfix(char* arr, int32_t length);
bool isOperator(char data);
int precedence(char data);
bool isOpeningParenthese(char data);
bool isClosingParenthese(char data);
int32_t Evalueate(char* arr);
void EPop();
void EPush(int32_t data);

int main(void) {
    char math[10] = "2+3*4-6*7"; //234*+67*-
    char math1[20] = "(2+3)*(4-6)*7/5"; //23+46-*7*
    InfixToPostfix(math, strlen(math));
    int32_t ans1 = Evalueate(buffer);
    printf("%" PRId32 "\n", ans1);
    InfixToPostfix(math1, strlen(math1));
    int32_t ans2 = Evalueate(buffer);
    printf("%" PRId32 "\n", ans2);
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

void EPop(){
    eva--;
}
void EPush(int32_t data) {
    eva++;
    evalue[eva] = data;
}
char Top() {
    return stack[top];
}

//"2+3*4-6*7"  234*+67*-
//"(2+3)*(4-6)*7" //23+46-*7*
void InfixToPostfix(char* arr, int32_t length) {
    top = -1;
    buf = -1;
    for (int i = 0; i < length; i++) {
        if (!isClosingParenthese(arr[i]) && !isOpeningParenthese(arr[i]) && !isOperator(arr[i])) { //如果是操作数存入buffer
            buf++;
            buffer[buf] = arr[i]; 
        }
        else if (isOpeningParenthese(arr[i])) {//如果是开括号 存入栈
            top++;
            stack[top] = arr[i];
        }
        else if (isClosingParenthese(arr[i])) {//如果是闭括号 出栈知道遇到开括号
            while (top != -1 && !isOpeningParenthese(stack[top])) {
                buf++;
                buffer[buf] = Top();
                Pop();
            }
            Pop();
        }
        else {//如果是运算符
            while (top != -1 && precedence(stack[top]) >= precedence(arr[i])) {//栈里的运算符优先级更高出栈
                buf++;
                buffer[buf] = Top();
                Pop();
            }
            Push(arr[i]);//进栈
        }
}
     while (top != -1) {
        buf++;
        buffer[buf] = Top();
        Pop();
    }
    buffer[++buf] = '\0';
}

bool isOperator(char data) {
    switch (data)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    return true;
    default:
        return false;
    }
}

int precedence(char data) {
    switch (data)
    {
    case '+':
    case '-':
    return 1;
    case '*':
    case '/':
    return 2;
    default:
        return 0;
    }
}

bool isOpeningParenthese(char data) {
    switch (data)
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

bool isClosingParenthese(char data) {
    switch (data)
    {
    case ')':
    return true;
    case ']':
    return true;
    case '}':
    return true;
    default:
        return false;
    }
}

int32_t Evalueate(char* arr) {
    eva = -1;
    for (int i = 0; i < strlen(arr); i++) {
        if (isOperator(arr[i])) {
        int32_t number1 = evalue[eva];
        EPop();
        int32_t number2 = evalue[eva];
        EPop();
        switch (arr[i])
        {
        case '+':
            EPush(number2 + number1);
            break;
        case '-':
            EPush(number2 - number1);
            break;
        case '*':
            EPush(number2 * number1);
            break;
        case '/':
            EPush(number2 / number1);
            break;
        default:
            break;
        }
    }
    else if (isdigit(arr[i])){
        int32_t value = arr[i] - '0';
        EPush(value);
    }
    }
    return evalue[eva];
}