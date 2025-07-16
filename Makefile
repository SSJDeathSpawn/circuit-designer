CC := gcc
CFLAGS := -Wall -I lib/glfw/include -I lib/glad/include
LDFLAGS := lib/glad/src/glad.o lib/glfw/src/libglfw3.a -lm

#Binary folder
BIN := bin

# Get the source files recursively
SRCS := $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
$(info SRCS is $(SRCS))
SRCS := $(filter-out $(wildcard src/tests/*), $(SRCS))

$(info SRCS is $(SRCS))

# generate names of object files
OBJS := $(SRCS:.c=.o)
$(info OBJS is $(OBJS))


# default recipe
all: dirs libs app

dirs:
	mkdir -p ./$(BIN)

#recipe for compiling the libraries
libs:
	cd lib/glad && $(CC) -o src/glad.o -I include -c src/glad.c
	cd lib/glfw && cmake -S . && make

# recipe for building the final executable
app: $(OBJS)
	$(CC) -o $(BIN)/app $^ $(LDFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.c)
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

run: all
	$(BIN)/app

# Test suite

testgate:
	$(CC) -o $(BIN)/testgate src/tests/simple_gates.c src/simulation/device.c src/tests/gate_consts.c -lm
	$(BIN)/testgate
	rm $(BIN)/testgate

testcircuit:
	$(CC) -o $(BIN)/testcircuit src/tests/simple_circuit.c src/simulation/device.c src/simulation/circuit.c src/tests/gate_consts.c -lm
	$(BIN)/testcircuit
	rm $(BIN)/testcircuit

testgateconv:
	$(CC) -o $(BIN)/testgateconv src/tests/circuit_conv.c src/simulation/device.c src/simulation/circuit.c src/tests/gate_consts.c -lm
	$(BIN)/testgateconv
	rm $(BIN)/testgateconv

test: testgate testcircuit testgateconv

# recipe to clean the workspace
clean:
	rm -f $(OBJS)

.PHONY: all clean run
