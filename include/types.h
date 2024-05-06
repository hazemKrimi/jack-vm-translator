#pragma once

enum Segment
{
    LCL,
    ARG,
    THIS,
    THAT,
    STATIC,
    CONSTANT,
    TEMP,
    POINTER,
};

enum NoArgumentCommand {
    ADD,
    SUB,
    NEG,
    EQ,
    GT,
    LT,
    AND,
    OR,
    NOT,
    RETURN,
};

enum OneArgumentCommand {
    LABEL,
    GOTO,
    IFGOTO,
};

enum TwoArgumentCommand {
    PUSH,
    POP,
    FUNCTION,
    CALL
};
