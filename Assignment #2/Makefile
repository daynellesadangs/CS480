###########################################################
# Course: CS 480-01, Summer 2026
# Instructor: Guy Leonard
# Assignment Information: Programming Assignment #2, Experimental Shell

# Team Members:
# - Daynelle Lorin Sadangsal (cssc3154)
# - Sophia Phung (cssc3147)

# FileName: Makefile
###########################################################

EXEC = xsh
FILES = main.cpp command.cpp exec.cpp
CC = g++
LFLAGS = -Wall -Wextra -std=c++17
CFLAGS = -Wall -Wextra -std=c++17 -c

OBJECTS = $(FILES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)
	rm -f *.o

.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o core a.out $(EXEC)

#######################[ EOF: Makefile ]###################
