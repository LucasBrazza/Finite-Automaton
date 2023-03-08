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
    States initialState;
} DFA;

void clearString(char *str)
{
    strcpy(str, "                                                                     "); // clears string
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
    {
        exit(1);
    }

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
    char finalStates[dfa->sizeFinals][20];
    for (iterate = 0; iterate < dfa->sizeFinals; iterate++)
    {
        lineIndex = 0; // reset index
        clearString(readLine);
        // reads line
        auxChar = getc(entry);
        while (auxChar != EOF)
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

// 1 - n estados
// 2 - estados
// 3 - n elementos alfabeto
// 4 - alfabeto
// 5 - n transições
// 6 - transições
// 7 - estado estado inicial
// 8 - n finais
// 9 - finais
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

    fputs(strcat(dfa.initialState.state, "\n"), file);

    itoa(dfa.sizeFinals, aux, 10);
    fputs(strcat(aux, "\n"), file);

    for (i = 0; i < dfa.sizeStates; i++)
    {
        if (dfa.states[i].final == 1)
            fputs(dfa.states[i].state, file);
    }

    fclose(file);
}

void productDFA(DFA *dfa1, DFA *dfa2, DFA *product, char operation)
{
    // fazer verificações para ver se o produto é possivel
    product->sizeStates = dfa1->sizeStates * dfa2->sizeStates;
    product->sizeFinals = 0;
    product->states = (States *)malloc(product->sizeStates * sizeof(States));

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
    printWord(dfa1->alphabet[1].element);
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

int main()
{
    DFA dfa1, dfa2, dfa3;

    generateDFA(&dfa1, "../a1.txt");
    generateDFA(&dfa2, "../a2.txt");

    productDFA(&dfa1, &dfa2, &dfa3, 'u');
    // printDFA(dfa3);
    dfaToFile(dfa3, "../convertToFile.txt");

    // dfaToFile(dfa1, "../test-complemente.txt");

    // FILE *f = fopen("../test.txt", "r");

    // fclose(f);
    freeDFA(dfa1);
    freeDFA(dfa2);
    freeDFA(dfa3);

    return 0;
}