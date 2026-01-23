VPATH = src include

CC = clang
AR = ar
ARFLAGS = rcs

OBJDIR = build
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRCS))

LIBNAME = $(OBJDIR)/libctuix.a

PREFIX ?= /usr/local
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include/ctuix
PKGDIR = $(PREFIX)/lib/pkgconfig

CPPFLAGS = -I include -I /opt/homebrew/include -I /opt/homebrew/opt/libxml2/include/libxml2

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

install: $(LIBNAME)
	@echo "Installing library..."
	install -d $(LIBDIR)
	install -m 644 $(LIBNAME) $(LIBDIR)

	@echo "Installing headers..."
	install -d $(INCDIR)
	install -m 644 include/*.h $(INCDIR)

	@echo "Installing pkg-config file (if exists)..."
	install -d $(PKGDIR)
	install -m 644 ctuix.pc $(PKGDIR) || true

uninstall:
	rm -f $(LIBDIR)/libctuix.a
	rm -rf $(INCDIR)
	rm -f $(PKGDIR)/ctuix.pc

clean:
	rm -rf $(OBJDIR)

.PHONY: all install uninstall clean
