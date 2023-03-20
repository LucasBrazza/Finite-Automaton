#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Minimization.h"

void minimization(DFA *dfa)
{
    int notFinal = dfa->sizeStates - dfa->sizeFinals;
    // if(notFinal == 0) retorna um unico grupo com todos os estados
    int equivalency = 0, i = 0, loop = 0, n = 2;
    char ***s;
    **s = (char **)malloc(sizeof(char **));
    *s[0] = (char *)malloc(n * sizeof(char *));
    *s[0][0] = (char *)malloc(dfa->sizeFinals * stringSize * sizeof(char));

    *s[0][1] = (char *)malloc(notFinal * stringSize + sizeof(char));
    strcpy(s[0][0], "");
    strcpy(s[0][1], "");

    for (i = 0; i < dfa->sizeStates; i++)
    {
        if (dfa->states[i].final -= 1)
        {
            strcat(s[0][0], dfa->states[i].state);
            strcat(s[0][0], ",");
        }
        else
        {
            strcat(s[0][1], dfa->states[i].state);
            strcat(s[0][1], ",");
        }
    }

    
}
