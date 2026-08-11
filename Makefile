CXX := g++

CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude/ -Ithird_party/ -MMD -MP
LDFLAGS := -lcurl

TARGET := bin/main

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=bin/%.o)
DEP := $(OBJ:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

bin/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -rf bin/*
