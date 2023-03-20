#include <stdlib.h>
#include "Recognize.h"
#include "Recognize.c"
#include "Operations.h"
#include "Converter.c"
#include "Helper.c"
#include "Input.c"
#include "DFA.h"

int main()
{
    DFA dfa1, dfa2, dfa3, dfa4;

    // generateDFA(&dfa1, "../a1.txt");
    // generateDFA(&dfa2, "../a2.txt");
    generateDFA(&dfa4, "a2.txt");

    // productDFA(&dfa1, &dfa2, &dfa3, 'u');
    printDFA(&dfa4);
    //   finalsToString(dfa3);
    // simulateDFA("test.txt","palavras.txt","palavras-reconhecidas.txt");
    // printf("%d",dfa4.states[1].initial);
    dfaToDOT("a2.dot", &dfa4);
    //  dfaToFile(dfa1, "../test-complemente.txt");

    // FILE *f = fopen("../test.txt", "r");

    // fclose(f);
    // freeDFA(&dfa1);
    // freeDFA(&dfa2);
    // freeDFA(&dfa3);
    // freeDFA(&dfa4);

    return 0;
}
