SYSCONF_LINK = g++
CPPFLAGS     =
LDFLAGS      =
LIBS         = -lm

DESTDIR = bin/
TARGET  = $(DESTDIR)main

SOURCE_FILES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,$(DESTDIR)%.o,$(SOURCE_FILES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): | $(DESTDIR)  # Ensure the directory exists before compiling objects
$(DESTDIR):
	mkdir -p $(DESTDIR)

$(OBJECTS): $(DESTDIR)%.o: %.cpp
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.tga
