
CC=g++
CFLAGS= -std=c++11 -lglfw -lGLEW -lGLU -lGL -Iinclude

# DEPS = init.h math.h

bin/main.o: src/main.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

bin/init.o: src/init.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

bin/math.o: src/math.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

bin/cube.o: src/cube.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

bin/window.o: src/window.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

build : bin/main.o bin/init.o bin/math.o bin/cube.o 
	$(CC) -o main bin/main.o bin/init.o bin/math.o bin/cube.o $(CFLAGS)
