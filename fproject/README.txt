CPE111 PROJECT by RICKROLLAPHOBIA

Member:
Tunwa Satianrapapong Por 63070503419
Panithi Suwanno Big 63070503426
Pada Cherdchoothai Da 63070503439
Muhammud Binhar Mud 63070503444

Files from Aj.sally:
    linkedListUtil.c (MODDED)
    linkedListQueue.c (MODDED)

Working files :
    every files except helpMenu.c/.h

How to use :

    libgd / gd.h is require to build this program
    the library can be install by running this command
        'sudo apt-get install libgd-dev'
    or getting it from https://github.com/libgd/libgd/releases

    Type 'make' to makefile , creating 2 executables
    - cmdGraphicEditor : Main program user can create, edit , save , load shape and color , then draw picture.
    - cmdColorEditor :  Standalone version of color functions , maintaining all the main functionality.

    Provided data files : Example of saved user command "stickman.sav" and drawing result "stickman.png"
                          Example of saved user color "userColor.dat"
                          Default color of the program "defaultColor.dat" *essential

   Example case :
   Run cmdGraphicEditor
   1. load stickman or load stickman.dat -> load the save file
   2. list -> show the details of each commands
   3. (Go in , type some command , have fun!)
   4. draw stickman.png -> draw the stickman

   Run cmdColorEditor
   -add some color
   -save it to file


Commands :
    all commands start with "-" is working

    [cmdGraphicEditor]

    -CreateImg [x] [y] , create the canvas (top-left is (0,0), bottom-right is (x-1,y-1)) *require to do before drawing
    -Background [color] , change background's color
    -Brush [size] , change brush size (pixel)
    -Circle/CircleFill [cx] [cy] [r] [color], create circle center at (cx,cy) with radius (r)
    -Line/LineDash [x1] [y1] [x2] [y2] [color], create line from (x1,y1) to (x2,y2)
    -Rectangle/RectangleFill [x1] [y1] [x2] [y2] [color] , create rectangle top-left (x1,y1) , bottom-right (x2,y2)
    -Triangle/TriangleFill [cx] [cy] [w] [h] [color], create triangle base center at (cx,cy) with width of (w) height of (h)
    -Diamond/DiamondFill [cx] [cy] [w] [h] [color], create diamond center at (cx,cy) with width of (w) height/depth of (h)
    -Ellipse/EllipseFill [cx] [cy] [rx] [ry] [color], create circle center at (cx,cy) with radius each axis (rx) and (ry)
    -Arc/ArcFilled [cx] [cy] [w] [rx] [ry] [e] [color], create arc center at (cx,cy) with radius each axis (rx) and (ry) arc-length (s) sector (e)
    -Polygon/PolygonOpen/PolygonFill [x1] [y1] [x2] [y2] .. [xn] [yn] [color], create polygon connecting with given coordinate in-order
     Variation of command , Fill - fill color inside the shape , Open - won't connect last dot to first dot

    -Draw [outputName] , create .png image with given instruction
    -List , show all the commands added by user , with index
    -Edit [index in list] [argument required for the shape], edit content of a command *can't change the shape
    -Move [index1] [index2], move item from position [index1] to position [index2]
    -Swap [index1] [index2], swap 2 item in list
    -Remove [index] , remove a command
    -Reset , clear everything , restart the program
    -Save [filename] , save instruction to file
    -Load [filename] , load instruction from file *added to existing commands
    -Color [List/Add/Edit/Delete/Save/Load] [Args] , use color commands *further information below
    *Help [command name], show detail of the command **not yet implement
    -Done , exit program

    [cmdColorEditor]

    - List , show all color
    - Add [name] [r] [g] [b] [a] , add new color to list with name and rgba value
    - Edit [name] [r] [g] [b] [a] , edit value of existing color
    - Delete [name] , delete color from list
    - Save [filename] , save user added color to file
    - Load [filename] , load custom color from file to list
    - Exit
