OBJS=main.cpp SDLmedia.cpp form.cpp libgeo/geometry.cpp objects.cpp
CC=g++
INCLUDE_PATHS=/SDL2-2.0.5/i686-w64-mingw32/include/SDL2 -I/freetype-2.7.1/build_1/include/freetype2 -I./libgeo
LIBRARY_PATHS=/SDL2-2.0.5/i686-w64-mingw32/lib -L/freetype-2.7.1/build_1/lib 
COMPILER_FLAGS=-std=c++11
LINKER_FLAGS=-lmingw32 -lSDL2main -lSDL2 -lfreetype -lSDL2_mixer -static-libgcc -static-libstdc++
OBJ_NAME=Demo.exe
all: $(OBJS)
	$(CC) $(OBJS) -I$(INCLUDE_PATHS) -L$(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
window: $(OBJS)
	$(CC) $(OBJS) -I$(INCLUDE_PATHS) -L$(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -mwindows -o $(OBJ_NAME)
