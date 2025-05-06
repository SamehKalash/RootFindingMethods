CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm 
TARGET = root_finder
SRC = main.c methods/bisection.c methods/newton_raphson.c

all:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)  # Correct order

root: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all root clean