#include <iostream>
#include "rgbapixel.h"
#include "png.h"

int main() //It outputs a 180' rotated version of the inputted image
{

	RGBAPixel temp;	

	PNG image("in.png");

	int width = image.width();
	int height = image.height();
			
	for(int i=0; i < width/2; i++)
	{
		for(int j=0; j < height; j++)
		{
			
			temp = *image(i,j);
			*image(i,j) = *image((width-i-1),(height-j-1));
			*image(width-i-1,height-j-1) = temp;
	
			}
		}

	if (width % 2 == 0)	image.writeToFile("out.png"); //even
	
	else 
	{                                                 //odd
			for(int i=width/2; i < (width/2)+1; i++)
			{
				for(int j=0; j < height/2; j++)
				{
			
					temp = *image(i,j);
					*image(i,j) = *image((width-i-1),(height-j-1));
					*image(width-i-1,height-j-1) = temp;
	
				}
			}
			
			image.writeToFile("out.png");
		
		}
};				
