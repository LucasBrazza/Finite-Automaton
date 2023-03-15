#ifndef CONVERTER_H
#define CONVERTER_H

#include "DFA.h"

char *finalsToString(DFA *dfa);

void dfaToDOT(char *path, DFA *dfa);

void dfaToFile(DFA *dfa, char *relativePath);

#endif

