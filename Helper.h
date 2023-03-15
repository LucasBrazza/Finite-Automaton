#ifndef HELPER_H
#define HELPER_H

#include "DFA.h"

int seekParam(DFA *dfa, char *path, int parameter);

int seekLine(int line, char *path);

void freeDFA(DFA *dfa);

void printWord(char *word);

void printDFA(DFA *dfa1);

#endif
