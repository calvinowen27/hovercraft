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

debug: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(DBGDIR)$(EXECUTABLE)

release: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(RLSDIR)$(EXECUTABLE)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)