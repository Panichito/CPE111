cmake_minimum_required(VERSION 3.16)
project(rickrollaphobia C)

set(CMAKE_C_STANDARD 99)

add_executable(yes cmdGraphicEditor.c commandFunctions.c colorFunctions.c utility.c linkedListUtilMod.c linkedListQueueMod.c
        commandFunctions.h colorFunctions.h utility.h abstractQueueMod.h linkedListUtilMod.h drawImage.c drawImage.h helpMenu.c helpMenu.h cmdColorEditor.c)

