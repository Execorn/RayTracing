CXXFLAGS   = -Wall -O2 -std=c++17 -fopenmp

SFML_INCLUDE  = -IC:\SFML-2.5.1\include
SFML_LIB      = -LC:\SFML-2.5.1\lib
SFMLFLAGS     = -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

GCCFLAGS      = -lmingw -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
COMPILER      = g++

OBJ_FILES     = build/TColor_.o build/TSphere_.o build/TWindow_.o build/main.o build/TSceneIntersec_.o build/TScene_.o


execute: rtracing
	./build/rtracing

rtracing: main.o TColor_.o TSphere_.o TWindow_.o TSceneIntersec_.o TScene_.o
	$(COMPILER) $(SFML_LIB) $(OBJ_FILES) $(CXXFLAGS) $(SFMLFLAGS) -o build/rtracing.exe 


main.o: src/main.cpp
	$(COMPILER) $(SFML_INCLUDE) $(CXXFLAGS) -c src/main.cpp -o build/main.o

TScene_.o: src/TScene_.h src/TScene_.cpp
	$(COMPILER) $(SFML_INCLUDE) $(CXXFLAGS) -c src/TScene_.cpp  -o build/TScene_.o

TSceneIntersec_.o: src/TSceneIntersec_.h src/TSceneIntersec_.cpp
	$(COMPILER) $(SFML_INCLUDE) $(CXXFLAGS) -c src/TSceneIntersec_.cpp  -o build/TSceneIntersec_.o

TColor_.o: src/TColor_.h src/TColor_.cpp
	$(COMPILER) $(SFML_INCLUDE) $(CXXFLAGS) -c src/TColor_.cpp  -o build/TColor_.o

TSphere_.o: src/TSphere_.h src/TSphere_.cpp
	$(COMPILER) $(SFML_INCLUDE) $(CXXFLAGS) -c src/TSphere_.cpp -o build/TSphere_.o

TWindow_.o: src/TWindow_.h src/TWindow_.cpp
	$(COMPILER) $(SFML_INCLUDE) $(CXXFLAGS) -c src/TWindow_.cpp -o build/TWindow_.o