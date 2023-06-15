/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Winter 2022     */
/*                                                                   */
/* Updated by: Mariam Rakka                                          */
/* Date:   01/20/2022                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();


int main()
{
	int rc ;
	int bug;



#ifdef DEBUG
	bug = AutoTest();
	rc = 0 ;
#else
	int ChoiceByUser;			/* user input option */
	char fname[SLEN];		/* input file name */
	char colorOption[SLEN];	
	IMAGE *p = NULL;
	rc = 1 ;
	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &ChoiceByUser);


	/* ColorFilter() parameters */
	int target_r, target_g, target_b, threshold;
	double factor_r, factor_g, factor_b;

	/* AddBorder() parameter */
	int border_width;
	unsigned char rbits, gbits, bbits;

	/* Noise() parameter */
	int n;

	/* MotionBlur() parameter */
	int motion_amount;

	/* Crop() parameter*/
	int xoffset, yoffset, cropW, cropH; 
	
	/* Brightness And Contrast() parameter*/
	int bright, contrast;
	int per;

	while (ChoiceByUser != EXIT) {
		if (ChoiceByUser == 1) {
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			p = malloc(sizeof(IMAGE));
			p = LoadImage(fname);
			assert(p);
			if(p == NULL){
			    rc = 1;
			}else{
			    rc = 0;
		}

		/* menu item 2 - 14 requires image is loaded first */
		}else if (ChoiceByUser >= 2 && ChoiceByUser <= 18) {
			if (rc != SUCCESS)	 {
				printf("No image is read.\n");
			}
			/* now image is loaded */
			else {	
				switch (ChoiceByUser) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%s", fname);
						SaveImage(fname, p);
						DeleteImage(p);
						p = NULL;
						break;
					case 3:
						p = BlackNWhite(p);
						printf("\"Black & White\" operation is done!\n");
						break;
					case 4:
						p = Negative(p);
						printf("\"Negative\" operation is done!\n");
						break;
					case 5:
						printf("Enter Red   component for the target color: ");
						scanf("%d", &target_r);
						printf("Enter Green component for the target color: ");
						scanf("%d", &target_g);
						printf("Enter Blue  component for the target color: ");
						scanf("%d", &target_b);
						printf("Enter threshold for the color difference: ");
						scanf("%d", &threshold);
						printf("Enter value for Red component in the target color: ");
						scanf("%lf", &factor_r);
						printf("Enter value for Green component in the target color: ");
						scanf("%lf", &factor_g);
						printf("Enter value for Blue  component in the target color: ");
						scanf("%lf", &factor_b);

						p = ColorFilter(p, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
						printf("\"Color Filter\" operation is done!\n");
						break;
					case 6:
						p = Edge(p);
						printf("\"Edge\" operation is done!\n");
						break;
					case 7:
						p = Shuffle(p);
						printf("\"Shuffle\" operation is done!\n");
						break;
					case 8:
						p = VFlip(p);
						printf("\"VFlip\" operation is done!\n");
						break;
					case 9:
						p = VMirror(p);
						printf("\"Vertically Mirror\" operation is done!\n");
						break;
					case 10:
						printf("Enter border width:");
						scanf("%d", &border_width);
						printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
						printf("Select border color from the options: ");
						scanf("%s",colorOption);
						p = AddBorder(p, colorOption, border_width);
						printf("\"Border\" operation is done!\n");
						break;
					case 11: 
						printf("Please input noise percentage: ");
						scanf("%d", &n);
						p = Noise(n, p);
						printf("\"Noise\" operation is done!\n");
						break;
					case 12:
						p = Sharpen(p);
						printf("\"Sharpen\" operation is done!\n"); 
						break;		
					case 13:
						printf("Enter the number of posterization bits for R channel (1 to 8):");
						scanf("%hhu", &rbits);
						printf("Enter the number of posterization bits for G channel (1 to 8):");
						scanf("%hhu", &gbits);
						printf("Enter the number of posterization bits for B channel (1 to 8):");
						scanf("%hhu", &bbits);
						p = Posterize(p, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n");
						break;
					case 14: 
						printf("Please input motion blur amount: ");
						scanf("%d", &motion_amount);
						p = MotionBlur(motion_amount, p);
						printf("\"Motion Blur\" operation is done!\n"); 
						break;
					case 15: 
						printf("Please enter the X offset value: ");
						scanf(" %d", &xoffset);
						printf("Please enter the Y offset value: ");
						scanf(" %d", &yoffset);
						printf("Please input the crop width: ");
						scanf(" %d", &cropW);
						printf("Please input the crop height: ");
						scanf(" %d", &cropH);
						Crop(p, xoffset, yoffset, cropW, cropH);
						printf("\"Crop\" operation is done!\n");
						break;
					case 16: 
						printf("Please input the resizing percentage (integer between 1 - 500): ");
						scanf(" %d", &per);
						p = Resize(p, per);
						printf("\"Resizing the image\"operation is done!\n");
						break;
					case 17:
						printf("Please input the brightness level (integer between -255 - 255): ");
						scanf(" %d", &bright);
						printf("Please input the contrast level (integer between -255 - 255): ");
						scanf(" %d", &contrast);
						p = BrightnessAndContrast(p, bright, contrast);
						printf("\"Brightness and Contrast\" operation is done!\n");
						break;
					case 18:
						printf("Watermark Operation is currently not supported:(\n");
						break;
					default:
						break;

				}
			}
		}

		else if (ChoiceByUser == 19) {
			bug = AutoTest();
			rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
		}else if(ChoiceByUser == 20){
			printf("You exit the program.\n");
			return 0;
		}
		else {
			printf("Invalid selection!\n");
		}

		/* Process finished, waiting for another input */
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &ChoiceByUser);
	}
	printf("Exiting...Bye!\n");	
#endif

	return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
	printf("\n----------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image vertically\n");
	printf(" 9: Mirror an image vertically\n");
	printf("10: Add border to an image\n");
	printf("11: Add Noise to an image\n");
	printf("12: Sharpen an image\n");
	printf("13: Posterize an image\n");
	printf("14: Add Motion Blur to an image\n");
	printf("15: Crop an image\n");
	printf("16: Resize an image\n");
	printf("17: Adjust the Brightness and Contrast of an image\n");
	printf("18: Add Watermark to an image\n");
	printf("19: Test all functions\n");
	printf("20: Exit\n");
}



