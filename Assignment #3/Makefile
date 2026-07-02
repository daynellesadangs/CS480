###########################################################
# Course: CS 480-01, Summer 2026
# Instructor: Guy Leonard
# Assignment Information: Programming Assignment #3, Disk Arm Scheduling Algorithms

# Team Members:
# - Daynelle Lorin Sadangsal (cssc3154)
# - Sophia Phung (cssc3147)

# FileName: Makefile
###########################################################

CC = g++
CFLAGS = -Wall -Wextra -std=c++11

EXEC = simarm
SRC = main.cpp

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)

#######################[ EOF: Makefile ]###################