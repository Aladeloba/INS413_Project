#include <stdio.h>

void demonstrate() {
    int value = 10;

    printf("Initial value: %d\n", value);

    value = 20;

    printf("Updated value: %d\n", value);

    {
        int temporary = 30;
        printf("Temporary value: %d\n", temporary);
    }

    // temporary is no longer accessible here
}

int main() {
    demonstrate();
    return 0;
}