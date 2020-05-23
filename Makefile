# Makefile (Leonardo Barbosa; May 16th, 2020)
# Techniken Watcher

EXEC = TechnikenWatcher
CFLAGS = -c -std=c++17

${EXEC}: main.o Path.o
	@g++ main.o Path.o -o ${EXEC}

main.o: main.cpp Path.o
	@g++ ${CFLAGS} main.cpp

Path.o: Path.hpp Path.cpp
	@g++ ${CFLAGS} Path.cpp

run:	${EXEC}
	@./${EXEC}

clean:
	@rm -f main.o Path.o ${EXEC}

All: ${EXEC}