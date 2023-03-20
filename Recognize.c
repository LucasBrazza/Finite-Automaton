#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Recognize.h"
#include "Input.h"

int recon(char *pathDFA, char *pathWords, char *pathOutput)
{
    DFA dfa;
    generateDFA(&dfa, pathDFA);
    FILE *f = fopen(pathWords, "rb");
    FILE *output = fopen(pathOutput, "wb");
    if (f == NULL || output == NULL)
    {
        printf("\n\nINVALID TEXT FILE\n\n");
        exit(1);
    }
    States auxState;
    strcpy(auxState.state, dfa.initialState.state);
    char auxChar = getc(f);
    int i = 0, t = 0;
    while (auxChar != EOF)
    {
        while (auxChar != '\n')
        {
            t = 0;
            i = 0;
            while ((i < dfa.sizeTransitions) && t == 0)
            {
                if (strcmp(dfa.transitions[i].origin, auxState.state) == 0 && dfa.transitions[i].transition == auxChar)
                {
                    strcpy(auxState.state, dfa.transitions[i].destiny);
                    t = 1;
                }
                printf("%d", i);
                i++;
            }
            auxChar = getc(f);
        }
        for (i = 0; i < dfa.sizeStates; i++)
        {
            if (strcmp(auxState.state, dfa.states[i].state) == 0)
            {
                if (dfa.states[i].final == 1)
                    fprintf(output, "1\n");
                else
                    fprintf(output, "0\n");
            }
        }
        auxChar = getc(f);
    }

    fclose(f);
    fclose(output);
    return 5;
}
