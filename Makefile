# variables

CC=g++
MINGW=x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++

CFLAGS=-O3 -g 

INC=./src/*

# linux
.PHONY: default
default: pn_imager
pn_imager:
	$(CC) $(INC) $(CFLAGS) -o $@ $^

# windows
.PHONY: windows
windows: pn_imager.exe
pn_imager.exe:
	$(MINGW) ${CFLAGS} -o $@ $^ ${INC}

# both
.PHONY: all 
all: default windows

# clean
.PHONY: clean
clean:
	rm -f pn_imager *.exe *.ppm 