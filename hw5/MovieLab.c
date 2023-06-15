/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "ImageList.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	int age, flip, edge, rev, spot, zoom, crop, fast, water; /*boolean, TRUE if operation is mentioned in command line*/
	char *fin = NULL;
	char *fout = NULL;
	char wmark[15];
	int cropstart, cropend;
	int factor; // fast forward factor
	int nframe;
	const IMAGE *mark = NULL;
	MOVIE *movie = NULL;
	ILIST *lst = NULL;
	unsigned int width = 512;
	unsigned int height = 288;

	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				fin = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the help option */
		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			return 0;
		} /*fi*/
		
		if(strcmp(argv[x], "-s") == 0){
		    if (x < argc - 1) {
			sscanf(argv[x+1], "%ux%u", &width, &height);
		    }else{
			printf("Missing argument for the movie dimensions! \n");
		        return 5;
		    }
		    x += 2;
		    continue;
		}
		
		if(strcmp(argv[x], "-f") == 0){
		    if(x < argc - 1){
			sscanf(argv[x+1], "%d", &nframe);
		    }else{
			printf("Missing argument for the frame numbers!\n");
			return 5;
		    }
		    x += 2;
		    continue;
		}
		
		if(strcmp(argv[x], "-crop") == 0){
		    if(x < argc - 1){
			sscanf(argv[x+1], "%u-%u", &cropstart, &cropend);
			crop = 1;
		    }else{
			printf("Missing argument for starting/ending cropped frames!\n");
			return 5;
		    }
		    x += 2;
		    continue;
		}

		if(strcmp(argv[x], "-fast") == 0){
		    if(x < argc - 1){
			sscanf(argv[x+1], "%d", &factor);
			fast = 1;
		    }else{
			printf("Missing argument for fast forward factor!\n");
			return 5;
		    }
		    x += 2;
		    continue;
		}
		
		if(strcmp(argv[x], "-watermark") == 0){
		    if(x < argc - 1){
			sscanf(argv[x+1], "-%[^\n]", wmark);
			mark = LoadImage(wmark);
			assert(mark);
			water = 1;
		    }else{
			printf("Missing watermark file!\n");
			return 5;
		    }
		    x += 2;
		    continue;
		}

		if(strcmp(argv[x], "-aging") == 0){
		    age = 1;
		    break;
		}
		if(strcmp(argv[x], "-hflip") == 0){
		    flip = 1;
		    break;
		}
		if(strcmp(argv[x], "-edge") == 0){
		    edge = 1;
		    break;
		}
		if(strcmp(argv[x], "-reverse") == 0){
		    rev = 1;
		    break;
		}
		if(strcmp(argv[x], "-spotlight") == 0){
		    spot = 1;
		    break;
		}
		if(strcmp(argv[x], "-zoom") == 0){
		    zoom = 1;
		    break;
		}

		x++;
	} /*elihw*/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}
	/* DIPs and ImageList operations*/
	if(crop == 1){
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
	    lst = movie -> Frames;
	    CropImageList(lst, cropstart, cropend);
	    printf("Operation Crop is done! New number of frames is %d.\n", 1+cropend-cropstart);	
	}
	if(rev == 1){
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
            lst = movie -> Frames;
	    ReverseImageList(lst);
	    printf("Operation Reverse is done!\n");
	}
	if(fast == 1){
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
            lst = movie -> Frames;
	    FastImageList(lst, factor);
	    printf("Operation Fast Forward is done! New number of frames is %d.\n", nframe/factor);
	}
	if(water == 1){
	    srand(time(0));
	    int fit = 0;
	    unsigned int x, y;
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
	    YUV2RGBMovie(movie);
	    lst = movie -> Frames;
	    IENTRY *e, *n;
	    e = lst -> First;
	    while(e){
		while(fit && (nframe % WATERMARK_PER_FRAMES == 0)){
		    x = rand()%width;
		    y = rand()%height;
		    if((x + mark -> W > width) || (y + mark -> H) > height){
			fit = 1;
		    }else{
			fit = 0;
		    }
		}
		n = e -> Next;
		assert(e -> RGBImage);
	        Watermark(e -> RGBImage, mark, x, y);
		e = n;
	    }
	    RGB2YUVMovie(movie);
	    printf("Operation watermark is done!\n");
	}
	if(age == 1){
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
	    assert(movie);
            YUV2RGBMovie(movie);
            lst = movie -> Frames;
 	    IENTRY *e, *n;
            e = lst -> First;
	    while(e){
		n = e -> Next;
		Aging(e -> RGBImage);
	        e = n;
	    }
	    RGB2YUVMovie(movie);
	    printf("Operation Aging is done!\n");
	}
	if(edge == 1){
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
            YUV2RGBMovie(movie);
            lst = movie -> Frames;
            IENTRY *e, *n;
	    e = lst -> First;
            while(e){
                n = e -> Next;
                Edge(e -> RGBImage);
		assert(e->RGBImage);
                e = n;
            }
	    RGB2YUVMovie(movie);
	    printf("Operation Edge is done!\n");
	}
	if(flip == 1){
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
            YUV2RGBMovie(movie);
            lst = movie -> Frames;
            IENTRY *e, *n;
            e = lst -> First;
            while(e){
		n = e -> Next;
		HFlip(e -> RGBImage);
		e = n;
	    }
	    RGB2YUVMovie(movie);
	    printf("Operation HFlip is done!\n");
	}
	if(spot == 1){
	    unsigned int radiusbyFrame = (unsigned int)((sqrt(width*width/4 + height*height/4)/19));
	    int cnt = 0;
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
            lst = movie -> Frames;
            CopyFrame(lst, 20);
	    YUV2RGBMovie(movie);
	    IENTRY *e, *n;
            e = lst -> First;
	    assert(e);
	    while(e){
		n = e -> Next;
		if(cnt < 20){
		    Spotlight(e -> RGBImage, width/2, height/2, cnt*radiusbyFrame);
		}else if(cnt > 90){
		    Spotlight(e -> RGBImage, width/2, height/2, (110 - cnt)*radiusbyFrame);
		}
		cnt++;
		e = n;

	    }
	    RGB2YUVMovie(movie);    	
	    printf("Operation Spotlight is done! New number of frames is 110.\n");
	}
	if(zoom == 1){
	    int cnt = 0;
	    movie = CreateMovie();
            movie = LoadMovie(fin, nframe, width, height);
            lst = movie -> Frames;
            CopyFrame(lst, 20);
	    YUV2RGBMovie(movie);
            IENTRY *e, *n;
            e = lst -> First;
	    while(e){
		n = e -> Next;
		if(cnt < 20){
		    Zoom(e -> RGBImage, 20 + ZOOM_SPEED*cnt);
		}else if(cnt > 90){
		    Zoom(e -> RGBImage, 100 - ZOOM_SPEED*(110-cnt));
		}
	        cnt++;
		e = n;	    
	    }
	    RGB2YUVMovie(movie);
	    printf("Operation Zoom is done!\n");
	}
	SaveMovie(fout, movie);
	DeleteMovie(movie);
	/* to be implemented */

	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
    MOVIE *movie = NULL;
    movie = CreateMovie();
    for (int i = 0; i < frameNum; i++){
	AppendYUVImage(movie->Frames, LoadOneFrame(fname, i, width, height));			
    }
    return movie;	
	/* to be implemented */
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
        assert(movie);
	int count;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}
	
	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL) {
		SaveOneFrame(curr->YUVImage, fname, file);
		curr = curr->Next;
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname);
	return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}

