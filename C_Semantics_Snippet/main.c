#include <stdio.h>
#include <string.h>

int main() {
    int result = 5 / 2;

    printf("Division result: %d\n", result);

    char greeting[30] = "Hello ";
    strcat(greeting, "World");

    printf("Concatenated string: %s\n", greeting);

    return 0;
}