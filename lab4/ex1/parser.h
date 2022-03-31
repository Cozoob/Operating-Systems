
#ifndef LAB4ZAD1_PARSER_H
#define LAB4ZAD1_PARSER_H

enum Option{
    IGNORE,
    HANDLER,
    MASK,
    PENDING
};

enum Option parse_option(const char* command);

#endif //LAB4ZAD1_PARSER_H
