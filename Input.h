#ifndef INPUT_H
#define INPUT_H

#include "DFA.h"

void clearString(char *str);

void saveStates(DFA *dfa, FILE *entry, char auxChar, int iterate, int lineIndex, char *readLine);

void saveAlphabet(DFA *dfa, FILE *entry, char auxChar, int iterate, int lineIndex, char *readLine);

void saveTransitions(DFA *dfa, FILE *entry, char auxChar, int iterate, int lineIndex, char *readLine);

void generateDFA(DFA *dfa, char *path);

#endif
