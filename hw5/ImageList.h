/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* ImageList.h: header file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#ifndef IMAGELIST_H
#define IMAGELIST_H

#include "Image.h"
typedef struct ImageEntry IENTRY;
typedef struct ImageList ILIST;

struct ImageList {
    unsigned int Length;
    IENTRY *First;
    IENTRY *Last;
	/* to be implemented */
};

struct ImageEntry {
    ILIST *List;
    IENTRY *Next;
    IENTRY *Prev;
    IMAGE *RGBImage;
    YUVIMAGE *YUVImage;	
/* to be implemented */
};

/* Create a new image list */
ILIST *CreateImageList(void);

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list);

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage);

/*Insert a YUV image to the image list at the beginning*/
void PrependYUVImage(ILIST *list, YUVIMAGE *YUVimage);

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage);

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end);

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor);

/* Reverse an image list */
void ReverseImageList(ILIST *list);

/*Make a number of copies of the first and last frame*/
void CopyFrame(ILIST *list, unsigned int num);
#endif
