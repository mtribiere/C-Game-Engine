TARGET = prog
LIBS = -lSDL_image
CC = gcc
CFLAGS = -o -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ `sdl-config --cflags --libs `

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@ `sdl-config --libs`

clean:
	-rm -f *.o
	-rm -f $(TARGET)
