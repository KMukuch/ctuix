VPATH = src include

CC = clang

OBJDIR = build
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGET = main

CPPFLAGS = -I include -I /opt/homebrew/include -I /opt/homebrew/opt/libxml2/include/libxml2

LDFLAGS = -L/opt/homebrew/lib -L/opt/homebrew/opt/libxml2/lib
LDLIBS  = -lncurses -lxml2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(OBJDIR)/$(TARGET) $(LDLIBS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

.PHONY: all clean
