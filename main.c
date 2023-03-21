#include <stdlib.h>
#include <string.h>
#include "Recognize.h"
#include "Operations.h"
#include "Converter.h"
#include "Helper.h"
#include "Input.h"

// #include "Recognize.c"
// #include "Operations.c"
// #include "Converter.c"
// #include "Helper.c"
// #include "Input.c"

#include "DFA.h"

int main(int argc, char *argv[])
{

    if(strcmp(argv[1], "--dot") == 0 && strcmp(argv[3], "--output") == 0){
        DFA dfa1;
        generateDFA(&dfa1, argv[2]);
        dfaToDOT(argv[4], &dfa1);
        freeDFA(&dfa1);

    }else{
        if(strcmp(argv[1], "--complemento") == 0 && strcmp(argv[3], "--output") == 0){
            DFA dfa1;
            generateDFA(&dfa1, argv[2]);
            complementDFA(&dfa1);
            dfaToFile(&dfa1, argv[4]);
            freeDFA(&dfa1);

        }else{
            if(strcmp(argv[1], "--intersecao") == 0 && strcmp(argv[4], "--output") == 0){
            DFA dfa1, dfa2, dfa3;
            generateDFA(&dfa1, argv[2]);
            generateDFA(&dfa2, argv[3]);
            productDFA(&dfa1, &dfa2, &dfa3, 'i');
            dfaToFile(&dfa1, argv[5]);
            freeDFA(&dfa1);
            freeDFA(&dfa2);
            freeDFA(&dfa3);
            }else{
                if(strcmp(argv[1], "--uniao") == 0 && strcmp(argv[4], "--output") == 0){
                DFA dfa1, dfa2, dfa3;
                generateDFA(&dfa1, argv[2]);
                generateDFA(&dfa2, argv[3]);
                productDFA(&dfa1, &dfa2, &dfa3, 'u');
                dfaToFile(&dfa1, argv[5]);
                freeDFA(&dfa1);
                freeDFA(&dfa2);
                freeDFA(&dfa3);
                }else{
                    if(strcmp(argv[1], "--reconhecer") == 0 && strcmp(argv[4], "--output") == 0){
                        simulateDFA(argv[2], argv[3], argv[5]);
                    }
                }
            }


        }
    }

        // DFA dfa1;
        // generateDFA(&dfa1, "a2.txt");
        // complementDFA(&dfa1);
        // dfaToFile(&dfa1, "comp_a2.txt");
        // freeDFA(&dfa1);


    // DFA dfa1, dfa2, dfa3, dfa4;

    // generateDFA(&dfa1, "a1.txt");
    // generateDFA(&dfa2, "../a2.txt");
    // generateDFA(&dfa4, "a2.txt");

    // productDFA(&dfa1, &dfa2, &dfa3, 'u');
    // printDFA(&dfa4);
    //   finalsToString(dfa3);
    // simulateDFA("test.txt","palavras.txt","rec_test_ide.txt");
    // printf("%d",dfa4.states[1].initial);
    // dfaToDOT("test_rob.dot", &dfa1);
    //  dfaToFile(dfa1, "../test-complemente.txt");

    // FILE *f = fopen("../test.txt", "r");

    // fclose(f);
    // freeDFA(&dfa1);
    // freeDFA(&dfa2);
    // freeDFA(&dfa3);
    // freeDFA(&dfa4);

    return 0;
}
