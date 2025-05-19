CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = threads_program
SRC = threads.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
