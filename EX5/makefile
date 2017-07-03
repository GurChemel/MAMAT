CPP = g++
CPPFLAGS = -g -Wall -std=c++0x
CCLINK = $(CPP)
LIBS =
OBJS = main.o  ScriptExceptions.h Matrix.o Scalar.o Variable.o Commands.o LineParser.o MamatScriptEngine.o VariablesMap.o
RM = rm -f

MamatScript: $(OBJS)
	$(CPP) -g -Wall -std=c++0x -o MamatScript $(OBJS) $(LIBS)

Commands.o: Commands.cpp Commands.h VariablesMap.h MySharedPtr.h \
 Variable.h Scalar.h Matrix.h LineParser.h ScriptExceptions.h
LineParser.o: LineParser.cpp LineParser.h VariablesMap.h MySharedPtr.h \
 Variable.h Commands.h Scalar.h Matrix.h ScriptExceptions.h
main.o: main.cpp MamatScriptEngine.h VariablesMap.h MySharedPtr.h \
 Variable.h LineParser.h Commands.h
MamatScriptEngine.o: MamatScriptEngine.cpp MamatScriptEngine.h \
 VariablesMap.h MySharedPtr.h Variable.h LineParser.h Commands.h \
 ScriptExceptions.h
Matrix.o: Matrix.cpp Matrix.h Variable.h MySharedPtr.h Scalar.h \
 ScriptExceptions.h
Scalar.o: Scalar.cpp Scalar.h Variable.h MySharedPtr.h Matrix.h \
 ScriptExceptions.h
Variable.o: Variable.cpp Variable.h MySharedPtr.h ScriptExceptions.h
VariablesMap.o: VariablesMap.cpp VariablesMap.h MySharedPtr.h Variable.h \
 ScriptExceptions.h


clean:
	$(RM) main *.o *.bak *~ "#"* core
