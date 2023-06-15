/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"
#include "Image.h"
#include "Movie.h"
/* Create a new image list */
ILIST *CreateImageList(void)
{
    ILIST *l = NULL;
    l = malloc(sizeof(ILIST));
    if(!l){
	printf("No memory!");
	exit(10);
    }
    l -> Length = 0; 
    l -> First = NULL;
    l -> Last = NULL;
    return l;
	/* to be implemented */
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
    IENTRY *e, *n = NULL;
    IMAGE *image = NULL;
    YUVIMAGE *yimage = NULL;
    assert(list);
    e = list -> First;
    while(e){
        n = e -> Next;
	yimage = e -> YUVImage;
	image = e -> RGBImage;
	free(e);
	assert(yimage);
	assert(image);
	DeleteYUVImage(yimage);
	DeleteImage(image);
	e = n;
    }
    list -> First = NULL;
    list -> Last = NULL; 
    free(list);
    
    
    
	/* to be implemented */
}


/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
    IENTRY *e;
    assert(list);
    assert(RGBimage);
    /*creating a new IENTRY instance*/
    e = malloc(sizeof(IENTRY));
    if(!e){ 
    printf("No memory!");
    exit(10);
    }
    /* empty list*/
    if(list -> Length == 0){
        e -> List = list;
	e -> Next = NULL;
	e -> Prev = NULL;
	e -> RGBImage = RGBimage;
	e -> YUVImage = NULL;
	list -> Last = e;
	list -> First = e;   
    }else{ //not empty list
	e -> List = list;
	e -> Next = NULL;
	e -> Prev = list -> Last;
	e -> Prev -> Next = e;
	list -> Last = e;
	e -> RGBImage = RGBimage;
	e -> YUVImage = NULL;
	/* to be implemented */
    }
    list -> Length ++;
}

/*Insert a YUV image to the image list at the beginning*/
void PrependYUVImage(ILIST *list, YUVIMAGE *YUVimage){
    IENTRY *e;
    assert(list);
    assert(YUVimage);
    e = malloc(sizeof(IENTRY));
    if(!e){
    printf("No memory!");
    exit(10);
    } 
    if(list -> Length == 0){
	e -> List = list;
	e -> Next = NULL;
	e -> Prev = NULL;
	e -> RGBImage = NULL;
	e -> YUVImage = YUVimage;
	list -> Last = e;
	list -> First = e;
    }else{
	e -> List = list;
	e -> Next = list -> First;
	e -> Prev = NULL;
	e -> Next -> Prev = e;
	list -> First = e;
	e -> RGBImage = NULL;
	e -> YUVImage = YUVimage;
    }
    list -> Length++;
					   				    
}
/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
    IENTRY *e;
    assert(list);
    assert(YUVimage);
    /*creating a new IENTRY instance*/
    e = malloc(sizeof(IENTRY));
    if(!e){
    printf("No memory!");
    exit(10);
    }
    /* empty list*/
    if(list -> Length == 0){
        e -> List = list;
        e -> Next = NULL;
        e -> Prev = NULL;
        e -> RGBImage = NULL;
        e -> YUVImage = YUVimage;
        list -> Last = e;
        list -> First = e;
    }else{ //not empty list
        e -> List = list;
        e -> Next = NULL;
        e -> Prev = list -> Last;
        e -> Prev -> Next = e;
        list -> Last = e;
	e -> RGBImage = NULL;
	e -> YUVImage = YUVimage;
        /* to be implemented */
    }
    list -> Length ++;
}	/* to be implemented */

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
    assert(list);
    int count = 0;
    IENTRY *i = NULL;
    IENTRY *n = NULL;
    i -> List = list;
    n -> List = list;
    i = list -> First;
    while(count < 70){
	if(count < start || count > end){
	    n = i -> Next;
	    assert(n);
	    DeleteYUVImage(i -> YUVImage);
	    i -> List = NULL;
	    i -> Next = NULL;
	    i -> Prev = NULL;
	    list -> Length--;
	    i = n;
	    count++; 
	    }else{
		n = i -> Next;
	        if(count == start){
		    list -> First = i;
		    i -> Prev = NULL;
		}
		if(count == end){
		    list -> Last = i;
		    i -> Next = NULL;
		}
		count++;	         
		i = n;
	    }
    }
}
	/* to be implemented */

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{   
    assert(list); 
    IENTRY *i = NULL;
    IENTRY *n = NULL;
    i = list -> First;
    int len = list -> Length;
    n = i;
    int countdown = 0; 
    for(int x = 0; x < len; x++){
        if(countdown == 0){
            if(x == 0){ 
                list -> First = i; 
                countdown = factor;
                continue;
            }
            if(x == ((list -> Length) / factor) * factor){
                list -> Last = i;
		continue;
            } 
            i -> Prev = n;
            n -> Next = i;
            n = i;
            countdown = factor;
            continue;
        }
        countdown--;
        i = i -> Next;
        DeleteYUVImage(i -> YUVImage);
        i -> List = NULL;
        len--;
    }
    list -> Length = len;                                 
}


/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
    assert(list);
    IENTRY *curr, *temp = NULL; 
    curr = list -> First;
    while(curr){
	temp = curr -> Next;
	curr -> Next = curr -> Prev;
	curr -> Prev = temp;
	curr = temp;
    }	
    temp = list -> First;
    list -> First = list -> Last;
    list -> Last = temp;

	/* to be implemented */
}

void CopyFrame(ILIST *list, unsigned int num){
    assert(list);
    YUVIMAGE *fir, *las = NULL;
    fir = list -> First -> YUVImage;
    las = list -> Last -> YUVImage;
    while(num != 0){
	PrependYUVImage(list, fir);
        AppendYUVImage(list, las);
	num--;
    }
}   
	

/* EOF */
