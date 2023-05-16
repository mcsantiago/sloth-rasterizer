SYSCONF_LINK = g++
CPPFLAGS     = -Isrc/include
LDFLAGS      =
LIBS         = -lm

DESTDIR = bin/
OBJDIR = obj/
TARGET  = $(DESTDIR)main

SOURCE_FILES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,$(OBJDIR)%.o,$(SOURCE_FILES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): | $(OBJDIR)  # Ensure the directory exists before compiling objects
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJECTS): $(OBJDIR)%.o: src/%.cpp
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.tga
	-rm -f *.png
