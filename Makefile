CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pedantic

LDFLAGS = -L./lib -lSDL2main -lSDL2 -lSDL2_image

SRCDIR = src
OBJDIR = build/obj
DBGDIR = build/debug/
RLSDIR = build/release/

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

EXECUTABLE = hovercraft

debug: $(OBJECTS) $(DBGDIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(DBGDIR)$(EXECUTABLE)

release: $(OBJECTS) $(RLSDIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(RLSDIR)$(EXECUTABLE)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

$(DBGDIR):
	mkdir -p $@

$(RLSDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)