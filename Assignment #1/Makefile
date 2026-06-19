# Course: CS 480-01, Summer 2026
# Instructor: Guy Leonard
# Assignment Information: Programming Assignment #1, Thread Manager

# Team Members:
# - Daynelle Lorin Sadangsal (cssc3154)
# - Sophia Phung (cssc3147)

# FileName: Makefile
# Makefile to compile program

CC = g++
CFLAGS = -Wall -g -pthread
OBJ = bots.o

bots: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

bots.o: bots.cpp bots.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o bots QUOTE.txt
