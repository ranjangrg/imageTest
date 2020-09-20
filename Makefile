COMPILER=g++

# for some standard libraries
CFLAGS=--std=c++14

SOURCES=./src/main.cpp
SOURCES+=./src/bmp.cpp
SOURCES+=./src/stb.cpp

OBJECTS=$(SOURCES:.cpp=.o)

MAIN_EXEC=main

main: $(SOURCES)
	$(COMPILER) $(CFLAGS) $(SOURCES) -g -o $(MAIN_EXEC)

clean:
	-@rm $(MAIN_EXEC) 2> /dev/null || true;
	