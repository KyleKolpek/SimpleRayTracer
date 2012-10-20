CC=g++
CFLAGS=-c -Wall
LDFLAGS=

all: rayTracer

rayTracer: image.o light.o loader.o main.o scene.o sphere.o triangle.o
	$(CC) image.o light.o loader.o main.o scene.o sphere.o triangle.o \
	-o rayTracer

image.o: image.cpp
	$(CC) $(CFLAGS) image.cpp

light.o: light.cpp
	$(CC) $(CFLAGS) light.cpp

loader.o: loader.cpp
	$(CC) $(CFLAGS) loader.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

scene.o: scene.cpp
	$(CC) $(CFLAGS) scene.cpp

sphere.o: sphere.cpp
	$(CC) $(CFLAGS) sphere.cpp

triangle.o: triangle.cpp
	$(CC) $(CFLAGS) triangle.cpp

script:
	echo
clean:
	rm -rf *.o
