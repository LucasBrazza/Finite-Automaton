afdtool: converter.o helper.o input.o main.o operations.o recognize.o
		cc -o afdtool main.o converter.o helper.o input.o operations.o recognize.o

main.o: main.c Operations.h Converter.c Helper.c Input.c DFA.h
		gcc -g -c main.c

converter.o: Converter.c Converter.h
		gcc -g -c Converter.c

operations.o: Operations.c Operations.h
		gcc -g -c Operations.c

helper.o: Helper.c Helper.h
		gcc -g -c Helper.c

input.o: Input.c Input.h
		gcc -g -c Input.c

recognize.o: Recognize.c Recognize.h
		gcc -g -c Recognize.c

clean:
	rm *.o *.gch
	rm operacoes