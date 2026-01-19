VPATH = src include

CPPFLAGS = -I include -I /opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LDLIBS = -lncurses

CC = clang

OBJDIR = build
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(OBJDIR)/$(TARGET) $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

.PHONY: all clean
