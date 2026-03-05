#include <stdio.h>

int main(void) {
    char* a = "hello";
    printf("%s\n", a);
    a = "world";
    printf("%s\n", a);
    printf("%c\n", a[1]);
    return 0;
}