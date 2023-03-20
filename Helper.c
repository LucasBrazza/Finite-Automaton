#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Helper.h"

// Seek in the file for the line that contains the desired parameter and returns the corresponding integer
// 1 - number of states
// 2 - states
// 3 - number of alphabet elements
// 4 - alphabet
// 5 - number transitions
// 6 - transitions
// 7 - initial state
// 8 - number of final states
// 9 - final states
int seekParam(DFA *dfa, char *path, int parameter)
{
    int line;
    switch (parameter)
    {
    case 1:
        line = 1;
        break;
    case 2:
        line = 1 + 1;
        break;
    case 3:
        line = 1 + 1 + dfa->sizeStates;
        break;
    case 4:
        line = 1 + 1 + dfa->sizeStates + 1;
        break;
    case 5:
        line = 1 + 1 + dfa->sizeStates + 1 + dfa->sizeAlphabet;
        break;
    case 6:
        line = 1 + 1 + dfa->sizeStates + 1 + dfa->sizeAlphabet + 1;
        break;
    case 7:
        line = 1 + 1 + dfa->sizeStates + 1 + dfa->sizeAlphabet + 1 + dfa->sizeTransitions;
        break;
    case 8:
        line = 1 + 1 + dfa->sizeStates + 1 + dfa->sizeAlphabet + 1 + dfa->sizeTransitions + 1;
        break;
    case 9:
        line = 1 + 1 + dfa->sizeStates + 1 + dfa->sizeAlphabet + 1 + dfa->sizeTransitions + 1 + 1;
        break;
    default:
        line = 1;
        break;
    }

    return seekLine(line, path);
}

// Seek in the file the desired line and returns the corresponding integer
int seekLine(int line, char *path)
{
    int position = 0, aux = 1;
    char c;
    FILE *file = fopen(path, "r");

    while (aux < line)
    {
        c = getc(file);
        position++;
        if (c == '\n')
            aux++;
    }

    fclose(file);
    return position;
}

// Free DFA memory
void freeDFA(DFA *dfa)
{
    printf("\nFree Memory Started\n");

    int i;

    // for (i = 0; i < dfa->sizeStates; i++)
    // {
    //     printf("\n%d - Free in Progress", i);
    //     free(dfa->states[i].state);
    // }

    printf("\nFree in Progress");

    free(dfa->states);

    // for (i = 0; i < dfa->sizeTransitions; i++)
    // {
    //     printf("\n%d - Free in Progress", i);

    //     free(dfa->transitions[i].destiny);
    //     free(dfa->transitions[i].origin);
    //     free(dfa->transitions[i].transition);
    // }
    free(dfa->transitions);

    // free(dfa->alphabet->element);
    free(dfa->alphabet);

    // free(dfa->initialState.final);
    // free(dfa->initialState.initial);
    // char var_null[] = "NULL";
    // strcpy(dfa->initialState.state, NULL);
    

    // free(dfa);
    printf("\nFree Memory Completed\n");
}

// Prints a word
void printWord(char *word)
{
    printf("\n");
    int i = 0;
    char aux = word[i];
    while (aux != '\0')
    {
        printf("%c", aux);
        aux = word[++i];
    }
}

// Prints the DFA
void printDFA(DFA *dfa1)
{
    printf("\nn states %d", dfa1->sizeStates);
    for (int i = 0; i < dfa1->sizeStates; i++)
    {
        printWord(dfa1->states[i].state);
        printf(" - initial %d - final %d", dfa1->states[i].initial, dfa1->states[i].final);
    }
    printf("\nn alphabet %d\n", dfa1->sizeAlphabet);
    for (int i = 0; i < dfa1->sizeAlphabet; i++)
    {
        printWord(dfa1->alphabet[i].element);
    }
    printf("\nn transitions %d", dfa1->sizeTransitions);
    for (int j = 0; j < dfa1->sizeTransitions; j++)
    {
        printf("\n");
        printWord(dfa1->transitions[j].origin);
        printWord(dfa1->transitions[j].transition);
        printWord(dfa1->transitions[j].destiny);
    }
}