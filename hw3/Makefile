all:
	PhotoLab PhotoLabTest
clean:
	rm -f *.o
	rm -f PhotoLab 
	rm -f PhotoLabTest

PhotoLab: FileIO.c DIPs.c Advanced.c PhotoLab.c 
	gcc -c FileIO.c -o FileIO.o -std=c11 -Wall
	gcc -c DIPs.c -o DIPs.o -std=c11 -Wall
	gcc -c Advanced.c -o Advanced.o -std=c11 -Wall
	gcc -c PhotoLab.c -o PhotoLab.o -std=c11 -Wall
	ar rc libfilter.a DIPs.o Advanced.o 
	ranlib libfilter.a
	gcc -Wall PhotoLab.o FileIO.o -L. -lfilter -lm -o PhotoLab

PhotoLabTest: FileIO.c DIPs.c Advanced.c PhotoLab.c
	gcc -c FileIO.c -o FileIO.o -std=c11 -Wall
	gcc -c DIPs.c -o DIPs.o -std=c11 -Wall
	gcc -c Advanced.c -o Advanced.o -std=c11 -Wall
	gcc -c PhotoLab.c -o PhotoLabTest.o -DDEBUG -std=c11 -Wall
	ar rc libfilter.a DIPs.o Advanced.o
	ranlib libfilter.a
	gcc -Wall PhotoLabTest.o FileIO.o -L. -lfilter -lm -o PhotoLabTest




