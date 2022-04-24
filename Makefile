# variables

CC=g++
MINGW=x86_64-w64-mingw32-g++

CFLAGS=-O3 -g 

INC=PerlinDemo_00.cpp PerlinNoise.cpp PerlinNoise.h ppm.cpp ppm.h

# linux
.PHONY: default
default: pn_image.bin
pn_image.bin:
	$(CC) $(INC) $(CFLAGS) -o $@ $^

# windows
.PHONY: windows
windows: pn_image.exe
pn_image.exe:
	$(MINGW) -o $@ $^ ${INC}

# both
.PHONY: all 
all: pn_image.bin pn_image.exe

# clean
.PHONY: clean
clean:
	rm -f *.bin *.exe *.ppm 