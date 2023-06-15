#include "Advanced.h"
#include "Image.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

/* Add noise to an image */
IMAGE *Noise(int n, IMAGE *image)
{
	int x, y, i;
	int num; /* number of noise added */
	num = ( n*ImageHeight(image)*ImageWidth(image))/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) {
		x = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
		y = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);
		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
	return image;
}


/* sharpen the image */
IMAGE *Sharpen(IMAGE *image)
{
	int		x, y, m, n, a, b;
	int		tmpR = 0;
	int		tmpG = 0;
	int		tmpB = 0;

	unsigned char	R_tmp[ImageWidth(image)][ImageHeight(image)];
	unsigned char	G_tmp[ImageWidth(image)][ImageHeight(image)];
	unsigned char	B_tmp[ImageWidth(image)][ImageHeight(image)];

	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++) {
			R_tmp[x][y] = GetPixelR(image, x, y);
			G_tmp[x][y] = GetPixelG(image, x, y);
			B_tmp[x][y] = GetPixelB(image, x, y);
		}
	}

	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = x + m;
					b = y + n;
					if (a > ImageWidth(image) - 1)
						a = ImageWidth(image) - 1;
					if (a < 0)
						a = 0;
					if (b > ImageHeight(image) - 1)
						b = ImageHeight(image) - 1;
					if (b < 0)
						b = 0;

					if ((n==0)&&(m==0))
					{
						tmpR += 9*R_tmp[a][b] ; 
						tmpG += 9*G_tmp[a][b] ; 
						tmpB += 9*B_tmp[a][b] ; 
					}
					else
					{
						tmpR -= R_tmp[a][b] ; 
						tmpG -= G_tmp[a][b] ; 
						tmpB -= B_tmp[a][b] ; 
					}
				}
			}
			SetPixelR(image, x, y, ((tmpR>255)? 255: (tmpR<0)? 0: tmpR));
			SetPixelG(image, x, y, ((tmpG>255)? 255: (tmpG<0)? 0: tmpG));
			SetPixelB(image, x, y, ((tmpB>255)? 255: (tmpB<0)? 0: tmpB));
			tmpR = tmpG = tmpB = 0; 	
		}
	}
	return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int x, y;
	for(x=0; x<ImageWidth(image); x++) {
		for(y=0; y<ImageHeight(image); y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				SetPixelR(image, x, y, GetPixelR(image, x, y) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelR(image, x, y, GetPixelR(image, x, y) & one);

			one = 1;
			for(i=0; i<gbits-1; i++) {
				SetPixelG(image, x, y, GetPixelG(image, x, y) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelG(image, x, y, GetPixelG(image, x, y) & one);

			one = 1;
			for(i=0; i<bbits-1; i++) {
				SetPixelB(image, x, y, GetPixelB(image, x, y) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelB(image, x, y, GetPixelB(image, x, y) & one);
		}
	}
	return image;
}

/* add motion blur to the image */
IMAGE *MotionBlur(int BlurAmount, IMAGE *image)
{
	int x,y,m;
	double temp_r , temp_g , temp_b;
	int n;

	for (x = 0; x < ImageWidth(image)-1; x++)
	{
		for (y = 0; y < ImageHeight(image) ; y++) 
		{
			temp_r = GetPixelR(image, x, y)/2;
			temp_b = GetPixelG(image, x, y)/2;
			temp_g = GetPixelB(image, x, y)/2;
			for (m = 1; m<=BlurAmount ; m++)
			{
				if ((x+m) < ImageWidth(image))
				{
					if (BlurAmount < ImageWidth(image)-x-1)
					{
						n = BlurAmount;
					}
					else
					{
						n = ImageWidth(image)-x-1;
					}
					temp_r = temp_r + GetPixelR(image, x+m, y) * 0.5/n;
					temp_b = temp_b + GetPixelB(image, x+m, y) * 0.5/n;
					temp_g = temp_g + GetPixelG(image, x+m, y) * 0.5/n;
				}
			}
			SetPixelR(image, x, y, temp_r);
			SetPixelG(image, x, y, temp_g);
			SetPixelB(image, x, y, temp_b);
		}	
	}
	return image;
}

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H){
    //assert(image); 
    IMAGE *i1 = NULL; 
    if(x + W > ImageWidth(image)){
	W = x + W - ImageWidth(image);
    }
    if(y + H > ImageHeight(image)){
	H = y + H - ImageHeight(image);
    }
    i1 = CreateImage(W, H);  
    for(int i = y; i < H; i++){
	for(int j = x; j < W; j++){
	    SetPixelR(i1, j, i, GetPixelR(image, j, i));
	    SetPixelG(i1, j, i, GetPixelG(image, j, i));
	    SetPixelB(i1, j, i, GetPixelB(image, j, i));
	}
    }
    DeleteImage(image);
    return i1;
}

IMAGE *Resize(IMAGE *image, int percentage){
   // assert(image);
    int x1, y1, x2, y2;
    int sumR, sumG, sumB;
    int cnt;
    int nWidth = (int)(ImageWidth(image) * percentage/100.0);
    int nHeight = (int)(ImageHeight(image) * percentage/100.0);
    IMAGE *i2 = NULL;
    if(percentage == 100){
	return image;         
    }else if(percentage > 100){
        i2 = CreateImage(nWidth, nHeight);
	for(int y = 0; y < nHeight; y++){
	    for(int x = 0; x < nWidth; x++){
		x1 = (int)(x/(percentage/100.0));
		y1 = (int)(y/(percentage/100.0));
		SetPixelR(i2, x, y, GetPixelR(image, x1, y1));
		SetPixelG(i2, x, y, GetPixelG(image, x1, y1));
		SetPixelB(i2, x, y, GetPixelB(image, x1, y1));
	    }
	}
	DeleteImage(image);
	return i2;
    }else if(percentage < 100){
	i2 = CreateImage(nWidth, nHeight);
	for(int y = 0; y < nHeight; y++){
	    for(int x = 0; x < nWidth; x++){
		x1 = (int)(x/(percentage/100.0));
                y1 = (int)(y/(percentage/100.0));
		x2 = (int)((x + 1)/(percentage/100.0));
                y2 = (int)((y + 1)/(percentage/100.0));
		for(int i = y1; i <= y2 - 1; i++){
		    for(int j = x1; j <= x2 - 1; j++){
			sumR += GetPixelR(image, j, i);		       
			sumG += GetPixelG(image, j, i);
			sumB += GetPixelB(image, j, i);
			cnt++;
		    }
		}
		sumR /= cnt;
		sumG /= cnt;
		sumB /= cnt;
		SetPixelR(i2, x, y, sumR);
                SetPixelG(i2, x, y, sumG);
                SetPixelB(i2, x, y, sumB);
		sumR = sumG = sumB = cnt = 0;		
	    }
	}
	DeleteImage(image);
	return i2;
    }
    printf("Invalid Percentage input.\n");
    return NULL;
}

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast){
    int newpixR, newpixG, newpixB;
    brightness = (brightness > 255) ? 255 : (brightness < -255) ? -255 : brightness;
    contrast = (contrast > 255) ? 255 : (contrast < -255) ? -255 : contrast;
    int factor = (double)(259*(contrast+255))/(double)(255*(259-contrast));
    for(int y = 0; y < ImageHeight(image); y++){
	for(int x = 0; x < ImageWidth(image); x++){
	    newpixR = (int)(factor*GetPixelR(image, x, y) + 128);
	    newpixG = (int)(factor*GetPixelG(image, x, y) + 128);
	    newpixB = (int)(factor*GetPixelB(image, x, y) + 128);
	    SetPixelR(image, x, y, newpixR);
	    SetPixelG(image, x, y, newpixG);
	    SetPixelB(image, x, y, newpixB);
	}
    }
    for(int y = 0; y < ImageHeight(image); y++){
	for(int x = 0; x < ImageWidth(image); x++){
	    SetPixelR(image, x, y, (brightness + GetPixelR(image, x, y)) > 255 ? 255 : (brightness + GetPixelR(image, x, y)) < -255 ? -255 : brightness + GetPixelR(image, x, y));
	    SetPixelG(image, x, y, (brightness + GetPixelG(image, x, y)) > 255 ? 255 : (brightness + GetPixelG(image, x, y)) < -255 ? -255 : brightness + GetPixelG(image, x, y));
	    SetPixelB(image, x, y, (brightness + GetPixelB(image, x, y)) > 255 ? 255 : (brightness + GetPixelB(image, x, y)) < -255 ? -255 : brightness + GetPixelB(image, x, y));
	}
    }

    return image;    
}

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image){
    image = NULL;
    return watermark_image;
}
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
