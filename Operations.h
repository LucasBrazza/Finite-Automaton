#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Helper.c"
#include "Input.c"
#include "Converter.c"

#define stringSize 20

typedef struct
{
    char state[stringSize];
    int initial;
    int final;
} States;

typedef struct
{
    char element[stringSize];
} Alphabet;

typedef struct
{
    char origin[stringSize];
    char transition[stringSize];
    char destiny[stringSize];
} Transition;

typedef struct
{
    int sizeStates;
    int sizeAlphabet;
    int sizeTransitions;
    int sizeFinals;
    States *states;
    Alphabet *alphabet;
    Transition *transitions;
    States initialState;
} DFA;

void printDFA(DFA *dfa1);

void generateDFA(DFA *dfa, char *path);

void complementDFA(DFA *dfa);

void productDFA(DFA *dfa1, DFA *dfa2, DFA *product, char operation);

void copyDFA(DFA model, DFA *newDFA);

#endif