CC = g++
CFLAGS = -Wall -g -pthread
TARGET = bots
OBJS = bots.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

bots.o: bots.cpp bots.h
	$(CC) $(CFLAGS) -c bots.cpp

clean:
	rm -f *.o $(TARGET) QUOTE.txt