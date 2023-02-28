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
    int sizeFinals;
    States *states;
    Alphabet *alphabet;
    Transition *transitions;
    //State *initial;
} DFA;

void generateDFA(DFA *dfa, char *path /*, char *initial*/)
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
    for (iterate = 0; iterate < dfa->sizeTransitions; iterate++)
    {
        strcpy(readLine, "                                                                      "); // clears string
        lineIndex = 0;                                                                              // reset index
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
                strcpy(readLine, "                                                                      "); // clears string
                lineIndex = 0;                                                                              // reset index
            }
            if (auxChar != ' ' && auxChar != '\n')
            {
                readLine[lineIndex] = auxChar;
                lineIndex++;
            }
            auxChar = getc(entry);
        }
        if (auxChar == '\n')
        {
            readLine[lineIndex++] = '\0';
            strcpy(dfa->transitions[iterate].destiny, readLine);
            strcpy(readLine, "                                                                      "); // clears string
            lineIndex = 0;                                                                              // reset index
            auxChar = getc(entry);
        }
    }

    // read the fourth parameter (inicial state)
    lineIndex = 0;                                                                              // reset index
    strcpy(readLine, "                                                                      "); // clears string
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0'; // indicate end of string to strcpy function

    // creates a varable with the initial state
    char initialState[lineIndex];
    strcpy(initialState, readLine);
    //strcpy(initial, readLine);


    // read the fifth parameter (number of final states)
    lineIndex = 0;                                                                              // reset index
    strcpy(readLine, "                                                                      "); // clears string
    auxChar = getc(entry);
    while (auxChar != '\n')
    {
        readLine[lineIndex++] = auxChar;
        auxChar = getc(entry);
    }
    readLine[lineIndex] = '\0';       // indicate end of string to atoi function
    dfa->sizeFinals = atoi(readLine); // convert string to int

    // creates a array with all the final states
    char finalStates[dfa->sizeFinals][20];
    for (iterate = 0; iterate < dfa->sizeFinals; iterate++)
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
    while (iterate < dfa->sizeStates || (foundInit == 0 && dfa->sizeFinals != foundFinals))
    {
        // compare strings looking for the initial state and update it when is found
        if (strcmp(dfa->states[iterate].state, initialState) == 0)
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
        }
        iterate++;
    }

    fclose(entry);
}

void copyDFA(DFA model, DFA *new)
{
    new->sizeStates = model.sizeStates;
    new->states = (States *)malloc(new->sizeStates * sizeof(States));

    new->sizeAlphabet = model.sizeAlphabet;
    new->alphabet = (Alphabet *)malloc(new->sizeStates * sizeof(Alphabet));

    new->sizeTransitions = model.sizeTransitions;
    new->transitions = (Transition *)malloc(new->sizeStates * sizeof(Transition));
    int i;
    for (i = 0; i < new->sizeStates; i++)
    {
        strcpy(new->states[i].state, model.states[i].state);
        new->states[i].initial = model.states[i].initial;
        new->states[i].final = model.states[i].final;
    }
    for (i = 0; i < new->sizeAlphabet; i++)
    {
        strcpy(new->alphabet[i].element, model.alphabet[i].element);
    }
    for (i = 0; i < new->sizeTransitions; i++)
    {
        strcpy(new->transitions[i].origin, model.transitions[i].origin);
        strcpy(new->transitions[i].destiny, model.transitions[i].destiny);
        strcpy(new->transitions[i].transition, model.transitions[i].transition);
    }
}

void complementDFA(DFA *dfa)
{
    for (int i = 0; i < dfa->sizeStates; i++)
    {
        if (dfa->states[i].final == 0)
            dfa->states[i].final = 1;
        else if (dfa->states[i].final == 1)
            dfa->states[i].final = 0;
    }
}

void freeDFA(DFA dfa)
{
    free(dfa.states);
    free(dfa.transitions);
    free(dfa.alphabet);
}

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

void printDFA(DFA dfa1)
{
    printf("\nn states %d", dfa1.sizeStates);
    for (int i = 0; i < dfa1.sizeStates; i++)
    {
        printWord(dfa1.states[i].state);
        printf(" - initial %d - final %d", dfa1.states[i].initial, dfa1.states[i].final);
    }
    printf("\nn alphabet %d\n", dfa1.sizeAlphabet);
    for (int i = 0; i < dfa1.sizeAlphabet; i++)
    {
        printWord(dfa1.alphabet[i].element);
    }
    printf("\nn transitions %d", dfa1.sizeTransitions);
    for (int j = 0; j < dfa1.sizeTransitions; j++)
    {
        printf("\n");
        printWord(dfa1.transitions[j].origin);
        printWord(dfa1.transitions[j].transition);
        printWord(dfa1.transitions[j].destiny);
    }
}

void dfaToFile(DFA dfa, char *relativePath)
{
    FILE *file = fopen(relativePath, "w");
    char aux[50];
    itoa(dfa.sizeStates, aux, 10);
    fputs(strcat(aux, "\n"), file);
    int i;

    for (i = 0; i < dfa.sizeStates; i++)
        fputs(strcat(dfa.states[i].state, "\n"), file);

    itoa(dfa.sizeAlphabet, aux, 10);
    fputs(strcat(aux, "\n"), file);

    for (i = 0; i < dfa.sizeAlphabet; i++)
        fputs(strcat(dfa.alphabet[i].element, "\n"), file);

    itoa(dfa.sizeTransitions, aux, 10);
    fputs(strcat(aux, "\n"), file);

    for (i = 0; i < dfa.sizeTransitions; i++)
    {
        fputs(strcat(dfa.transitions[i].origin, " "), file);
        fputs(strcat(dfa.transitions[i].transition, " "), file);
        fputs(strcat(dfa.transitions[i].destiny, "\n"), file);
    }

    int foundInit = 0;
    i = 0;
    while (i < dfa.sizeStates || foundInit == 0)
    {
        // compare strings looking for the initial state and update it when is found
        if (dfa.states[i].initial == 1)
        {
            fputs(dfa.states[i].state, file);
            foundInit = 1;
        }
        i++;
    }

    itoa(dfa.sizeFinals, aux, 10);
    fputs(strcat(aux, "\n"), file);

    for (i = 0; i < dfa.sizeStates; i++)
    {
        if (dfa.states[i].final == 1)
            fputs(strcat(dfa.states[i].state, "\n"), file);
    }

    fclose(file);
}

void productDFA(char dfa1[100], char dfa2[100], char operation){
    DFA result;
    char *initDFA1, *initDFA2;
    


    transitions = (Transition *)malloc(dfa->sizeTransitions * sizeof(Transition));
    
    result.state = (States*) malloc(sizeof(States));
    //para pegar o estado inicial devemos verificar na posição do arquivo correta
    

    //alocar state
    // definir estado inicial 
    // iterar entre transições 
    // definir estados equivalentes
    // um estado equivalente consitem em um mesmo estado de origem que leva a um estado final
    // estados equivalentes tem uma mesma origem com mesma transição
    // ter um array auxiliar de strings para armazenar os multiplos estados 

}

int main()
{
    DFA dfa1;

    generateDFA(&dfa1, "../test.txt");

    dfaToFile(dfa1, "../test-complemente.txt");

    freeDFA(dfa1);

    return 0;
}