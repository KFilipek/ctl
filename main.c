#include "ctl.h"

#include <stdio.h>

void func1() {
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
    addPath("debug.log.enable=1", OPTION_TYPE_BOOL, OPERATION_TYPE_EXEC, func1);
    addPath("debug.log.level=5", OPTION_TYPE_INT, OPERATION_TYPE_EXEC, func1);
    printPaths();
    testPath("debug.log.enable");
    testPath("debug.log.level");
    testPath("nonexistent.file");
    return 0;
}