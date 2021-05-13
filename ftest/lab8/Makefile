# Makefile for demo programs for Lecture 8
# Hash tables

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= hashTester$(EXECEXT) applyHash$(EXECEXT) applyHash2$(EXECEXT)

all : $(EXECUTABLES)

hashTester.o :	hashTester.c abstractHashTable.h
	gcc -c hashTester.c

chainedHashTable.o :	chainedHashTable.c abstractHashTable.h
	gcc -c chainedHashTable.c

timeFunction.o : timeFunctions.c timeFunctions.h
	gcc -c timeFunctions.c

hashDicionary.o : hashDictionary.c abtractHashTable.h timeFunction.h
	gcc -c hashDictionary.c

hashDictionary$(EXECEXT) : hashDictionary.o chainedHashTable.o timeFunction.o
	gcc -o hashDictionary$(EXECEXT) hashDictionary.o chainedHashTable.o timeFunctions.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
