CC = gcc

CFLAGS = -g -Wall -Wextra -std=c11 -Isrc

SOURCEDIR = src/
TESTDIR = tests/
BINDIR = bin/

HEADERS_FP := $(shell find $(SOURCEDIR) -type f -name "*.h")
SOURCE_FP := $(shell find $(SOURCEDIR) -type f -name "*.c")

OBJECTS := $(patsubst $(SOURCEDIR)%.c,$(BINDIR)%.o,$(SOURCE_FP))

EXECUTABLE = $(BINDIR)main

main: $(EXECUTABLE)
	@./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@

$(BINDIR)%.o: $(SOURCEDIR)%.c $(HEADERS_FP)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR)