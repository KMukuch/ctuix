VPATH = src include

CC = clang
AR = ar
ARFLAGS = rcs

OBJDIR = build
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))

LIBNAME = $(OBJDIR)/libctuix.a

CPPFLAGS = -I include -I /opt/homebrew/include -I /opt/homebrew/opt/libxml2/include/libxml2

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(LIBNAME)

.PHONY: all clean
