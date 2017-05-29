CC = cc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS =  main.o cluster.o list.o person.o point.o 
RM = rm -f
# Creating the executable (airport)
ADT: $(OBJS)
	$(CCLINK) -o ADT $(OBJS) $(LIBS)

# Creating object files using default rules
main.o: main.c list.h defs.h point.h cluster.h person.h
cluster.o: cluster.c defs.h list.h point.h cluster.h
point.o: point.c defs.h list.h point.h
person.o: person.c defs.h person.h
list.o: list.c defs.h list.h

# Cleaning old files before new make
clean: 
	$(RM) ADT *.o *.bak *~ "#"* core