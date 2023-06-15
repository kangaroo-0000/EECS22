######################################################################
# Makefile: Makefile for Assignment #3 EECS22 Winter 2022
# 01/20/22 Mariam Rakka  : updated for EECS22 Assignment 3 Winter 2022
# 11/08/17 Mina Moghadam : updated for EECS22 Assignment 3 Fall 2017
# 10/08/16 Tim Schmidt   : updated for EECS22 Assignment 3 Fall 2016
# 10/17/15 Tim Schmidt   : updated for EECS22 Assignment 3 Fall 2015
# 10/21/14 Nistha Tandiya: updated for EECS22 Assignment 3 Fall 2014
# 10/27/13 Yasaman Samei : updated for EECS22 Assignment 3 Fall 2013
# 10/16/11 Weiwei Chen   : updated for EECS22 Assignment 3 Fall 2012
# 10/10/11 Weiwei Chen   : initial solution version
#
######################################################################


# design names
DESIGN = PhotoLab PhotoLabTest

#libs
LIBS   = libFilter.a libFileIO.a

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -Wall -std=c11
LFLAGS = -Wall
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm \
         negative.ppm \
         colorfilter.ppm \
         edge.ppm \
         vflip.ppm \
         shuffle.ppm \
         vmirror.ppm \
         border.ppm \
         noise.ppm \
         sharpen.ppm \
         posterize.ppm \
         blur.ppm

all: PhotoLab PhotoLabTest


########### generate object files ###########

#target to generate FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h Image.h 
	$(CC) $(CFLAGS) -c FileIO.c -o FileIO.o

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c Image.h Constants.h
	$(CC) $(CFLAGS) -c DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Advanced.h Advanced.c Image.h Constants.h
	$(CC) $(CFLAGS) -c Advanced.c -o Advanced.o

#target to generate PhotoLab.o
PhotoLab.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Image.h Test.h Constants.h
	$(CC) $(CFLAGS) -c PhotoLab.c -o PhotoLab.o

#target to generate FileIO_DEBUG.o
PhotoLab_DEBUG.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Image.h Test.h Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab.c -o PhotoLab_DEBUG.o

#target to generate Image.o
Image.o: Image.h Image.c Constants.h
	$(CC) $(CFLAGS) -c Image.c -o Image.o

#target to generate Test.o
Test.o: Test.h Test.c Constants.h
	$(CC) $(CFLAGS) -c Test.c -o Test.o
########### generate library files ###########

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a


########### generate executables ###########

#target to generate PhotoLab
PhotoLab: Image.o Test.o PhotoLab.o FileIO.o libFilter.a
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o Image.o Test.o -L. -lFilter -o PhotoLab

#target to generate test
PhotoLabTest: Image.o Test.o PhotoLab_DEBUG.o FileIO.o libFilter.a
	$(CC) $(LFLAGS) PhotoLab_DEBUG.o FileIO.o Image.o Test.o -L. -lFilter -o PhotoLabTest
	
#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)

