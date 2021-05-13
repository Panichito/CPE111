# Makefile for demo programs for Lecture 3 
# Queues and stacks

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= queueTesterA$(EXECEXT) stackTesterL$(EXECEXT) simpleCalc$(EXECEXT) 

all : $(EXECUTABLES)

arrayQueue.o :	arrayQueue.c abstractQueue.h
	gcc -c arrayQueue.c

queueTester.o :	queueTester.c abstractQueue.h
	gcc -c queueTester.c

linkedListStack.o : linkedListStack.c abstractStack.h
	gcc -c linkedListStack.c

integerStack.o : integerStack.c integerStack.h
	gcc -c integerStack.c

stackTester.o :	stackTester.c abstractStack.h
	gcc -c stackTester.c

simpleCalc.o : simpleCalc.c abstractStack.h
	gcc -c simpleCalc.c

# queueTester using the arrayQueue implementation of the abstract queue
queueTesterA$(EXECEXT) : queueTester.o arrayQueue.o
	gcc -o queueTesterA$(EXECEXT) queueTester.o arrayQueue.o

# stackTester using the linkedListStack implementation of the abstract stack
stackTesterL$(EXECEXT) : stackTester.o linkedListStack.o
	gcc -o stackTesterL$(EXECEXT) stackTester.o linkedListStack.o

# simpleCalc uses the linkedListStack implementation of the abstract stack
simpleCalc$(EXECEXT) : simpleCalc.o linkedListStack.o
	gcc -o simpleCalc$(EXECEXT) simpleCalc.o linkedListStack.o


clean : 
	-rm *.o
	-rm queueTesterA$(EXECEXT) 
	-rm stackTesterL$(EXECEXT)
	-rm simpleCalc$(EXECEXT)

