# To compile main game type "make main"
# To execute compiled thingy, type "./name" in terminal

CC=g++
INCLUDE_DIR = include
CFLAGS = -I/usr/local/mpfr-4.0.2/include -L/usr/local/mpfr-4.0.2/lib -lmpfr -lgmp
OBJECT_DIR = obj
SOURCE_DIR = src

_DEPS = interval.h mpreal.h
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)

_OBJ = main.o
OBJ = $(patsubst %,$(OBJECT_DIR)/%,$(_OBJ))

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPS) | $(OBJECT_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Cleaning up files
.PHONY: clean
clean:
	make clean_compiled
	make clean_objects
clean_objects:
	rm -f $(OBJECT_DIR)/*.o
clean_compiled:
	rm -f main