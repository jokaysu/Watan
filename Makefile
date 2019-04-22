CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = watan
OBJECTS = game.o main.o board.o subject.o player.o
DEPENDS = ${OBJECTS:.o=.d}

.c.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
