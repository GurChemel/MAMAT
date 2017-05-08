# This is the enhanced Makefile for the main project
CC = cc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS = main.o airport.o runway.o flight.o
RM = rm -f
# Creating the executable (main)
main: $(OBJS)
	$(CCLINK) -o main $(OBJS) $(LIBS)

# Creating object files using default rules
airport.o: airport.c airport.h ex2.h flight.h runway.h
flight.o: flight.c ex2.h flight.h
main.o: main.c runway.h ex2.h flight.h
runway.o: runway.c runway.h ex2.h flight.h

# Cleaning old files before new make
clean: 
	$(RM) main *.o *.bak *~ "#"* core