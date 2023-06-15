#include "Image.h" 
#include <assert.h>
#include <stdlib.h>
#include <string.h>

IMAGE *CreateImage(unsigned int Width, unsigned int Height){
    IMAGE *i = NULL;
    //assert(i);
    i = malloc(sizeof(IMAGE));
    i -> R = malloc(sizeof(unsigned char)*Height*Width);
    i -> G = malloc(sizeof(unsigned char)*Height*Width);
    i -> B = malloc(sizeof(unsigned char)*Height*Width);
    i -> W = Width;
    i -> H = Height;
    return i;
}

void DeleteImage(IMAGE *image){
    assert(image);
    free(image); 
      
}

unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y){
    return image -> R[x+y*ImageWidth(image)];
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y){
    return image -> G[x+y*ImageWidth(image)];
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y){
    return image -> B[x+y*ImageWidth(image)];
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r){
    image -> R[x+y*ImageWidth(image)] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g){
    image -> R[x+y*ImageWidth(image)] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b){
    image -> R[x+y*ImageWidth(image)] = b;
}

unsigned int ImageWidth(const IMAGE *image){
    return image -> W;
}

unsigned int ImageHeight(const IMAGE *image){
    return image -> H;
}
