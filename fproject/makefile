EXECUTABLES=cmdGraphicEditor$(EXECEXT) cmdColorEditor$(EXECEXT)

all : $(EXECUTABLES)

utility.o : utility.c utility.h
	gcc -c utility.c utility.h -std=c99 -D_GNU_SOURCE

linkedListUtilMod.o : linkedListUtilMod.c linkedListUtilMod.h
	gcc -c linkedListUtilMod.c linkedListUtilMod.h -std=c99 -D_GNU_SOURCE

linkedListQueueMod.o : linkedListQueueMod.c abstractQueueMod.h
	gcc -c linkedListQueueMod.c abstractQueueMod.h -std=c99 -D_GNU_SOURCE

helpMenu.o : helpMenu.c helpMenu.h
	gcc -c helpMenu.c helpMenu.h -std=c99 -D_GNU_SOURCE

colorFunctions.o : colorFunctions.c colorFunctions.h
	gcc -c colorFunctions.c colorFunctions.h -std=c99 -D_GNU_SOURCE

commandFunctions.o : commandFunctions.c commandFunctions.h
	gcc -c commandFunctions.c commandFunctions.h -std=c99 -D_GNU_SOURCE

drawImage.o : drawImage.c drawImage.h
	gcc -c drawImage.c drawImage.h -std=c99 -D_GNU_SOURCE

cmdGraphicEditor.o : cmdGraphicEditor.c
	gcc -c cmdGraphicEditor.c -std=c99 -D_GNU_SOURCE

cmdGraphicEditor$(EXECEXT) : cmdGraphicEditor.o drawImage.o commandFunctions.o colorFunctions.o linkedListQueueMod.o linkedListUtilMod.o utility.o helpMenu.o
	gcc -o cmdGraphicEditor$(EXECEXT) cmdGraphicEditor.o drawImage.o commandFunctions.o colorFunctions.o linkedListQueueMod.o linkedListUtilMod.o utility.o helpMenu.o -lgd -lpng -lz -ljpeg -lfreetype -lm -std=c99 -D_GNU_SOURCE

cmdColorEditor$(EXECEXT): cmdColorEditor.c colorFunctions.o linkedListUtilMod.o linkedListQueueMod.o utility.o helpMenu.o
	gcc -o cmdColorEditor$(EXECEXT) cmdColorEditor.c colorFunctions.o linkedListUtilMod.o linkedListQueueMod.o utility.o helpMenu.o -std=c99 -D_GNU_SOURCE

clean :
	-rm *.o
	-rm *.gch
	-rm $(EXECUTABLES)