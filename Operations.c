#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Operations.h"

// Entry: a DFA; 
// The method creates a new DFA changing the final states of the DFA to non-final
void complementDFA(DFA *dfa)
{
    int newSizeFinals = 0;
    for (int i = 0; i < dfa->sizeStates; i++)
    {
        if (dfa->states[i].final == 0)
        {
            dfa->states[i].final = 1;
            newSizeFinals = newSizeFinals + 1;
        }
        else if (dfa->states[i].final == 1)
            dfa->states[i].final = 0;
    }

    dfa->sizeFinals = newSizeFinals;
}

// Entry: three DFAs and the operation
// Operation: "u" for Union or "i" for intersection
// The method creates a new DFA from the union or intersection of the two DFAs using the states and the entry operation
void productDFA(DFA *dfa1, DFA *dfa2, DFA *product, char operation)
{
    product->sizeStates = dfa1->sizeStates * dfa2->sizeStates;
    product->states = (States *)malloc(product->sizeStates * sizeof(States));
    product->sizeFinals = 0;

    int i, j, counter = 0;
    for (i = 0; i < dfa1->sizeStates; i++)
    {
        for (j = 0; j < dfa2->sizeStates; j++)
        {
            strcpy(product->states[counter].state, dfa1->states[i].state);
            strcat(product->states[counter].state, ",");
            strcat(product->states[counter].state, dfa2->states[j].state);
            product->states[counter].initial = 0;

            if (operation == 'u')
            {
                if (dfa1->states[i].final == 1 || dfa2->states[j].final == 1)
                {
                    product->states[counter].final = 1;
                    product->sizeFinals++;
                }
                else
                    product->states[counter].final = 0;
            }

            if (operation == 'i')
            {
                if (dfa1->states[i].final == 1 && dfa2->states[j].final == 1)
                {
                    product->states[counter].final = 1;
                    product->sizeFinals++;
                }
                else
                    product->states[counter].final = 0;
            }

            if (dfa1->states[i].initial == 1 && dfa2->states[j].initial == 1)
            {
                strcpy(product->initialState.state, product->states[counter].state);
                product->initialState.initial = 1;
                product->initialState.final = product->states[counter].final;
                product->states[counter].initial = 1;
            }
            counter++;
        }
    }

    product->sizeAlphabet = dfa1->sizeAlphabet;
    product->alphabet = (Alphabet *)malloc(product->sizeAlphabet * sizeof(Alphabet));
    for (i = 0; i < product->sizeAlphabet; i++)
        strcpy(product->alphabet[i].element, dfa1->alphabet[i].element);

    counter = 0;
    product->sizeTransitions = product->sizeStates * product->sizeAlphabet;
    product->transitions = (Transition *)malloc(product->sizeStates * product->sizeAlphabet * sizeof(Transition));
    for (i = 0; i < dfa1->sizeTransitions; i++)
    {
        for (j = 0; j < dfa2->sizeTransitions; j++)
        {
            if (strcmp(dfa1->transitions[i].transition, dfa2->transitions[j].transition) == 0)
            {
                strcpy(product->transitions[counter].origin, dfa1->transitions[i].origin);
                strcat(product->transitions[counter].origin, ",");
                strcat(product->transitions[counter].origin, dfa2->transitions[j].origin);

                strcpy(product->transitions[counter].transition, dfa1->transitions[i].transition);

                strcpy(product->transitions[counter].destiny, dfa1->transitions[i].destiny);
                strcat(product->transitions[counter].destiny, ",");
                strcat(product->transitions[counter].destiny, dfa2->transitions[j].destiny);
                counter++;
            }
        }
    }
}

// Copy a DFA
void copyDFA(DFA model, DFA *newDFA)
{
    newDFA->sizeStates = model.sizeStates;
    newDFA->states = (States *)malloc(newDFA->sizeStates * sizeof(States));

    newDFA->sizeAlphabet = model.sizeAlphabet;
    newDFA->alphabet = (Alphabet *)malloc(newDFA->sizeStates * sizeof(Alphabet));

    newDFA->sizeTransitions = model.sizeTransitions;
    newDFA->transitions = (Transition *)malloc(newDFA->sizeStates * sizeof(Transition));
    int i;
    for (i = 0; i < newDFA->sizeStates; i++)
    {
        strcpy(newDFA->states[i].state, model.states[i].state);
        newDFA->states[i].initial = model.states[i].initial;
        newDFA->states[i].final = model.states[i].final;
    }
    for (i = 0; i < newDFA->sizeAlphabet; i++)
    {
        strcpy(newDFA->alphabet[i].element, model.alphabet[i].element);
    }
    for (i = 0; i < newDFA->sizeTransitions; i++)
    {
        strcpy(newDFA->transitions[i].origin, model.transitions[i].origin);
        strcpy(newDFA->transitions[i].destiny, model.transitions[i].destiny);
        strcpy(newDFA->transitions[i].transition, model.transitions[i].transition);
    }
}
