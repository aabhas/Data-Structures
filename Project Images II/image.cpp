#include "png.h"
#include "image.h"
#include <iostream>

using namespace std;

void Image::flipleft() //Flips the image along a vertical line
	{
		RGBAPixel temp;
		int width = this->width();
		int height = this->height();
		
		for(int i=0; i<width/2; i++)
		{
			for(int j=0;j<height; j++)
			{
				temp = (*(*this)(i,j));
				(*(*this)(i,j)) = (*(*this)((width-1-i),j));
				(*(*this)((width-1-i),j)) = temp;
			}
		}
	}
	

void Image::adjustbrightness(int r, int	g, int b) //change the brightness of the image
	{
		int width = this->width();
		int height = this->height();
		
		for(int i=0; i<width; i++)
		{
			for(int j=0; j<height; j++)
			{
				/*
				int case_r = ((*this)(i,j)->red+r);
				int case_g = ((*this)(i,j)->green+g);
				int case_b = ((*this)(i,j)->blue+b);
				//red
				if(case_r > 255) case_r = 255;
				else if(case_r<=0) case_r = 0;
				else
				{
					(*this)(i,j)->red = case_r;
				}				
				
				//green
				if(case_g > 255) case_g = 255;
				else if(case_g<=0) case_g = 0;
				else
				{
					(*this)(i,j)->green = case_g;
				}
				
				//blue
				if(case_b > 255) case_b = 255;
				else if(case_b<=0) case_b = 0;
				else
				{
					(*this)(i,j)->blue = case_b;
				}
				*/
				
				
				//red
				if(((*this)(i,j)->red+r)>255)
					(*this)(i,j)->red = 255;
				else if(((*this)(i,j)->red + r <= 0))
					(*this)(i,j)->red = 0;
				else
					{
						(*this)(i,j)->red = (*this)(i,j)->red + r;
					}			
				
				//green
					if(((*this)(i,j)->green+g)>255)
					(*this)(i,j)->green = 255;
				else if(((*this)(i,j)->green + g <= 0))
					(*this)(i,j)->green = 0;
				else
					{
						(*this)(i,j)->green = (*this)(i,j)->green + g;
					}	
				
				/*if((((*this)(i,j)->green + g)<255)&&(((*this)(i,j)->green + g)>0))
					(*this)(i,j)->green = (*this)(i,j)->green + g;
				else if ((*this)(i,j)->green + g <= 0)
					(*this)(i,j)->green = 0;
				else (*this)(i,j)->green = 255;
				*/
				
				
				//blue
					if(((*this)(i,j)->blue+b)>255)
					(*this)(i,j)->blue = 255;
				else if(((*this)(i,j)->blue + b <= 0))
					(*this)(i,j)->blue = 0;
				else
					{
						(*this)(i,j)->blue = (*this)(i,j)->blue + b;
					}	
				
				/*if((((*this)(i,j)->blue + b)<255)&&(((*this)(i,j)->blue + b)>0))
					(*this)(i,j)->blue = (*this)(i,j)->blue + b;
				else if ((*this)(i,j)->blue + b <= 0)
					(*this)(i,j)->blue = 0;
				else (*this)(i,j)->blue = 255;
				*/
				
			}
		}
	}
	

void Image::invertcolors()	//invert the colors of the image
	{
		int width = this->width();
		int height = this->height();
		
		for(int i=0; i<width; i++)
		{
			for(int j=0; j<height; j++)
			{
				(*this)(i,j)->red = 255 - (*this)(i,j)->red;
				(*this)(i,j)->green = 255 - (*this)(i,j)->green;
				(*this)(i,j)->blue = 255 - (*this)(i,j)->blue;
			}
		}	
	
	}		

