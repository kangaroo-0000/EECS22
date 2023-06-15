/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* Movie.h: header file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#ifndef MOVIE_H
#define MOVIE_H

#include "ImageList.h"

typedef struct Movie MOVIE;
/* the movie structure */
struct Movie{
    ILIST *Frames;	
/* to be implemented */
};

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void);

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie);

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie);

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie);

unsigned int clip(unsigned int num);
#endif
