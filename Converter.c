#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Converter.h"


// Converts a string to an integer
char *finalsToString(DFA *dfa)
{
    char *str;
    str = (char *)malloc(dfa->sizeFinals * stringSize * sizeof(char));
    strcpy(str, "");
    int index = 0;
    for (int i = 0; i < dfa->sizeStates; i++)
    {
        if (dfa->states[i].final == 1)
        {
            strcat(str, dfa->states[i].state);
            strcat(str, " ");
        }
    }
    return str;
}


// Creates the corresponding .dot file for a DFA
void dfaToDOT(char *path, DFA *dfa)
{
    char *str = finalsToString(dfa);
    FILE *file = fopen(path, "wt");

    fprintf(file, "digraph finite_state_machine {\n\trankdir=LR;\n\tsize=\"10\"\n\n"
                  "\tnode [shape = doublecircle]; %s;",
            str);

    fprintf(file, "\n\tnode [shape = point]; qi;\n");

    fprintf(file, "\n\tnode [shape = circle]");

    fprintf(file, "\n\tqi -> %s;", dfa->initialState.state);

    for (int i = 0; i < dfa->sizeTransitions; i++)
        fprintf(file, "\n\t%s -> %s [label = %s ];", dfa->transitions[i].origin, dfa->transitions[i].destiny, dfa->transitions[i].transition);
        fprintf(file, "\n\t}");

    free(str);
    fclose(file);
}


// Creates the corresponding .txt file for a DFA
void dfaToFile(DFA *dfa, char *relativePath)
{
    FILE *file = fopen(relativePath, "w");
    char aux[50];
    itoa(dfa->sizeStates, aux, 10);
    fputs(strcat(aux, "\n"), file);
    int i;

    for (i = 0; i < dfa->sizeStates; i++)
        fputs(strcat(dfa->states[i].state, "\n"), file);

    itoa(dfa->sizeAlphabet, aux, 10);
    fputs(strcat(aux, "\n"), file);

    for (i = 0; i < dfa->sizeAlphabet; i++)
        fputs(strcat(dfa->alphabet[i].element, "\n"), file);

    itoa(dfa->sizeTransitions, aux, 10);
    fputs(strcat(aux, "\n"), file);

    for (i = 0; i < dfa->sizeTransitions; i++)
    {
        fputs(strcat(dfa->transitions[i].origin, " "), file);
        fputs(strcat(dfa->transitions[i].transition, " "), file);
        fputs(strcat(dfa->transitions[i].destiny, "\n"), file);
    }

    fputs(strcat(dfa->initialState.state, "\n"), file);

    itoa(dfa->sizeFinals, aux, 10);
    fputs(strcat(aux, "\n"), file);

    for (i = 0; i < dfa->sizeStates; i++)
    {
        if (dfa->states[i].final == 1)
            fputs(dfa->states[i].state, file);
    }

    fclose(file);
}


