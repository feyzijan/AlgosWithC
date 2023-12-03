# Compiler
CC = gcc

# Compiler flags, -Wall: most warnings on 
CFLAGS = -Wall -fopenmp  # Added -fopenmp for OpenMP support
DEBUG_FLAGS = -g  # Debug flags

# Name of executable generated
EXEC = bellmanford

# All .c files
SOURCES = main.c

# Object files, auto generated from SOURCES lists
OBJECTS = $(SOURCES:.c=.o)

# Rule to make everything - when we write make all
all: $(EXEC)

# Rule to make the executable
$(EXEC): $(OBJECTS)
# Link all object files to create executable
	$(CC) $(CFLAGS) -o $@ $^ -lm  

# Rule to make debug version of the executable
debug: CFLAGS += $(DEBUG_FLAGS)  # Append debug flags to CFLAGS
debug: $(EXEC)

# Rule to make object files from .c files
%.o: %.c
# Compile each .c file into a .o
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the directory
clean:
# Remove all object files and the executable
	rm -f $(OBJECTS) $(EXEC)
