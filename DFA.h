#ifndef DFA_H
#define DFA_H

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

#endif  DFA_H
