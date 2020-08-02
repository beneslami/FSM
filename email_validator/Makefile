TARGET:exe

exe: main.o fsm.o utils.o
	gcc -g main.o fsm.o -o exe

main.o:
	gcc -g -c main.c -o main.o

fsm.o:
	gcc -g -c ../fsm.c -o fsm.o

utils.o:
	gcc -g -c utils.c -o utils.o

clean:
	rm -rf main.o fsm.o utils exe
