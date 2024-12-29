#include "ctl.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_OPTIONS 100
#define MAX_STRING_LENGTH 256

int matrix_length = MAX_OPTIONS;
int string_length = MAX_STRING_LENGTH;

Option options[MAX_OPTIONS];

void init() {
    printf("Initializing...\n");
}

void addPath(char *path, enum OptionType type, enum OperationType operation, void (*callback)(void *)) {
    // Sample path: debug.log.enable=1
    // Sample path: debug.log.level=5
    // Sample path: debug.log.path=/var/log/debug.log

    // Find the first '=', and replace it with '\0', then set value as the next character
    char *path_copy = strdup(path);

    void *value = NULL;
    char *equal_sign = strchr(path_copy, '=');
    if (equal_sign != NULL) {
        *equal_sign = '\0';
        value = equal_sign + 1;
    }
    for (int i = 0; i < MAX_OPTIONS; i++) {
        if (options[i].path == NULL) {
            options[i].path = strdup(path_copy);
            options[i].type = type;
            switch (type) {
                case OPTION_TYPE_STRING:
                    options[i].string_value = strdup((char *)value);
                    break;
                case OPTION_TYPE_INT:
                    options[i].int_value = atoi((char *)value);
                    break;
                case OPTION_TYPE_BOOL:
                    options[i].bool_value = atoi((char *)value);
                    break;
            }
            switch (operation) {
                case OPERATION_TYPE_R:
                    options[i].callback_r = (void (*)(char *))callback;
                    break;
                case OPERATION_TYPE_W:
                    options[i].callback_w = (void (*)(char *))callback;
                    break;
                case OPERATION_TYPE_EXEC:
                    options[i].callback_exec = (void (*)(char *))callback;
                    break;
            }
            break;
        }
    }
    free(path_copy);
}

void printPaths() {
    for (int i = 0; i < MAX_OPTIONS; i++) {
        if (options[i].path != NULL) {
            printf("Path: %s, ", options[i].path);
            switch (options[i].type) {
                case OPTION_TYPE_STRING:
                    printf("Value: %s\n", options[i].string_value);
                    break;
                case OPTION_TYPE_INT:
                    printf("Value: %d\n", options[i].int_value);
                    break;
                case OPTION_TYPE_BOOL:
                    printf("Value: %d\n", options[i].bool_value);
                    break;
            }
        }
    }
}

int pathExists(const char *path) {
    for (int i = 0; i < MAX_OPTIONS; i++) {
        if (options[i].path != NULL && strcmp(options[i].path, path) == 0) {
            return 1;
        }
    }
    return 0;
}