# Course: CS 480-01, Summer 2026
# Instructor: Guy Leonard
# Assignment Information: Programming Assignment #1, Thread Manager

# Team Members:
# - Daynelle Lorin Sadangsal (cssc3154)
# - Sophia Phung (cssc3147)

# FileName: Makefile

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