# Mój plik makefile - wpisz 'make all' aby skompilować cały program
# (właściwie wystarczy wpisać 'make' - all jest domyślny jako pierwszy cel)
CC = gcc
CFLAGS=-Wall -Wextra

all: main.o structure_and_list.o menu.o display_data.o wifi_collector.o io.o
	$(CC) main.o structure_and_list.o menu.o wifi_collector.o display_data.o io.o -o wifi_collector $(CFLAGS)

main.o: main.c main.h
	$(CC) main.c -c -o main.o $(CFLAGS)

structure_and_list.o: structure_and_list.c structure_and_list.h
	$(CC) structure_and_list.c -c -o structure_and_list.o $(CFLAGS)

menu.o: menu.c menu.h
	$(CC) menu.c -c -o menu.o $(CFLAGS)

wifi_collector.o: wifi_collector.c wifi_collector.h
	$(CC) wifi_collector.c -c -o wifi_collector.o $(CFLAGS)

display_data.o: display_data.c display_data.h
	$(CC) display_data.c -c -o display_data.o $(CFLAGS)

io.o: io.c io.h
	$(CC) io.c -c -o io.o $(CFLAGS)
