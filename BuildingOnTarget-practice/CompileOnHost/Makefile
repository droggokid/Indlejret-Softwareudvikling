SOURCES = main.cpp part1.cpp part2.cpp
OBJECTS =${SOURCES:.cpp=.o}
CXX=g++
EXECUTABLE = parts

.PHONY: all
all: ${EXECUTABLE}

%.o: %.cpp
   ${CXX} -c -o $@ $^

${EXECUTABLE}: ${OBJECTS}
   ${CXX} -o $@ $^
clean:
   rm -f ${EXECUTABLE} *.o

help:
   @echo "Available targets: all, clean, help" 
