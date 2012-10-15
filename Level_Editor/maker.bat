g++ -c Level_Editor.cpp
move Level_Editor.o src
cd src
mkdir Object_Folder
move Level_Editor.o Object_Folder
g++ -c *.cpp
move *.o Object_Folder
cd Object_Folder
g++ -o Level_Editor.exe *.o -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf
move Level_Editor.exe ..
del *.o
cd ..
move Level_Editor.exe ..
rmdir Object_Folder
cd ..