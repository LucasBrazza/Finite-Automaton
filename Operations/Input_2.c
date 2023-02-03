#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    String state;
    int initial;
    int final;
}States;

typedef struct
{
    String element;
}Alphabet;

typedef struct
{
    String origin;
    String transition;
    String destiny;
}Transition;

typedef struct {
    int sizeStates;
    int sizeAlphabet;
    int sizeTransitions;
    States *states;
    Alphabet *alphabet;
    Transition *transitions;
}DFA;
