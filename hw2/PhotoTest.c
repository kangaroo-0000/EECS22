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
void Edge(unsigned char R[WIDTH][HEIGHT]

/* print a menu */
,
