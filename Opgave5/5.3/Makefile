SOURCES=parkAlot-2000capped.cpp
OBJECTS=${SOURCES:.cpp=.o}
EXECUTABLE=parkAlot-2000capped
CXX=g++
CXXFLAGS=-ggdb -I.

%.o: %.cpp
	${CXX} -c -o $@ $^ ${CXXFLAGS}

${EXECUTABLE}: ${OBJECTS}
	${CXX} -o $@ $^

clean:
	rm ${EXECUTABLE} ${OBJECTS}
