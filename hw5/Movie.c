/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
    MOVIE *movie = NULL;
    movie = malloc(sizeof(MOVIE));
    if(!movie){
	printf("NO MEMORY:(");
	exit(10);
    }
    movie -> Frames = CreateImageList();
    return movie;
	/* to be implemented */
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
    assert(movie);
    ILIST *i = NULL;
    i = movie -> Frames;
    DeleteImageList(i);
    i = NULL;
    free(movie);	
/* to be implemented */
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
    assert(movie);
    IENTRY *currE, *nextE = NULL;
    ILIST *lst = NULL;
    IMAGE *img = NULL;
    unsigned int c, d, e; 
    unsigned int r, g, b;
    lst = movie -> Frames;
    currE = lst -> First; 
    while(currE){
        nextE = currE -> Next;
	img = CreateImage(currE -> YUVImage -> W, currE -> YUVImage -> H);
	assert(img);
        for(int j = 0; j < (currE -> YUVImage -> H); j++){
	    for(int i = 0; (i < currE -> YUVImage -> W); i++){
		c = GetPixelY(currE -> YUVImage, i, j) - 16;
		d = GetPixelU(currE -> YUVImage, i, j) - 128;
		e = GetPixelV(currE -> YUVImage, i, j) - 128;
		r = clip((298*c + 409*e + 128) >> 8);
		g = clip((298*c - 100*d - 208*e +128) >> 8);
		b = clip((298*c + 516*d +128) >> 8);
		SetPixelR(img, i, j, r);
		SetPixelG(img, i, j, g);
		SetPixelB(img, i, j, b);
	    }
	}
	currE -> RGBImage = img;
	currE = nextE;
    }		
 
/* to be implemented */
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
    assert(movie);
    IENTRY *currE, *nextE = NULL;
    ILIST *lst = NULL;
    YUVIMAGE *yimg = NULL;
    unsigned int y, u, v;
    unsigned int r, g, b;
    lst = movie -> Frames;
    currE = lst -> First;
    while(currE){
	nextE = currE -> Next;
	yimg = CreateYUVImage(currE -> RGBImage -> W, currE -> RGBImage -> H);
	for(int j = 0; j < currE -> RGBImage -> H; j++){
	    for(int i = 0; i < currE -> RGBImage -> W; i++){
		r = GetPixelR(currE -> RGBImage, i, j);
		g = GetPixelG(currE -> RGBImage, i, j);
		b = GetPixelB(currE -> RGBImage, i, j);
		y = clip(((66*r + 129*g + 25*b + 128) >> 8) + 16);
		u = clip(((-38*r - 74*g + 112*b +128) >> 8) +128);
		v = clip(((112*r - 94*g - 18*b +128) >> 8) +128);
		SetPixelY(yimg, i, j, y);
		SetPixelU(yimg, i, j, u);
		SetPixelV(yimg, i, j, v);
	    }
	}
	currE -> YUVImage = yimg;
	currE = nextE;
    }
						

	/* to be implemented */
}

unsigned int clip(unsigned int num){
 
    if(num < 0){
	num = 0;	
    }else if(num > 255){
	num = 255;
    } 
    return num;
}


/* EOF */
