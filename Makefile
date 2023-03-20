trabFinal: converter.o helper.o input.o main.o 
		cc -o trabFinal main.o converter.o helper.o input.o

main.o: main.c Operations.h Converter.c Helper.c Input.c DFA.h
		gcc -g -c main.c

converter.o: Converter.c Converter.h
		gcc -g -c Converter.c

helper.o: Helper.c Helper.h
		gcc -g -c Helper.c

input.o: Input.c Input.h
		gcc -g -c Input.c

clean:
	rm *.o *.gch
	rm operacoes