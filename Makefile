.PHONY: clean run
.DEFAULT: build

EXEC_FILE = huff

CXX = g++

SRC_DIR = ./src
BUILD_DIR = ./build
SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CPPINCS =
CPPLIBS =

build: $(EXEC_FILE)

$(EXEC_FILE): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(CPPLIBS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	-mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CPPINCS) 

clean:
	-rm $(EXEC_FILE) $(OBJS)

run:
	./$(EXEC_FILE)