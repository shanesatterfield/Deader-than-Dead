all: Level_Editor

Level_Editor: Level_Editor.o Button.o
	g++ -o Level_Editor Level_Editor.o Button.o -lSDL -lSDL_image -lSDL_ttf

Level_Editor.o: Level_Editor.cpp
	g++ -c Level_Editor.cpp
	mv Level_Editor.o src

Button.o: src/Button.cpp
	g++ -c Button.cpp