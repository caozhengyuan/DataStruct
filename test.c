#include <stdio.h>
#include <string.h>
int main(void) {
    char* a = "hello";
    int c = strlen(a);
    printf("%d\n", c);
    printf("%s\n", a);
    a = "world";
    printf("%s\n", a);
    printf("%c\n", a[1]);
    return 0;
}