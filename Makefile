all: Ageron


Ageron: build/Ageron.o \
		build/Game.o \
		build/Entity.o \
		build/Renderer.o \
		build/KeyHandler.o

	g++ -std=c++11 -lSDL2 -lSDL2_image \
		build/Ageron.o \
		build/Game.o \
		build/Entity.o \
		build/Renderer.o \
		build/KeyHandler.o \
			-o Ageron


# Big objects
build/Ageron.o: src/Ageron.cpp
	g++ -std=c++11 -c src/Ageron.cpp -o build/Ageron.o

build/Game.o: src/Game.cpp src/Game.h
	g++ -std=c++11 -c src/Game.cpp -o build/Game.o


# Game objects
build/Entity.o: src/Entity.cpp src/Entity.h
	g++ -std=c++11 -c src/Entity.cpp -o build/Entity.o


# Engine objects
build/Renderer.o: src/Renderer.cpp src/Renderer.h
	g++ -std=c++11 -c src/Renderer.cpp -o build/Renderer.o

build/KeyHandler.o: src/KeyHandler.cpp src/KeyHandler.h
	g++ -std=c++11 -c src/KeyHandler.cpp -o build/KeyHandler.o



clean:
	rm Ageron
	rm build/*
