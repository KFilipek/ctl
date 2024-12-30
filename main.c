#include "ctl.h"
#include "module.h"

#include <stdio.h>

void* func1() {
    printf("Function 1\n");
}

void testPath(const char *path) {
    if (pathExists(path)) {
        printf("%s exists\n", path);
    } else {
        printf("%s does not exist\n", path);
    }
}

int main() {
    init();
    initialize_module();
    addPath("debug.log.enable=1", OPTION_TYPE_BOOL, OPERATION_TYPE_RW, NULL, NULL, func1);
    addPath("debug.log.level=5", OPTION_TYPE_INT, OPERATION_TYPE_RW, NULL, NULL, func1);
    
    printf("----------------\n");
    testPath("debug.log.enable");
    testPath("debug.log.level");
    testPath("nonexistent.file");
    
    printf("----------------\n");
    printPaths();
    
    printf("----------------\n");
    void* res = NULL;
    res = executePath("module.my_value", OPERATION_TYPE_RO);
    printf("Value: %s\n", (char *)res);
    executePath("module.my_value=Hello, World!", OPERATION_TYPE_RW);
    executePath("module.my_value", OPERATION_TYPE_RO);
    executePath("module.simple_value", OPERATION_TYPE_RO);
    return 0;
}