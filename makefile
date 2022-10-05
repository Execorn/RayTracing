CC       := g++
CXXFLAGS := -Wall -Werror -O2 -std=c++17 -fopenmp

LDLIB     = -LC:\SFML-2.5.1\lib
LDINCLUDE = -IC:\SFML-2.5.1\include
LDFLAGS   = -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

SRCDIRS = ./src/
BINDIR  = ./build/

SOURCES = $(wildcard $(SRCDIRS)*.cpp)
OBJECTS = $(addprefix $(BINDIR),$(notdir $(SOURCES:.cpp=.o)))

EXECUTABLE = RayTracing.exe

execute: $(EXECUTABLE)
	./RayTracing.exe

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDLIB) $(OBJECTS) $(CXXFLAGS) $(LDFLAGS) -o $@

$(BINDIR)%.o: $(SRCDIRS)%.cpp
	$(CC) $(LDINCLUDE) -c $(CXXFLAGS) $< -o $@

.PHONY: clean, mkdirs

mkdirs:
	mkdir $(BINDIR) $(SRCDIRS)

clean: 
	del $(BINDIR)*.o