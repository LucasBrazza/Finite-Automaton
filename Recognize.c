#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Recognize.h"
#include "Input.h"
#include "Helper.h"

// Função que recebe uma palavra e um DFA e retorna 1 se a palavra é aceita pelo DFA, 0 caso contrário
int acceptsWord(char *word, DFA *dfa)
{

    char currentState[stringSize] = ""; // Estado inicial
    strcpy(currentState, dfa->initialState.state);
    int i, j, k;
    int foundTransition;
    int lenWord = strlen(word);
    char auxChar;

    // Percorre a palavra
    for (i = 0; i < lenWord; i++)
    {
        foundTransition = 0;
        auxChar = word[i];
        if (auxChar == '\n')
            break;
        // Procura uma transição com origem no estado atual e com o elemento atual da palavra
        for (j = 0; j < dfa->sizeTransitions; j++)
        {

            if (strcmp(dfa->transitions[j].origin, currentState) == 0 && atoi(dfa->transitions[j].transition) == (auxChar - '0'))
            {
                // Se encontrou uma transição, atualiza o estado atual
                for (k = 0; k < dfa->sizeStates; k++)
                {

                    if (strcmp(dfa->states[k].state, dfa->transitions[j].destiny) == 0)
                    {
                        strcpy(currentState, dfa->states[k].state);
                        foundTransition = 1;
                        break;
                    }
                }
                break;
            }
        }

        // Se não encontrou uma transição, a palavra não é aceita pelo DFA
        if (!foundTransition)
        {
            return 0;
        }
    }

    // Verifica se o estado atual é um estado final
    for (i = 0; i < dfa->sizeStates; i++)
    {
        if (strcmp(currentState, dfa->states[i].state) == 0)
        {
            if (dfa->states[i].final == 1)
            {
                return 1;
            }
            else
                return 0;
        }
    }

    return 0;
}

// Função que simula o DFA com as palavras do arquivo de teste e grava o resultado no arquivo de saída
void simulateDFA(char *dfaFile, char *inputFile, char *outputFile)
{
    DFA dfa;
    generateDFA(&dfa, dfaFile);
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");

    if (input == NULL || output == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }
    char word[stringSize];
    int accepted;

    // Lê cada palavra do arquivo de teste
    while (fgets(word, stringSize, input))
    {
        // Verifica se a palavra é aceita pelo DFA
        accepted = acceptsWord(word, &dfa);
        // Escreve o resultado no arquivo de saída
        if (accepted == 1)
            fprintf(output, "1\n");
        else
            fprintf(output, "0\n");
    }
    fclose(input);
    fclose(output);
    freeDFA(&dfa);
}