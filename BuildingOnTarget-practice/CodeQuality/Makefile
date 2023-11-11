SOURCES = main.cpp part1.cpp part2.cpp
OBJECTS =${SOURCES:.cpp=.o}
DEPS =${SOURCES:.cpp=.d}
CLANG_FORMAT=/home/stud/.clang-format
CXX=g++
CXXFLAGS=-I.
EXECUTABLE = parts

.PHONY :all clean tidy format
all: ${EXECUTABLE}

${EXECUTABLE}:${DEPS} ${OBJECTS}
    ${CXX} ${CXXFLAGS} -o $@  ${OBJECTS}  

%.d: %.cpp
    ${CXX} -MT$@ -MM $(CXXFLAGS) $< > $@
    ${CXX} -MT${@:.d=.o} -MM $(CXXFLAGS) $< >> $@

#format: $(SOURCES:.cpp=.format)
#%.format: %.cpp
#    @echo "Formatting file '$<'" 
#    @clang-format -i $<
#    @echo "" > $@

tidy: $(SOURCES:.cpp =.tidy)
%.tidy: %.cpp
    @echo "Tidying file '$<'"...
    @clang-tidy $< -- $(CXXFLAGS)
    @echo "" > $@

clean:
    rm -f ${EXECUTABLE} ${OBJECTS}

help:
    @echo "Available targets: parts clean help all" 

