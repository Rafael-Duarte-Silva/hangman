CC = gcc

CFLAGS = -g -Wall -Wextra -std=c11 -Isrc

SOURCEDIR = src
BINDIR = bin

SOURCE = $(SOURCEDIR)/main.c
OLD_SOURCE = $(SOURCEDIR)/old_main.c

OBJECT = $(BINDIR)/main.o
OLD_OBJECT = $(BINDIR)/old_main.o

EXECUTABLE = $(BINDIR)/main
OLD_EXECUTABLE = $(BINDIR)/old_main


.PHONY: main old-main clean

main: $(EXECUTABLE)
	@./$(EXECUTABLE)

old-main: $(OLD_EXECUTABLE)
	@./$(OLD_EXECUTABLE)


$(EXECUTABLE): $(OBJECT) | $(BINDIR)
	$(CC) $(OBJECT) -o $@

$(OLD_EXECUTABLE): $(OLD_OBJECT) | $(BINDIR)
	$(CC) $(OLD_OBJECT) -o $@


$(BINDIR)/%.o: $(SOURCEDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(BINDIR):
	mkdir -p $(BINDIR)


clean:
	rm -rf $(BINDIR)