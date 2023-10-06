SOURCES = main.cpp
OBJECTS = ${SOURCES:.cpp=.o}
CXX = gcc
EXECUTABLE = hello

.PHONY: all clean help

all: $(EXECUTABLE)

%.o: %.cpp
    ${CXX} -c -o $@ $^

$(EXECUTABLE): ${OBJECTS}
    $(CXX) -o $@ $^ -lncurses

clean:
    rm -f $(EXECUTABLE) $(OBJECTS)

help:
    @echo "Available targets: all, clean, help" 
