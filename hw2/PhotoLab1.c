/********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2022                 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/
const int WIDTH  = 512;      /* image width */
const int HEIGHT = 288;      /* image height */
const int SLEN   =  80;      /* max. string length */

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* read image from a file */
int LoadImage(const char fname[SLEN], 
	      unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT], 
	      unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], 
	      unsigned char R[WIDTH][HEIGHT], 
	      unsigned char G[WIDTH][HEIGHT], 
	      unsigned char B[WIDTH][HEIGHT]);

/* change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], 
		 unsigned char G[WIDTH][HEIGHT], 
		 unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], 
	      unsigned char G[WIDTH][HEIGHT], 
	      unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], 
		 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], 
		 int target_r, int target_g, int target_b, int threshold, 
		 int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], 
	  unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);

/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], 
	     unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], 
	     unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], 
	       unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], 
	       char color[SLEN], int border_width);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], 
	   unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], 
	      unsigned char G[WIDTH][HEIGHT], 
	      unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];
    int choice;
    int tr;
    int tg;
    int tb;
    int range;
    int vr;
    int vg;
    int vb;
    char name[SLEN];
    char pic[SLEN];
    /* Please replace the following code with proper menu with function calls for DIP operations */
    do{
        PrintMenu();
	printf("please make your choice:");
	scanf("%d", &choice);
	switch(choice){
	    case 1:
		printf("Please input the file name to load: ");
		scanf(" %[^\n]", pic);
		if(LoadImage(pic, R, G, B) >= 0)
		    break;
	    case 2:
		printf("Please input the file name to save: ");
		scanf(" %[^\n]", name);
		if(SaveImage(name, R, G, B) >= 0)
		break;
	    case 3:
		BlackNWhite(R, G, B);
		break;
	    case 4:
		Negative(R, G, B);
		break;
	    case 5:
		printf("Enter Red component for the target color:");
		scanf(" %d", &tr);
		printf("Enter Green component for the target color:");
		scanf(" %d", &tg);
		printf("Enter Blue component for the targer color:");
		scanf(" %d", &tb);
		printf("Enter threshold for the color difference:");
		scanf(" %d", &range);
		printf("Enter value for Red component in the target color:");
		scanf(" %d", &vr);
		printf("Enter value for Green component in the targer color:");
		scanf(" %d", &vg);
		printf("Enter value for Blue component in the target color:");
		scanf(" %d", &vb);
		ColorFilter(R, G, B, tr, tg, tb, range, vr, vg, vb);
		break;
	    case 6:
		Edge(R, G, B);
		break;
	    case 7:
		Shuffle(R, G, B);
		break;
	    case 8:
		VFlip(R, G, B);
		break;
	    case 9:
		VMirror(R, G, B);
		break;
	    case 10:
		AddBorder(R, G, B, "EngPlaza", 32);
		printf("This function is currently unsupported\n");
		break;
	    case 11:
		AutoTest(R, G, B);
		break;
	    case 12:
		printf("Exiting program... Bye!\n");
	 	break;
	    default:
		printf("please type in a valid choice. Try again.\n");
		break;								
	    }	
    } while(choice != 12);
    return 0;
    /* End of replacing */
}

int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}

void PrintMenu(void){
	printf ("---------------------------------------------------\n");
	printf("1: Load a PPM image\n");
	printf("2: Save an image in PPM and JPEG format\n");
	printf("3: Change a color image to Black & White\n");
	printf("4: Make a negative of an image\n");
	printf("5: Color filter an image\n");
	printf("6: Sketch the edge of an image\n");
	printf("7: Shuffle an image\n");
	printf("8: Flip an image vertically\n");
	printf("9: Mirror an image vertically\n");
	printf("10: Add Border to an image\n");
	printf("11: Test all functions\n");
	printf("12: Exit\n");
}

void BlackNWhite(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]){
    unsigned char temp_r;
    unsigned char temp_g;
    unsigned char temp_b;
    for(int c = 0; c < 512; c++){
	for(int r = 0; r < 288; r++){
	    temp_r =  R[c][r];
	    temp_g = G[c][r];
	    temp_b = B[c][r];
	    R[c][r] = (temp_r + temp_g + temp_b)/3;
	    G[c][r] = (temp_r + temp_g + temp_b)/3;
	    B[c][r] = (temp_r + temp_g + temp_b)/3;
	}
    } 
    printf("\"Black and White\" Operation is done!\n");
}

void Negative(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]){
    for(int c = 0; c < 512; c++){
        for(int r = 0; r < 288; r++){
	    R[c][r] = 255 - R[c][r];
	    G[c][r] = 255 - G[c][r];
	    B[c][r] = 255 - B[c][r];
	}
    }
    printf("\"Negative\" Operation is done!\n");
}

void ColorFilter(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT],
		int target_r, int target_g, int target_b, int threshold,
		int replace_r, int replace_g, int replace_b){
    if(replace_r < 0)
	replace_r = 0;
    if(replace_g < 0)
	replace_g = 0;
    if(replace_b < 0)
	replace_b = 0;
    if(replace_r > 255)
	replace_r = 255;
    if(replace_g > 255)
	replace_g = 255;
    if(replace_b > 255)
	replace_b = 255;
    for(int c = 0; c < 512; c++){
        for(int r = 0; r < 288; r++){
	    if((R[c][r] < (target_r + threshold)) && (R[c][r] > (target_r - threshold)))
		R[c][r] = (char)(replace_r);
	    if((G[c][r] < (target_r + threshold)) && (G[c][r] > (target_r - threshold)))
		G[c][r] = (char)(replace_g);
	    if((B[c][r] < (target_r + threshold)) && (B[c][r] > (target_r - threshold)))
		B[c][r] = (char)(replace_b);
	}
    }
    printf("\"ColorFilter\" Operation is done!\n");
}

void Edge(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]){
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
	    saturate_r = tempr[c][r]*8 - tempr[c-1][r-1] - tempr[c-1][r] - tempr[c-1][r+1] - tempr[c][r-1] - tempr[c][r+1] - tempr[c+1][r-1] - tempr[c+1][r] - tempr[c+1][r+1];
	    saturate_g = tempg[c][r]*8 - tempg[c-1][r-1] - tempg[c-1][r] - tempg[c-1][r+1] - tempg[c][r-1] - tempg[c][r+1] - tempg[c+1][r-1] - tempg[c+1][r] - tempg[c+1][r+1];
	    saturate_b = tempb[c][r]*8 - tempb[c-1][r-1] - tempb[c-1][r] - tempb[c-1][r+1] - tempb[c][r-1] - tempb[c][r+1] - tempb[c+1][r-1] - tempb[c+1][r] - tempb[c+1][r+1];
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
    printf("\"Edge\" Operation is done!\n");
}


void VMirror(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]){
    for(int c = 0; c < 512; c++){
	for(int r = 0; r < 144; r++){
	    R[c][287-r] = R[c][r];
	    G[c][287-r] = G[c][r];
	    B[c][287-r] = B[c][r];
	}
    }	           
    printf("\"VMirror\" Operation is done!\n");
}

void Shuffle(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]){
    int arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int count = 0;
    int r1;
    int r2;
    unsigned char temp;
    srand(time(0));
    while(count != 16){
	count = 0;
	r1 = rand() % 16;
	r2 = rand() % 16;
	arr[r1] = arr[r1] + 1;
	arr[r2] = arr[r2] + 1;
	for(int k = 0; k < 16; k++){
	    if(arr[k] == 0){
		break;
	    }else{
		count = count + 1;
	    }
	}
	for(int i = 0; i < 128; i++){
	    for(int j = 0; j < 72; j++){
		temp = R[(r1%4)*128+i][(r1/4)*72+j];
		R[(r1/4)*128][(r1/4)*72+j] = R[(r2%4)*128][(r2%4)*72+j];;
		R[(r2/4)*128][(r2%4)*72+j] = temp;
		temp = G[(r1/4)*128+i][(r1%4)*72+j];
		G[(r1/4)*128][(r1%4)*72+j] = G[(r2/4)*128][(r2%4)*72+j];
		G[(r2/4)*128+i][(r2%4)*72+j] = temp;
		temp = B[(r1/4)*128][(r1%4)*72+j];
		B[(r1/4)*128][(r1%4)*72+j] = B[(r2/4)*128][(r2%4)*72+j];
		B[(r2/4)*128][(r2%4)*72+j] = temp;
	    }
	}
    }
    printf("\"Shuffle\" Operation is done!\n");		
}

void AddBorder(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT],
		char color[SLEN], int border_width){
}

void VFlip(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]){
   unsigned char tempp; 
   for(int c = 0; c < 512; c++){
        for(int r = 0; r < 144; r++){
	    tempp = R[c][r];
	    R[c][r] = R[c][287-r];
	    R[c][287-r] = tempp;
            tempp = G[c][r];
            G[c][r] = G[c][287-r]; 
	    G[c][287-r] = tempp;
	    tempp = B[c][r];
	    B[c][r] = B[c][287-r];
	    B[c][287-r] = tempp;  
   	}
   }
   printf("\"VFlip\" Operation is done!\n");
}

void AutoTest(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]){
    
    LoadImage("EngPlaza", R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    printf("Black and White tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    Negative(R, G, B);
    SaveImage("negative", R, G, B);
    printf("Negative tested!\n\n");
    
    LoadImage("EngPlaza", R, G, B);
    ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
    SaveImage("colorfilter", R, G, B);
    printf("Color Filter tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    Edge(R, G, B);
    SaveImage("edge", R, G, B);
    printf("Edge Detection tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    Shuffle(R, G, B);
    SaveImage("shuffle", R, G, B);
    printf("Shuffle tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    VFlip(R, G, B);
    SaveImage("vflip", R, G, B);
    printf("Vertical Flip tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    VMirror(R, G, B);
    SaveImage("vmirror", R, G, B);
    printf("Vertical Mirroring tested!\n\n");   
}
