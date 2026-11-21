#include <stdio.h>

int value = 10;

int main() {
    int value = 20;

    {
        int value = 30;
        printf("Inner block value: %d\n", value);
    }

    printf("Function block value: %d\n", value);

    return 0;
}