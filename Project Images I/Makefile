EXE = lab_intro
OBJS = main.o png.o rgbapixel.o

COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

mp1 : main.o rgbapixel.o png.o
	$(LINKER) main.o png.o rgbapixel.o -lpng -o mp1

main.o : main.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) main.cpp

png.o : png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp

clean :
	-rm -f *.o $(EXE)
