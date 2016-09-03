all: Ageron


Ageron: build/Ageron.o \
		build/Game.o \
		build/Renderer.o \
		build/KeyHandler.o

	g++ -lSDL2 -lSDL2_image \
		build/Ageron.o \
		build/Game.o \
		build/Renderer.o \
		build/KeyHandler.o \
			-o Ageron


build/Ageron.o: src/Ageron.cpp
	g++ -c src/Ageron.cpp -o build/Ageron.o

build/Game.o: src/Game.cpp src/Game.h
	g++ -c src/Game.cpp -o build/Game.o



build/Renderer.o: src/Renderer.cpp src/Renderer.h
	g++ -c src/Renderer.cpp -o build/Renderer.o

build/KeyHandler.o: src/KeyHandler.cpp src/KeyHandler.h
	g++ -c src/KeyHandler.cpp -o build/KeyHandler.o



clean:
	rm Ageron
	rm build/*
