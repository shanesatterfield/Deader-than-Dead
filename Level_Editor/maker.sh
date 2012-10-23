#! /bin/bash

g++ -g -c Level_Editor.cpp
mv Level_Editor.o src
cd src
mkdir Object_Files
g++ -g -c *.cpp
mv *.o Object_Files
cd Object_Files
g++ -o Level_Editor *.o -lSDL -lSDL_image -lSDL_ttf
mv Level_Editor ../..
rm *.o
cd ../
rmdir Object_Files
cd ..
