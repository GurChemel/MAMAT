CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS = Course.o CS_Course.o EE_Course.o main.o  EE_Course.h Person.o StArray.o  Course.h EE_Course.h Student.o  EE_Course.h 
RM = rm -f

student: $(OBJS)
	$(CCLINK) -o student $(OBJS) $(LIBS)

Course.o: Course.cpp Proj.h Course.h
CS_Course.o: CS_Course.cpp Proj.h Course.h CS_Course.h
EE_Course.o: EE_Course.cpp Proj.h Course.h EE_Course.h
main.o: main.cpp Proj.h StArray.h Student.h Person.h CS_Course.h Course.h \
 EE_Course.h
Person.o: Person.cpp Proj.h Person.h
StArray.o: StArray.cpp StArray.h Proj.h Student.h Person.h CS_Course.h \
 Course.h EE_Course.h
Student.o: Student.cpp Student.h Proj.h Person.h CS_Course.h Course.h \
 EE_Course.h

clean:
	$(RM) student *.o *.bak *~ "#"* core
