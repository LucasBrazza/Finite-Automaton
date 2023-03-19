#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Input.h"


void clearString(char *str)
{
    strcpy(str, ""); // clears string
}

void saveStates(DFA *dfa, FILE *entry, char auxChar, int iterate, int lineIndex, char *readLine)
{
    for (iterate = 0; iterate < dfa->sizeStates; iterate++)
    {
        lineIndex = 0; // reset index
        clearString(readLine);
        // reads line
        auxChar = getc(entry);
        while (auxChar != '\n')
        {
            readLine[lineIndex++] = auxChar;
            auxChar = getc(entry);
        }

        readLine[lineIndex] = '\0'; // indicate end of string to strcpy function
        strcpy(dfa->states[iterate].state, readLine);

        dfa->states[iterate].initial = 0;
        dfa->states[iterate].final = 0;
    }
}

void saveAlphabet(DFA *dfa, FILE *entry, char auxChar, int iterate, int lineIndex, char *readLine)
{
    // saves all alphabet elements of dfa
    for (iterate = 0; iterate < dfa->sizeAlphabet; iterate++)
    {
        lineIndex = 0; // reset index
        clearString(readLine);
        // reads line
        auxChar = getc(entry);
        while (auxChar != '\n')
        {
            readLine[lineIndex++] = auxChar;
            auxChar = getc(entry);
        }

        readLine[lineIndex] = '\0'; // indicate end of string to strcpy function
        strcpy(dfa->alphabet[iterate].element, readLine);
    }
}

void saveTransitions(DFA *dfa, FILE *entry, char auxChar, int iterate, int lineIndex, char *readLine)
{
    int aux;
    auxChar = getc(entry);
    for (iterate = 0; iterate < dfa->sizeTransitions; iterate++)
    {
        clearString(readLine);
        lineIndex = 0; // reset index
        // if (auxChar != ' ' && auxChar != '\n')
        //     readLine[lineIndex] = auxChar;
        // lineIndex++;

        // reads line
        aux = 0; // variable used to count spauxChares
        while (auxChar != '\n')
        {

            // there will be 3 words, when one word is identfied the end of the string is
            // indicated after the last position (indexAux+1), the string is than copied
            // to its dfa position, the line read is emptied and the word index is reset
            if (auxChar == ' ')
            {
                if (aux == 0)
                {
                    readLine[lineIndex++] = '\0';
                    strcpy(dfa->transitions[iterate].origin, readLine);
                }
                if (aux == 1)
                {
                    readLine[lineIndex++] = '\0';
                    strcpy(dfa->transitions[iterate].transition, readLine);
                }
                aux++;
                clearString(readLine);
                lineIndex = 0; // reset index
            }
            if (auxChar != ' ' && auxChar != '\n')
            {
                readLine[lineIndex] = auxChar;
                lineIndex++;
            }
            auxChar = getc(entry);
        }
        //saves destiny
        if (auxChar == '\n')
        {
            readLine[lineIndex++] = '\0';
            strcpy(dfa->transitions[iterate].destiny, readLine);
            clearString(readLine);
            lineIndex = 0; // reset index
            auxChar = getc(entry);
        }
    }
}

void generateDFA(DFA *dfa, char *path)
{
    FILE *entry = fopen(path, "r");
    if (entry == NULL)
    {
        printf("\n\nINVALID TEXT FILE\n\n");
        exit(1);
    }

    // variables for reading file
    char readLine[70] = "                                                                      ";
    int lineIndex = 0;
    int iterate;

    // read the first parameter (number of states)
    char auxChar = getc(entry);
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0';       // indicate end of string to atoi function
    dfa->sizeStates = atoi(readLine); // convert string to int

    // alocate numer of states of the dfa
    dfa->states = (States *)malloc(dfa->sizeStates * sizeof(States));
    if (dfa->states == NULL)
        exit(1);

    // saves all states of dfa
    saveStates(dfa, entry, auxChar, iterate, lineIndex, readLine);

    // read the second parameter (number of elements in alphabet)
    lineIndex = 0; // reset index
    clearString(readLine);
    auxChar = getc(entry);
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0';         // indicate end of string to atoi function
    dfa->sizeAlphabet = atoi(readLine); // convert string to int

    // alocate alphabet size of the dfa
    dfa->alphabet = (Alphabet *)malloc(dfa->sizeAlphabet * sizeof(Alphabet));
    if (dfa->alphabet == NULL)
    {
        exit(1);
    }

    saveAlphabet(dfa, entry, auxChar, iterate, lineIndex, readLine);

    // read the third parameter (number of transitions)
    lineIndex = 0; // reset index
    clearString(readLine);
    auxChar = getc(entry);
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0';            // indicate end of string to atoi function
    dfa->sizeTransitions = atoi(readLine); // convert string to int

    // alocate number of transitions of the dfa
    dfa->transitions = (Transition *)malloc(dfa->sizeTransitions * sizeof(Transition));
    if (dfa->alphabet == NULL)
    {
        exit(1);
    }

    // saves all transitions of dfa
    saveTransitions(dfa, entry, auxChar, iterate, lineIndex, readLine);

    // read the fourth parameter (inicial state)
    fseek(entry, seekParam(dfa, path, 7), SEEK_SET);
    lineIndex = 0; // reset index
    clearString(readLine);
    auxChar = getc(entry);
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0'; // indicate end of string to strcpy function

    strcpy(dfa->initialState.state, readLine);
    dfa->initialState.initial = 1;
    // atualizar o elemento em states

    // read the fifth parameter (number of final states)
    lineIndex = 0; // reset index
    clearString(readLine);
    auxChar = getc(entry);
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0';
    dfa->sizeFinals = atoi(readLine); // convert string to int
    // creates a array with all the final states
    char **finalStates = (char **)malloc(dfa->sizeFinals * sizeof(char *));
    for (iterate = 0; iterate < dfa->sizeFinals; iterate++)
    {
        lineIndex = 0; // reset index
        clearString(readLine);
        // reads line
        auxChar = getc(entry);
        while (auxChar != EOF && auxChar != '\n')
        {
            readLine[lineIndex++] = auxChar;
            auxChar = getc(entry);
        }
        readLine[lineIndex] = '\0'; // indicate end of string to strcpy function
        finalStates[iterate] = malloc(stringSize * sizeof(char));
        strcpy(finalStates[iterate], readLine);
    }

    // now we can iterate the dfa states looking for updating the initial and final states
    // iteration will stop when searched all the dfa states or when it has updated the initial
    // and all the final states
    iterate = 0;
    int foundInit = 0;
    int foundFinals = 0;
    while (iterate < dfa->sizeStates || (foundInit == 0 && dfa->sizeFinals != foundFinals))
    {
        // compare strings looking for the initial state and update it when is found
        if (strcmp(dfa->states[iterate].state, dfa->initialState.state) == 0)
        {
            dfa->states[iterate].initial = 1;
            foundInit = 1;
        }

        // iterates through final states array looking for the final state and update them when are foundF
        for (int i = 0; i < dfa->sizeFinals; i++)
        {
            if (strcmp(dfa->states[iterate].state, finalStates[i]) == 0)
            {
                dfa->states[iterate].final = 1;
                foundFinals++;
            }
            // update the initial state if its also final
            if (strcmp(dfa->initialState.state, finalStates[i]) == 0)
                dfa->initialState.final = 1;
        }
        iterate++;
    }

    fclose(entry);
}
