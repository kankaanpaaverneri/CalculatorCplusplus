CC = g++
FLAGS = -std=c++17 -Wall -g
objects = main.o Util.o Value.o Value_List.o
source_files = main.cpp Util.cpp Value.cpp Value_List.cpp

all: compile clean

compile: ${objects} #LINKS OBJECT FILES
	${CC} ${objects} Exceptions.h -o calculator

main.o: main.cpp Util.h
	${CC} ${FLAGS} -c main.cpp

Util.o: Util.cpp
	${CC} ${FLAGS} -c Util.cpp

Value.o: Value.cpp
	${CC} ${FLAGS} -c Value.cpp

Value_List.o: Value_List.cpp
	${CC} ${FLAGS} -c Value_List.cpp

asm: ${source_files}
	${CC} ${FLAGS} -S ${source_files}

clean_asm:
	rm *.s

clean:
	rm *.o