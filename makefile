# This is the enhanced Makefile for the main project
CC = cc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS = main.o runway.o flight.o
RM = rm -f
# Creating the executable (main)
main: $(OBJS)
	$(CCLINK) -o main $(OBJS) $(LIBS)

# Creating object files using default rules
main.o: main.c runway.h ex2.h flight.h
flight.o: flight.c ex2.h flight.h
runway.o: runway.c runway.h ex2.h flight.h

# Cleaning old files before new make
clean: 
	$(RM) main *.o *.bak *~ "#"* core