# Mój plik makefile - wpisz 'make all' aby skompilować cały program
# (właściwie wystarczy wpisać 'make' - all jest domyślny jako pierwszy cel)
CC = gcc

all: main.o structure_and_list.o menu.o display_data.o
	$(CC) main.o structure_and_list.o menu.o display_data.o -o wifi_collector

main.o: main.c main.h
	$(CC) main.c -c -o main.o

structure_and_list.o: structure_and_list.c structure_and_list.h
	$(CC) structure_and_list.c -c -o structure_and_list.o

menu.o: menu.c menu.h
	$(CC) menu.c -c -o menu.o

display_data.o: display_data.c display_data.h
	$(CC) display_data.c -c -o display_data.o
