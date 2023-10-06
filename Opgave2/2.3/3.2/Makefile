
SOURCES=main.cpp part1.cpp part2.cpp
OBJECTS=$(addprefix $(OBJECT_DIR)/, $(SOURCES:.cpp=.o))
DEPS=$(addprefix $(OBJECT_DIR)/, $(SOURCES:.cpp=.d))
EXE=$(TARGET_DIR)/prog
CXXFLAGS=-I
ARCH?=x86-64

#Making for x86-64
# > make ARCH=x86-64
ifeq (${ARCH},x86-64)
CXX=g++
BUILD_DIR=build/x86-64
PROG_DIR=bin/x86-64
endif

#Making for architecture
# > make ARCH=arm
ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR=build/arm
PROG_DIR=bin/arm
endif

#BUILD RULES
$(EXE): $(DEPS) $(OBJECTS) 
    $(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

$(OBJECT_DIR)/%.d: %.cpp
    @mkdir -p $(OBJECT_DIR)
    $(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
    $(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

clean:
    rm -rf $(OBJECT_DIR) $(TARGET_DIR)

#Check build & target dir exist
$(shell mkdir -p $(OBJECT_DIR))
$(shell mkdir -p $(TARGET_DIR))
