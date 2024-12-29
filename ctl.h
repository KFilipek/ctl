#ifndef CTL_H
#define CTL_H

/* Operation type */
enum OperationType {
    OPERATION_TYPE_R,
    OPERATION_TYPE_W,
    OPERATION_TYPE_EXEC
};

/* Type of stored value */
enum OptionType {
    OPTION_TYPE_BOOL,
    OPTION_TYPE_STRING,
    OPTION_TYPE_INT,
    OPTION_TYPE_EXEC
};

/* Option structure */
typedef struct Option {
    /* Properties */
    char *path;
    enum OptionType type;

    /* Callbacks */
    void (*callback_r)(char *);
    void (*callback_w)(char *);
    void (*callback_exec)(char *);

    /* Value of the option */
    union {
        int int_value;
        char *string_value;
        int bool_value;
    };
} Option;

/* API */
void init();
void addPath(char *path, void *value, enum OptionType type, enum OperationType operation, void (*callback)(void *));
void printPaths();
int pathExists(char *path);

#endif // CTL_H