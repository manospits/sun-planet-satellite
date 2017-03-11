OBJS = main.o visuals.o
SOURCE = main.cpp visuals.cpp
OUT = solarsystem
CC = g++
FLAGS = -Wall
GL=-lGL -lGLU -lglut

$(OUT): $(OBJS)
	$(CC) $(FLAGS) $? $(GL) -o $@

main.o: main.cpp
	$(CC) $(FLAGS) -c $? $(GL)

visuals.o: visuals.cpp
	$(CC) $(FLAGS) -c $? $(GL)

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE)
