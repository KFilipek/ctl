#ifndef CTL_H
#define CTL_H

/*
* CTL - Control Library
* Intention of this library is to provide a simple way to control the application
* by reading and writing properties called paths.
* Each path can have a callback function that is called when the path is read, written or executed.
* Otherwise the path is just a simple value.
*/

/* Operation type */
enum OperationType {
    OPERATION_TYPE_RO, // TODO: Read-only
    OPERATION_TYPE_RW, // TODO: Read-write
    OPERATION_TYPE_EXEC, // Same as RO, but executes exec callback. Notice: Forbidden in union mode.
    OPERATION_TYPE_CALLBACK // Callback driven RWExec
};

/* Type of stored value */
enum OptionType {
    OPTION_TYPE_BOOL,
    OPTION_TYPE_STRING,
    OPTION_TYPE_INT,
    OPTION_TYPE_EXEC // Ignore union values -> callback driven
};

/* Option structure */
typedef struct Option {
    /* Properties */
    char *path;
    enum OptionType type;

    /* Callbacks */
    void *(*callback_r)(void *);
    void *(*callback_w)(void *);
    void *(*callback_exec)(void *);

    /* Value of the option */
    union {
        // Stores just simple values
        // TODO: Consider storing BLOBs in the future
        int int_value;
        char *string_value;
        int bool_value;
    };
} Option;

/* API */
void init();
// Add new path to the CTL
// TODO: Add operation type as write level
void addPath(char *path, enum OptionType type, enum OperationType write_level, void *(*read_cb)(void *), void *(*write_cb)(void *), void *(*exec_cb)(void *));
// Execute path with given operation
void* executePath(const char *path, enum OperationType operation);

void printPaths();
int pathExists(const char *path);

#endif // CTL_H