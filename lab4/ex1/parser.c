#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

enum Option parse_option(const char* command){
    if (strcmp(command, "ignore") == 0){
        return IGNORE;
    }

    if (strcmp(command, "handler") == 0){
        return HANDLER;
    }

    if (strcmp(command, "mask") == 0){
        return MASK;
    }

    if (strcmp(command, "pending") == 0){
        return PENDING;
    }
    // error
    fprintf(stderr,"Unknown command: %s\n"
                   "Use one of them: ignore/handler/mask/pending\n", command);
    exit(1);
}