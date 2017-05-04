# This is the enhanced Makefile for the doom project
CC = cc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS = runway.o
RM = rm -f
# Creating the executable (doom)
flight: $(OBJS) $(CCLINK) -o flight $(OBJS) $(LIBS)

# Creating object files using default rules
runway.o: runway.c runway.h flight.h ex2.h
#flight.o: flight.c ex2.h

# Cleaning old files before new make
clean: $(RM) airport *.o *.bak *~ "#"* core