#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "DFA.h"

void complementDFA(DFA *dfa);

void productDFA(DFA *dfa1, DFA *dfa2, DFA *product, char operation);

void copyDFA(DFA model, DFA *newDFA);

#endif
