# modify the following line to match your needs
BINDIR=$(HOME)/bin
GDAL=-I/usr/include/gdal -L/usr/lib
GCC = gcc

CFLAGS=-O3 -Wno-write-strings -Wno-unused-result
LDFLAGS=-lm -lgdal

all: temp imgsum

.PHONY: all temp install clean

temp:
	mkdir -p tmp

imgsum: src/imgsum.c
	$(GCC) $(GDAL) $(CFLAGS) -o tmp/imgsum src/imgsum.c $(LDFLAGS)

install:
	chmod 0755 tmp/imgsum
	cp tmp/imgsum $(BINDIR)

clean:
	rm -rf tmp

