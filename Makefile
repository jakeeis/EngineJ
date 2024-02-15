CC := emcc
CFLAGS := -Wall -Wextra -std=c++20 -fwasm-exceptions
EMFLAGS := -sALLOW_MEMORY_GROWTH=1 -sFULL_ES2=1 -sWASM=1 -sNO_EXIT_RUNTIME=1 --embed-file assets 
TARGET := ./build/engine.js

# The first parameter ($1) is a list of directories, and the second ($2) is a list of patterns you want to match.
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS := $(call rwildcard, ., *.cpp)
OBJS := $(patsubst ./src%,./build%,$(SRCS:.cpp=.o))

HEADERS := $(patsubst ./%, -I%, $(call rwildcard, ., *.hpp))
CFLAGS := $(CFLAGS) $(dir $(HEADERS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(EMFLAGS) $^ -o $@

./build/%.o: ./src/%.cpp ./include/headers/%.hpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

./build/engine.o: ./src/engine.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf ./build/*
	
.PHONY: all clean