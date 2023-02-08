#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    States *states;
    Alphabet *alphabet;
    Transition *transitions;
} DFA;

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
    {
        exit(1);
    }

    // saves all states of dfa
    int iterate;
    for (iterate = 0; iterate < dfa->sizeStates; iterate++)
    {
        lineIndex = 0;                                                                              // reset index
        strcpy(readLine, "                                                                      "); // clears string

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

    // read the seconf parameter (number of elements in alphabet)
    lineIndex = 0;                                                                              // reset index
    strcpy(readLine, "                                                                      "); // clears string
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

    // saves all alphabet elements of dfa
    for (iterate = 0; iterate < dfa->sizeAlphabet; iterate++)
    {
        lineIndex = 0;                                                                              // reset index
        strcpy(readLine, "                                                                      "); // clears string

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

    // read the third parameter (number of transitions)
    lineIndex = 0;                                                                              // reset index
    strcpy(readLine, "                                                                      "); // clears string
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
    int aux;
    auxChar = getc(entry);
    printf("\n\n\n=====================\n\n\n");
    for (iterate = 0; iterate < dfa->sizeTransitions; iterate++)
    {

        printf("%d-", iterate);

        strcpy(readLine, "                                                                      "); // clears string
        lineIndex = 0;                                                                              // reset index
        if (auxChar != ' ' && auxChar != '\n')
            readLine[lineIndex++] = auxChar;
        else
            lineIndex++;

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
                    strcpy(dfa->transitions[iterate].origin, readLine);
                }
                if (aux == 1)
                {
                    strcpy(dfa->transitions[iterate].transition, readLine);
                }
                aux++;
                strcpy(readLine, "                                                                      "); // clears string
                lineIndex = 0;                                                                              // reset index
            }
            auxChar = getc(entry);
            if (auxChar != ' ' && auxChar != '\n')
                readLine[lineIndex++] = auxChar;
            else
                lineIndex++;
        }
        if (auxChar == '\n')
        {
            strcpy(dfa->transitions[iterate].destiny, readLine);
            strcpy(readLine, "                                                                      "); // clears string
            lineIndex = 0;                                                                              // reset index
            auxChar = getc(entry);
        }
    }
    printf("\n\n\n=====================\n\n\n");

    // read the fourth parameter (inicial state)
    lineIndex = 0;                                                                              // reset index
    strcpy(readLine, "                                                                      "); // clears string
    auxChar = getc(entry);
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0'; // indicate end of string to strcpy function

    // creates a varable with the initial state
    char initialState[lineIndex];
    strcpy(initialState, readLine);

    // read the fifth parameter (number of final states)
    lineIndex = 0;                                                                              // reset index
    strcpy(readLine, "                                                                      "); // clears string
    auxChar = getc(entry);
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0';           // indicate end of string to atoi function
    int sizeFinalStates = atoi(readLine); // convert string to int

    // creates a array with all the final states
    char finalStates[sizeFinalStates][20];
    for (iterate = 0; iterate < sizeFinalStates; iterate++)
    {
        lineIndex = 0;                                                                              // reset index
        strcpy(readLine, "                                                                      "); // clears string

        // reads line
        auxChar = getc(entry);
        while (auxChar != '\n')
        {
            readLine[lineIndex++] = auxChar;
            auxChar = getc(entry);
        }

        readLine[lineIndex] = '\0'; // indicate end of string to strcpy function
        strcpy(finalStates[iterate], readLine);
    }

    // now we can iterate the dfa states looking for updating the initial and final states
    // iteration will stop when searched all the dfa states or when it has updated the initial
    // and all the final states
    iterate = 0;
    int foundInit = 0;
    int foundFinals = 0;
    while (iterate < dfa->sizeStates || (foundInit == 0 && sizeFinalStates != foundFinals))
    {
        // compare strings looking for the initial state and update it when is found
        if (strcmp(dfa->states[iterate].state, initialState) == 0)
        {
            dfa->states[iterate].initial = 1;
            foundInit = 1;
        }

        // iterates through final states array looking for the final state and update them when are foundF
        for (int i = 0; i < sizeFinalStates; i++)
        {
            if (strcmp(dfa->states[iterate].state, finalStates[i]) == 0)
            {
                dfa->states[iterate].final = 1;
                foundFinals++;
            }
        }
        iterate++;
    }

    fclose(entry);
}

int main()
{
    DFA dfa1;

    generateDFA(&dfa1, "../test.txt");

    printf("\nn states %d", dfa1.sizeStates);
    printf("\nn aplhabet %d", dfa1.sizeAlphabet);
    printf("\nn transitions %d", dfa1.sizeTransitions);
    printf("\nfinal: %d\n", dfa1.states[0].final);

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            printf("%c-", dfa1.transitions[j].destiny[i]);
        }
        printf("\n");
    }
    printf("\n\nCODE ENDED\n");
    return 0;
}