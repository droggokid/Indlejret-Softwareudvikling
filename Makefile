SOURCES=main.cpp part1.cpp part2.cpp
OBJECTS=${SOURCES:.cpp=.o}
EXE=parts
CXX=g++

.PHONY: all clean
all: ${EXE}

%.o: %.cpp
	${CXX} -c -o $@ $^

${EXE}: ${OBJECTS}
	${CXX} -o $@ $^

clean:
	rm -f ${OBJECTS} ${EXE}

help:
	@echo "Targets:"
	@echo "all"
	@echo "hello"
	@echo "clean"
	@echo "commands"
       @LC_ALL=C $(MAKE) -pRrq -f $(firstword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/(^|\n)# Files(\n|$)
