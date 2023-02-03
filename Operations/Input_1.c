#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    int size;
    String states[size];    //nao tenho ctz se
    String initial;         //é possivel alocar
    String final;           //espaço assim
}States;

typedef struct {
    int size;
    char elements[size];
}Alphabet;

typedef struct {
    String origin;
    char transition;
    String destiny;
}Transition;

typedef struct {
    int size;
    Transition transition;
}Transitions;

typedef struct {
    States states;
    Alphabet alphabet;
    Transitions transitions;
}DFA;

