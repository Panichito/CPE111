# Makefile for demo programs for Lecture 9
# Heaps & priority queues

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= heapTester$(EXECEXT) 

all : $(EXECUTABLES)

heapTester.o :	heapTester.c abstractHeap.h
	gcc -c heapTester.c

arrayHeap.o :	arrayHeap.c abstractHeap.h
	gcc -c arrayHeap.c

heapTester$(EXECEXT) : heapTester.o arrayHeap.o 
	gcc -o heapTester$(EXECEXT) heapTester.o arrayHeap.o 

clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
