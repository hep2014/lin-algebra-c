CC = gcc
CFLAGS = -Wall -Wextra -fPIC -Iinclude
LDFLAGS = -shared
SRC = src/matrix.c
OBJ = build/matrix.o
LIB = build/libmatrix.so

PREFIX ?= /usr/local
INCLUDEDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

all: $(LIB)

$(LIB): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ): $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

install: $(LIB)
	sudo install -Dm755 $(LIB) $(LIBDIR)/libmatrix.so
	sudo install -Dm644 include/matrix.h $(INCLUDEDIR)/matrix.h
	sudo ldconfig

uninstall:
	sudo rm -f $(LIBDIR)/libmatrix.so
	sudo rm -f $(INCLUDEDIR)/matrix.h
	sudo ldconfig

clean:
	rm -rf build

.PHONY: all install uninstall clean
