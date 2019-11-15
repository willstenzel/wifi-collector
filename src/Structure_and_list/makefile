# Mój plik makefile - wpisz 'make all' aby skompilować cały program
# (właściwie wystarczy wpisać 'make' - all jest domyślny jako pierwszy cel)
CC = gcc  

all: main.o structure_and_list.o
	$(CC) main.o structure_and_list.o -o wifi_collector

main.o: main.c main.h
	$(CC) main.c -c -o main.o

structure_and_list.o: structure_and_list.c
	$(CC) structure_and_list.c -c -o structure_and_list.o