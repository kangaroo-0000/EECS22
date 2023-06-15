#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2022
#
# Initial author: Tim Schmidt
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
DESIGN = MovieLab

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -Wall -std=c11
LFLAGS = -Wall

# Default target
all: MovieLab
######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: MovieLab.c FileIO.h DIPs.h Image.h ImageList.h Movie.h Constants.h 
	$(CC) $(CFLAGS) -c MovieLab.c -o MovieLab.o 
# Target for FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h Image.h 
	$(CC) $(CFLAGS) -c FileIO.c -o FileIO.o 
# Target for DIPs.o
DIPs.o: DIPs.h DIPs.c Image.h Constants.h
	$(CC) $(CFLAGS) -c DIPs.c -o DIPs.o
# Target for Image.o
Image.o: Image.h Image.c Constants.h
	$(CC) $(CFLAGS) -c Image.c -o Image.o
# Target for ImageList.o
ImageList.o: ImageList.c ImageList.h FileIO.h DIPs.h Image.h Movie.h Constants.h 
# Target for Movie.o
Movie.o: Movie.c FileIO.h DIPs.h Image.h ImageList.h Movie.h Constants.h 
	$(CC) $(CFLAGS) -c Movie.c -o Movie.o
######################### Generate the executable #####################
# Target for MovieLab
MovieLab: MovieLab.o FileIO.o Movie.o DIPs.o ImageList.o Image.o
	$(CC) $(LFLAGS) MovieLab.o Movie.o DIPs.o FileIO.o ImageList.o Image.o -lm -o MovieLab
###############################  others  ##############################
# Target for clean-up
clean:
	rm -f *.o
	rm $(DESIGN)
