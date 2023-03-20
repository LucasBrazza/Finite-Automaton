#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Recognize.h"
#include "Input.h"

void reconWord(char *pathDFA, char *pathWords, char *pathOutput)
{
    DFA dfa;
    generateDFA(&dfa, pathDFA);
    FILE *f = openf(pathWords);
    FILE *output = openf(pathOutput);
    States auxState;
    char auxChar = getc(f);
    int i;
    while (auxChar != EOF)
    {
        while (auxChar != '\n')
        {
            strcmp(auxState.state, dfa.initialState.state);
            for (i = 0; i < dfa.sizeTransitions; i++)
            {
                if (strcmp(dfa.transitions[i].origin, auxState.state) == 0 && strcmp(dfa.transitions[i].transition, auxChar) == 0)
                {
                    strcpy(auxState.state, dfa.transitions[i].destiny);
                    break;
                }
            }
            auxChar = getc(f);
        }
    }

    for (i = 0; i < dfa.sizeStates; i++)
    {
        if (strcmp(auxState.state, dfa.states[i].state))
        {
            if (dfa.states[i].final == 1)
                fprintf(pathOutput, "1\n");
            else
                fprintf(pathOutput, "0\n");
        }
    }

    fclose(pathWords);
    fclose(pathDFA);
    fclose(pathOutput);
    free(&dfa);
}
