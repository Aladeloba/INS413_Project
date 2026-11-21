#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Identify the type currently stored in a Value */
typedef enum {
    VALUE_INT,
    VALUE_DOUBLE,
    VALUE_STRING
} ValueType;

/* Store one of the supported data types */
typedef struct {
    ValueType type;

    union {
        int integer;
        double decimal;
        char *string;
    } data;

} Value;

/* Create an integer value */
Value make_int(int number) {
    Value v;
    v.type = VALUE_INT;
    v.data.integer = number;
    return v;
}

/* Create a floating-point value */
Value make_double(double number) {
    Value v;
    v.type = VALUE_DOUBLE;
    v.data.decimal = number;
    return v;
}

/* Create a string value */
Value make_string(const char *text) {
    Value v;
    v.type = VALUE_STRING;

    v.data.string = malloc(strlen(text) + 1);

    if (v.data.string != NULL) {
        strcpy(v.data.string, text);
    }

    return v;
}

/* Display a value according to its type */
void print_value(Value v) {
    switch (v.type) {
        case VALUE_INT:
            printf("%d\n", v.data.integer);
            break;

        case VALUE_DOUBLE:
            printf("%g\n", v.data.decimal);
            break;

        case VALUE_STRING:
            if (v.data.string != NULL) {
                printf("%s\n", v.data.string);
            } else {
                printf("String allocation failed\n");
            }
            break;
    }
}

/* Release memory used by a string value */
void destroy_value(Value *v) {
    if (v->type == VALUE_STRING) {
        free(v->data.string);
        v->data.string = NULL;
    }
}

/* Perform addition based on the runtime types */
int add_values(Value a, Value b, Value *result) {

    if (a.type == VALUE_INT && b.type == VALUE_INT) {
        *result = make_int(a.data.integer + b.data.integer);
        return 1;
    }

    if ((a.type == VALUE_INT || a.type == VALUE_DOUBLE) &&
        (b.type == VALUE_INT || b.type == VALUE_DOUBLE)) {

        double first = (a.type == VALUE_INT)
            ? a.data.integer : a.data.decimal;

        double second = (b.type == VALUE_INT)
            ? b.data.integer : b.data.decimal;

        *result = make_double(first + second);
        return 1;
    }

    if (a.type == VALUE_STRING && b.type == VALUE_STRING) {

        if (a.data.string == NULL || b.data.string == NULL) {
            return 0;
        }

        size_t length = strlen(a.data.string)
                      + strlen(b.data.string) + 1;

        char *combined = malloc(length);

        if (combined == NULL) {
            return 0;
        }

        strcpy(combined, a.data.string);
        strcat(combined, b.data.string);

        result->type = VALUE_STRING;
        result->data.string = combined;

        return 1;
    }

    return 0;
}

/* Test an addition operation */
void test_addition(Value a, Value b) {
    Value result = make_int(0);

    if (add_values(a, b, &result)) {
        printf("Result: ");
        print_value(result);
    } else {
        printf("Error: Incompatible data types.\n");
    }

    destroy_value(&result);
}

int main() {

    /* Demonstrate variable reassignment */
    Value variable = make_int(10);

    printf("Initial value: ");
    print_value(variable);

    destroy_value(&variable);
    variable = make_string("Hello");

    printf("Reassigned value: ");
    print_value(variable);

    printf("\nInteger addition:\n");
    test_addition(make_int(5), make_int(10));

    printf("\nMixed numeric addition:\n");
    test_addition(make_int(5), make_double(2.5));

    printf("\nString concatenation:\n");
    Value first = make_string("Hello ");
    Value second = make_string("World");

    test_addition(first, second);

    printf("\nIncompatible types:\n");
    test_addition(make_int(5), make_string("Hello"));

    /* Release allocated string memory */
    destroy_value(&variable);
    destroy_value(&first);
    destroy_value(&second);

    return 0;
}