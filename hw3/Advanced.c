#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Advanced.h"
#include "Constants.h"

void Noise( int percentage, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    
    int x, y; //random x y positions
    int num = (percentage * WIDTH * HEIGHT) / 100;
    srand(time(0));
    for(int i = 0; i < num; i++){
	x = rand() % WIDTH;
	y = rand() % HEIGHT;
	R[x][y] = 255;
	G[x][y] = 255;
	B[x][y] = 255;
    }
}
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int tempr[WIDTH][HEIGHT];
    int tempg[WIDTH][HEIGHT];
    int tempb[WIDTH][HEIGHT];
    int saturate_r;
    int saturate_g;
    int saturate_b;
    for(int c = 0; c < 512; c++){
        for(int r = 0; r < 288; r++){
            tempr[c][r] = (int)(R[c][r]);
            tempg[c][r] = (int)(G[c][r]);
            tempb[c][r] =(int)(B[c][r]);
        }
    }
    for(int c = 0; c < 512; c++){
        for(int r = 0; r < 288; r++){
            saturate_r = tempr[c][r]*9 - tempr[c-1][r-1] - tempr[c-1][r] - tempr[c-1][r+1] - tempr[c][r-1] - tempr[c][r+1] - tempr[c+1][r-1] - tempr[c+1][r] - tempr[c+1][r+1];
            saturate_g = tempg[c][r]*9 - tempg[c-1][r-1] - tempg[c-1][r] - tempg[c-1][r+1] - tempg[c][r-1] - tempg[c][r+1] - tempg[c+1][r-1] - tempg[c+1][r] - tempg[c+1][r+1];
            saturate_b = tempb[c][r]*9 - tempb[c-1][r-1] - tempb[c-1][r] - tempb[c-1][r+1] - tempb[c][r-1] - tempb[c][r+1] - tempb[c+1][r-1] - tempb[c+1][r] - tempb[c+1][r+1];
            if(saturate_r < 0)
                saturate_r = 0;
            if(saturate_r > 255)
                saturate_r = 255;
            if(saturate_g < 0)
                saturate_g = 0;
            if(saturate_g > 255)
                saturate_g = 255;
            if(saturate_b < 0)
                saturate_b = 0;
            if(saturate_b > 255)
                saturate_b = 255;
            R[c][r] = (char)(saturate_r);
            G[c][r] = (char)(saturate_g);
            B[c][r] = (char)(saturate_b);

        }
    }

}

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits){
    int x, y, z;
    for (int j = 0; j < HEIGHT; j++){
        for (int i = 0; i < WIDTH; i++){
            x = R[i][j] % (int)(pow(2, rbits));
            R[i][j] = R[i][j] - x + (int)(pow(2, rbits - 1) - 1);
            y = G[i][j] % (int)(pow(2, gbits));
            G[i][j] = G[i][j] - y + (int)(pow(2, gbits - 1) - 1);
            z = B[i][j] % (int)(pow(2, bbits));
            B[i][j] = B[i][j] - z + (int)(pow(2, bbits - 1) - 1);
        }
    }
}

void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int sumr = 0;
    int sumg = 0;
    int sumb = 0;
    //BlurAmount = BlurAmount*512/100;
    int blur = BlurAmount;
    for(int x = 0; x < 288; x++){
	for(int y = 0; y < 512; y++){
	    for(int b = 1; b <= blur; b++){
		if((x + BlurAmount) > 287){
		    blur = 287 - x;
		}
	            sumr += R[y][x+b];
		    sumg += G[y][x+b];
		    sumb += B[y][x+b];
	    }
	    if(blur != 0){
  	        sumr /= blur;
	        sumg /= blur;
	        sumb /= blur;
	    }else{
		break;
	    }
	    R[y][x] = R[y][x]/2 + sumr/2;
	    G[y][x] = G[y][x]/2 + sumg/2;
	    B[y][x] = B[y][x]/2 + sumb/2;
	    sumr = 0;
	    sumg = 0;
	    sumb = 0;
	    blur = BlurAmount;
	}
    }
}
