CC = cc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS = main_list.o list.o person.o
RM = rm -f
# Creating the executable (airport)
main_list: $(OBJS)
	$(CCLINK) -o main_list $(OBJS) $(LIBS)

# Creating object files using default rules
main_list.o: main_list.c defs.h list.h person.h
list.o: list.c defs.h list.h
person.o: person.c defs.h person.h

# Cleaning old files before new make
clean: 
	$(RM) main_list *.o *.bak *~ "#"* core