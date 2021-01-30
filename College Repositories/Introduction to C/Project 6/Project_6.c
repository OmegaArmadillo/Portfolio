/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct Pix
{

	unsigned char G;

	unsigned char R;
	
	unsigned char B;
	//unsigned char A;
}Pix;
#pragma pack(pop)

#pragma pack(push, 1)

typedef struct BitMap
{
	short Signature;
	long Reserved1;
	long Reserved2;
	long DataOffSet;

	long Size;
	long Width;
	long Height;
	short Planes;
	short BitsPerPixel;
	long Compression;
	long SizeImage;
	long XPixelsPreMeter;
	long YPixelsPreMeter;
	long ColorsUsed;
	long ColorsImportant;
	struct Pix *pixels;
} BitMap;
#pragma pack(pop)

int main(int argc, char **argv)
{



//changing the color of the image

	unsigned long int i = 0;//to count pixels read
	unsigned long int S = 0;//number of pixels to read

	struct BitMap source_info;//to store bitmap info header
	struct Pix source_pix;// to store pixels

	FILE *fp;		//input bitmap
	FILE *fpOut;	//output bitmap

	if (!(fp = fopen("C:\\Users\\matth\\Documents\\C Projects\\Project 6\\some.bmp", "rb")))//open in binary read mode
	{
		printf(" can not open file");//print and exit if file open error
		exit(-1);
	}

	fpOut = fopen("out.bmp", "wb");//open in binary write mode

	// read header
	fread(&source_info, (sizeof(BitMap) - sizeof(struct Pix*)), 1, fp);

	// total pixels
	S = source_info.Width*source_info.Height;

	// allocate space
	Pix *pixels = (struct Pix *) malloc(sizeof(struct Pix *) * S);
	source_info.pixels = pixels;

	int red = 255;
	int green = 106;
	int blue = 0;
	

	
	//read pixels
	for (i = 1; i <= S; i++)
	{
		fread(&source_pix, sizeof(struct Pix), 1, fp);

		

		if(source_pix.R == source_pix.G && source_pix.R == source_pix.B && source_pix.B == source_pix.G)
		{
			source_info.pixels[i] = source_pix;
		}
		
		else
		{
			source_pix.R = red;
			source_pix.G = green;
			source_pix.B = blue;
			source_info.pixels[i] = source_pix;
		}

				
	}

	
	
		
	// write header to dest file
	fwrite(&source_info, sizeof(source_info), 1, fpOut);

	// write pixels to dest file
	for (i = 0; i <= S; i++)
	{
		
	//	printf( "r %d	 g %d 	b %d",  source_info.pixels[i-1].R, source_info.pixels[i-1].G,  source_info.pixels[i-1].B);
	//	printf("\n");
		
		//YOUR CODE HERE
		if(source_info.pixels[i].R == 255 && source_info.pixels[i].G == 106 && source_info.pixels[i].B == 0)
		{
		   source_info.pixels[i].R = 255;
		   source_info.pixels[i].G = 128;
		   source_info.pixels[i].B = 192;
		   
		   
		}
		
			fwrite(&source_info.pixels[i], sizeof(struct Pix), 1, fpOut);
	}

	//close 
	fclose(fp);
	fclose(fpOut);

	//getchar();
	//return(0);
	
	
	
	
	
	
	
	
	
	unsigned long int j = 0;//to count pixels read
	unsigned long int t = 0;//number of pixels to read

	struct BitMap source_info2;//to store bitmap info header
	struct Pix source_pix2;// to store pixels

	FILE *fp2;		//input bitmap
	FILE *fpOut2;	//output bitmap

	if (!(fp2 = fopen("C:\\Users\\matth\\Documents\\C Projects\\Project 6\\some.bmp", "rb")))//open in binary read mode
	{
		printf(" can not open file");//print and exit if file open error
		exit(-1);
	}

	fpOut2 = fopen("out2.bmp", "wb");//open in binary write mode



	// read header
	fread(&source_info2, (sizeof(BitMap) - sizeof(struct Pix*)), 1, fp2);

	
	
	int pictureWidth = source_info2.Width/2;
	int pictureHeight = source_info2.Height/2;



		
	// total pixels
	t = source_info2.Width*source_info2.Height;

	// allocate space
Pix *pixels2 = (struct Pix *) malloc(sizeof(struct Pix *) * t);
	source_info2.pixels = pixels;

	
	
	//read pixels


	for (i = 1; i <= t; i++)
	{
		fread(&source_pix2, sizeof(struct Pix), 1, fp);

		

		if(source_pix2.R == source_pix2.G && source_pix2.R == source_pix2.B && source_pix2.B == source_pix2.G)
		{
			source_info2.pixels[i] = source_pix2;
		}
		else{
			source_pix2.R = red;
			source_pix2.G = green;
			source_pix2.B = blue;
			source_info2.pixels[i] = source_pix2;
			}

				
	}
	
	
	
	
	
//printing the top left corner
	
	// write header to dest file
	fwrite(&source_info2, sizeof(source_info2), 1, fpOut2);

	
	int positionWidth = 0;
	int positionHeight = 0;
	
	
	// write pixels to dest file
	for (int k = 0 ; k <= t; k++)
	{
	

		positionWidth++;

	
	
	
	if(positionHeight > pictureHeight)
	{


		if(positionWidth >= pictureWidth)
		{	

		
			source_info2.pixels[k].R = 255;
		   source_info2.pixels[k].G = 255;
		   source_info2.pixels[k].B = 255;
		

			fwrite(&source_info2.pixels[k], sizeof(struct Pix), 1, fpOut2);
				
		}

	
	
		else
		{
	
		
			fwrite(&source_info2.pixels[k], sizeof(struct Pix), 1, fpOut2);
		
		
		}
	
	
	

	
	}	

	
		else
		{
		
			source_info2.pixels[k].R = 255;
		   source_info2.pixels[k].G = 255;
		   source_info2.pixels[k].B = 255;
		
			fwrite(&source_info2.pixels[k], sizeof(struct Pix), 1, fpOut2);		
		}




		if(positionWidth == source_info2.Width)
		{
			positionWidth = 0;
			positionHeight++;	
		}



				
	
	}
	
	
	

	//close 
	fclose(fp2);
	fclose(fpOut2);

	//getchar();
	return 0;
	
	
}



