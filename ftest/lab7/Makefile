# Makefile for demo for Lab 7

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= dictionary$(EXECEXT) 

all : $(EXECUTABLES)

linkedListUtil.o : linkedListUtil.c linkedListUtil.h
	gcc -c linkedListUtil.c

dictionary.o : dictionary.c linkedListUtil.h
	gcc -c dictionary.c


dictionary$(EXECEXT) : dictionary.o linkedListUtil.o
	gcc -o dictionary$(EXECEXT) dictionary.o linkedListUtil.o


clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
