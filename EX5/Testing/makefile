CPP = g++
CPPFLAGS = -g -Wall -std=c++0x
CCLINK = $(CC)
LIBS =
OBJS = main_Var.o  ScriptExceptions.h Matrix.o  ScriptExceptions.h Scalar.o  ScriptExceptions.h Variable.o 
RM = rm -f

main_Var: $(OBJS)
	$(CPP) -g -Wall -std=c++0x -o main_Var $(OBJS) $(LIBS)

main_Var.o: main_Var.cpp Matrix.h Variable.h MySharedPtr.h Scalar.h \
 ScriptExceptions.h
Matrix.o: Matrix.cpp Matrix.h Variable.h MySharedPtr.h Scalar.h \
 ScriptExceptions.h
Scalar.o: Scalar.cpp Scalar.h Variable.h MySharedPtr.h Matrix.h \
 ScriptExceptions.h
Variable.o: Variable.cpp Variable.h MySharedPtr.h ScriptExceptions.h

clean:
	$(RM) main_Var *.o *.bak *~ "#"* core
