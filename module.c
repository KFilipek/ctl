#include <stdio.h>
#include "ctl.h"

char my_value[100] = "Hello, World from module!";

// Sample callback
void* printMyValue() {
    if (*(int*)executePath("ctl.log.enable", OPERATION_TYPE_RO) == 1)
        printf("Value from module: %s\n", my_value);
    return my_value;
}

// Set callback
void* setMyValue(void *value) {
    snprintf(my_value, sizeof(my_value), "%s", (char *)value);
}

void initialize_module() {
    addPath("module.my_value", OPTION_TYPE_EXEC, OPERATION_TYPE_EXEC, printMyValue, setMyValue, NULL);
    addPath("module.simple_value=sample text", OPTION_TYPE_STRING, OPERATION_TYPE_RW, NULL, NULL, NULL);
    if (*(int*)executePath("ctl.log.enable", OPERATION_TYPE_RO) == 1)
        printf("Module initialized\n");
}