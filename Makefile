all: solver.c 
	gcc -o solver solver.c -Ilib -Llib -lalgorithms 
