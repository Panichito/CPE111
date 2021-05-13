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

EXECUTABLES= simpleTreeTester$(EXECEXT) simpleBinaryTreeTest$(EXECEXT) twelveDays$(EXECEXT) sillyRecursion$(EXECEXT) 

all : $(EXECUTABLES)

linkedListQueue.o : linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

simpleBinaryTree.o : simpleBinaryTree.c simpleBinaryTree.h
	gcc -c simpleBinaryTree.c

simpleTreeTester.o : simpleTreeTester.c simpleBinaryTree.h
	gcc -c simpleTreeTester.c

simpleBinaryTreeTest$(EXECEXT) : simpleBinaryTree.c linkedListQueue.o \
				 simpleBinaryTree.h
	gcc -DDEBUG -o simpleBinaryTreeTest$(EXECEXT) simpleBinaryTree.c \
			linkedListQueue.o

simpleTreeTester$(EXECEXT) : simpleTreeTester.o simpleBinaryTree.o \
				linkedListQueue.o
	gcc -o simpleTreeTester$(EXECEXT) simpleTreeTester.o simpleBinaryTree.o\
				linkedListQueue.o

twelveDays$(EXECEXT) : twelveDays.c 
	gcc -o twelveDays$(EXECEXT) twelveDays.c

sillyRecursion$(EXECEXT) : sillyRecursion.c 
	gcc -o sillyRecursion$(EXECEXT) sillyRecursion.c

clean : 
	-rm *.o
	-rm $(EXECUTABLES)
        
