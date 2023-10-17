CFLAGS  = -Wall -ansi -pedantic -g

all: main.o Utilities.o MemoryStruct.o List.o Instructions.o Decoder.o  MemoryTables.o macro.o
	gcc $(CFLAGS) -o assembler main.o Utilities.o MemoryStruct.o List.o Instructions.o Decoder.o MemoryTables.o macro.o

#main
main.o: main.c
	gcc $(CFLAGS) -c main.c

#Utilities
Utilities.o: Utilities.c Utilities.h
	gcc $(CFLAGS) -c Utilities.c

#MemoryStruct
MemoryStruct.o: MemoryStruct.c MemoryStruct.h
	gcc $(CFLAGS) -c MemoryStruct.c

#List
List.o: List.c List.h
	gcc $(CFLAGS) -c List.c

#Instructions
Instructions.o: Instructions.c Instructions.h MemoryStruct.h
	gcc $(CFLAGS) -c Instructions.c

#Decoder
Decoder.o: Decoder.c Decoder.h
	gcc $(CFLAGS) -c Decoder.c

#MemoryTables
MemoryTables.o: MemoryTables.c MemoryTables.h
	gcc $(CFLAGS) -c MemoryTables.c

macro.o: macro.c macro.h
	gcc $(CFLAGS) -c macro.c

#clean o files and exec
clean:
	rm *.o
	rm -rf assembler
