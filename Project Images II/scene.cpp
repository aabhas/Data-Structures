#include "scene.h"
#include "image.h"
#include "png.h"
#include "rgbapixel.h"
#include <iostream>


using namespace std;

//Initializes this Scene object to be able to hold "max" number of images with indices 0 through max-1. 
Scene::Scene(int max1){
	max = max1;
	arr = new Image* [max];
	xi = new int[max];
	yi = new int[max];
	for(int i =0; i<max; i++)
		{
			arr[i] = NULL;
		}
	
	}

//Frees all space that was dynamically allocated by this Scene. 
Scene::~Scene()
	{
		clear();
	}
	

//The copy constructor makes this Scene an independent copy of the source. 	
Scene::Scene(const Scene &source)
	{
		copy(source);
	}

//The assignment operator for the Scene class. 	
const Scene& Scene::operator= (const Scene &source)
{
	if (this != &source)
	{
		clear();
		copy(source);
	}
	
	return *this;
}
	
	
//Modifies the size of the array of Image pointers without changing their indices. 	
void Scene::changemaxlayers(int newmax)
{	
		int counter=0;																				//  <-
	//for(int i=0;i<max;i++)
	//{
		//if(arr[i] != NULL)//<-
		//{//<-
		if(newmax >= max)
		{
			Image** arr_new = new Image*[newmax];
			int* xi_new = new int[newmax];
			int* yi_new = new int[newmax];
			for(int i =0; i<newmax; i++)
				{
					arr_new[i] = NULL;
				}
		
			for(int j =0; j<max; j++)
				{
						arr_new[j] = arr[j];
						xi_new[j] = xi[j];
						yi_new[j] = yi[j];
				}
			/*for(int j=0; j<max;j++)
			{
				delete arr[j];
				arr[j]=NULL;
			}*/
			delete []arr;
			delete []xi;
			delete []yi;
			arr = NULL;
			
			arr = arr_new;
			xi = xi_new;
			yi = yi_new;
			max=newmax;
		}
		
		else
		{
			for(int a=newmax; a<max; a++)
			{
				if(arr[a] != NULL)
				{															//  <-
					counter++;												//  <-
				}															//  <-
			}																//  <-
			
			if(counter !=0)													//  <-
			{																//  <-
					cout << "invalid newmax" << endl;						
					return;
			}
				else
				{
					Image** arr_new = new Image*[newmax];
					int* xi_new = new int[newmax];
					int* yi_new = new int[newmax];
					for(int i =0; i<newmax; i++)
						{
							arr_new[i] = NULL;
						}
		
					for(int j =0; j<newmax; j++)
						{
							arr_new[j] = arr[j];
							xi_new[j] = xi[j];
							yi_new[j] = yi[j];
						}
					/*for(int j=0; j<max;j++)
					{
						delete arr[j];
						arr[j]=NULL;
					}*/
		
					delete []arr;
					delete []xi;
					delete []yi;
					arr = NULL;
					
					arr = arr_new;
					xi = xi_new;
					yi = yi_new;
					max=newmax;
				}
			}
		//}
	//}

}
	
//This function will add a picture to the scene, by placing it in the array cell corresponding to the given index, and storing its x coordinate and y coordinate. 	
void Scene::addpicture (const char *FileName, int index, int x, int y)
	{
		if((index<0)||(index>max-1))
			cout<<"index out of bounds"<< endl;
		else
			{
				if(arr[index] != NULL)
				delete arr[index];
			
				arr[index] = new Image;
				arr[index]->readFromFile(FileName);
				xi[index] = x;
				yi[index] = y;
		
			}
	}

//Moves an Image from one layer to another. 	 	
 void Scene::changelayer (int index, int newindex)
 	{
 		
 		if((index<0)||(index>max)||(newindex<0)||(newindex>=max))
 				cout << "invalid index" << endl;
 		else {
 			
 			if(arr[newindex] != NULL)
 				arr[newindex] = NULL;
 		
 				arr[newindex] = arr[index];
 				xi[newindex] = xi[index];
 				yi[newindex] = yi[index];
 				arr[index] = NULL;
 			}
 	}
 
 //Changes the x and y coordinates of the Image in the specified layer. 	
 void Scene::translate (int index, int xcoord, int ycoord)
 	{
 		if((index<0)||(index>=max)||(arr[index]==NULL))
 			cout << "invalid index" << endl;
 		else
 		{
 			xi[index] = xcoord;
 			yi[index] = ycoord;
 		}
 	}
 	
 //Deletes the Image at the given index.	
 void Scene::deletepicture (int index)
 	{	
 		if((index<0)||(index>=max)||(arr[index]==NULL))
 			cout << "invalid index" << endl;
 		else
 			{
 				delete arr[index];
 				arr[index] = NULL;
 			}
 	} 
 	
 //This function will return a pointer to the Image at the specified index, not a copy of it. 	
 Image* Scene::getpicture (int index) const
 	{
 		if((index<0)||(index>=max))
 			{
 				return NULL;
 				cout << "invalid index" << endl;	
 			}	
 		else
 			{
 				return (arr[index]);
 			}
 		
 	}
 	
 //Draws the whole scene on one Image and returns that Image by value.	
 Image Scene::drawscene() const
 {	
 	unsigned int min_height=0;
 	unsigned int min_width = 0;
 	unsigned int hi = 0;
 	unsigned int wi = 0;
 	
 	for(int i=0;i<max;i++)
 	{
 		if(arr[i] != NULL)
 		{
 			if (xi[i]+ arr[i]->width() >= min_width)
 			{
 				min_width = arr[i]->width() + xi[i];
 			}
 		}
 		
 		if(arr[i] != NULL)
 		 {
 			if(yi[i]+arr[i]->height() >= min_height) 
 			{
 			   	min_height = arr[i]->height() + yi[i];
 			 }
 		} 
 	}
 		
	Image img_final;
	img_final.resize(min_width,min_height); 
	
	for(int a=0;a<max;a++)
	{  
 		if(arr[a] != NULL)
 		{
 			hi = arr[a]->height();
 			//cout<<a<<endl;
 			wi = arr[a]->width();
 			//cout<<hi<<"  "<<wi<<endl;

 			for(unsigned int j = 0; j<wi; j++)
 			{
 				for(unsigned int k = 0; k<hi; k++)
				{ 
					//cout <<"test" <<endl;
 					//(img_final((xi[i]+j),(yi[i]+k))) = ((*arr[i])(j,k));
 					*(img_final)((int)(j+xi[a]),(int)(yi[a]+k)) = *(*arr[a])((int)j,(int)k);
 				}
 			}
 		}
 	}
 	 		//	cout<< "end of draw" <<endl;
 	return img_final;
 }
 
 	
void Scene::copy(const Scene &other)
{
	max = other.max; 
	xi = new int [max]; 
	yi = new int [max];
	arr = new Image * [max]; 
	
	for(int i=0; i<max;i++)
	{
		xi[i] = other.xi[i];
		yi[i] = other.yi[i]; 				
		
		if (other.arr[i] != NULL)
		{
			arr[i] = new Image (*other.arr[i]);
		}
		else 
		{ 
			arr[i] = NULL;
		}	 
	}
}

void Scene::clear()
{
	delete []xi;
	xi = NULL;

	delete []yi;
	yi = NULL;

	for (int i = 0; i < max; i++)
	{
		if(arr[i] != NULL)
		{
			delete arr[i];
			arr[i] = NULL;
		}
	}
	
	delete []arr;
	arr = NULL;
}
