CC := gcc
CFLAGS := -Wall -I lib/glfw/include -I lib/glad/include
LDFLAGS := lib/glad/src/glad.o lib/glfw/src/libglfw3.a -lm

#Binary folder
BIN := bin

# Get the source files recursively
SRCS := $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)

# generate names of object files
OBJS := $(SRCS:.c=.o)


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

# recipe to clean the workspace
clean:
	rm -f $(OBJS)

.PHONY: all clean run
