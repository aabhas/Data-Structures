// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <math.h>

Quadtree::Quadtree()
{
	root = NULL;
}

Quadtree::Quadtree(const PNG &source, int resolution)
{
	root=NULL;//res = resolution;
	buildTree(source, resolution);
}

Quadtree::Quadtree(Quadtree const & other)
{
	if(other.root != NULL)
	{
		res = other.res;
		root = copy(other.root);
	}
	else root = NULL;
}

Quadtree::QuadtreeNode * Quadtree::copy(QuadtreeNode *other)
{
	if(other != NULL)
	{
		QuadtreeNode *curr = new QuadtreeNode(other);
		curr->neChild = copy(other->neChild);
		curr->nwChild = copy(other->nwChild);
		curr->swChild = copy(other->swChild);
		curr->seChild = copy(other->seChild);
		return curr;
	}
	else return NULL;
}

Quadtree::~Quadtree()
{
	if(root != NULL) clear(root);
}

void Quadtree::clear(QuadtreeNode * &other)
{
	if(other == NULL) return;
	clear(other->neChild);
	clear(other->nwChild);
	clear(other->swChild);
	clear(other->seChild);
	delete other;
	other = NULL;
}

Quadtree const & Quadtree::operator=(Quadtree const & other)
{
	if(this != &other)
	{
		res = other.res;
		clear(root);
		root = copy(other.root);
	}
	return other;
}	
/*
bool Quadtree::operator==(Quadtree const & other) const
{
	return checkSame(root, other->root);
}

bool Quadtree::checkSame(QuadtreeNode const * curr, QuadtreeNode const * other) const
{
	if(curr == NULL)&&(other == NULL) return true;
	if(curr == NULL)||(other == NULL) return false;
	if(curr->neChild == NULL)&&(other->neChild == NULL)
	{
		return (curr->element.red == other->element.red)&&(curr->element.green == other->element.green)&&(curr->element.blue == other->element.blue);
	}
	return(checkSame(curr->neChild, other->neChild)&&checkSame(curr->nwChild, other->nwChild)&&checkSame(curr->swChild, other->swChild)&&checkSame(curr->seChild, other->seChild));
}
*/
void Quadtree::buildTree(PNG const & source,int resolution)
{
	res = resolution;
	clear(root);
	root = buildTree(source, resolution, 0, 0); 
}	

Quadtree::QuadtreeNode* Quadtree::buildTree(PNG const & source,int resolution, int x, int y)
{
	
	QuadtreeNode *curr = new QuadtreeNode();
	if(resolution == 1) 
	{
		curr->element = *source(x,y);
		return curr;
	}
	
	curr->neChild = buildTree(source, resolution/2, x+(resolution/2) , y);
	curr->nwChild = buildTree(source, resolution/2, x, y);
	curr->swChild = buildTree(source, resolution/2, x, y+(resolution/2));
	curr->seChild = buildTree(source, resolution/2, x+(resolution/2) , y+(resolution/2));

	curr->element.red = (curr->nwChild->element.red + curr->neChild->element.red + curr->swChild->element.red + curr->seChild->element.red)/4; 
    curr->element.green = (curr->nwChild->element.green + curr->neChild->element.green + curr->swChild->element.green + curr->seChild->element.green)/4; 
    curr->element.blue = (curr->nwChild->element.blue + curr->neChild->element.blue + curr->swChild->element.blue + curr->seChild->element.blue)/4;

	return curr;
}

RGBAPixel Quadtree::getPixel(int x,int y) const
{
	if((x > res)||(y > res)||(root == NULL)) return RGBAPixel();	
	return searchPixel(root, x, y, 0, 0, res);
}	

RGBAPixel Quadtree::searchPixel(QuadtreeNode * other, int x, int y, int l, int m, int resolution) const
{
	if((other->neChild == NULL)||(resolution == 1))
	{
			return other->element;
	}
	
	if((x < l+resolution/2)&&(x >= l)&&(y < m+resolution/2)&&(y >= m)) 
		return searchPixel(other->nwChild, x, y, l, m, resolution/2);
	else if((x >= l+resolution/2)&&(x < l+resolution)&&(y < m+resolution/2)&&(y >= m)) 
		return searchPixel(other->neChild, x, y, l+resolution/2, m, resolution/2);
	else if((x < l+resolution/2)&&(x >= l)&&(y >= m+resolution/2)&&(y <= m+resolution))
		return searchPixel(other->swChild, x, y, l, m+resolution/2, resolution/2);
	else return searchPixel(other->seChild, x, y, l+resolution/2, m+resolution/2, resolution/2);
}

PNG Quadtree::decompress() const
{
	PNG object;
	if(root == NULL) return object;
	object.resize(res, res);
	for(int i = 0; i < res; i++)
	{
		for(int j = 0; j < res; j++)
		{
			*object(i,j) = getPixel(i,j);
		}
	}
	return object;
}	

int Quadtree::idealPrune(int numLeaves) const
{
	int high = 5000000;
	int low = 0;
	return idealPrune(low, high, high/2, numLeaves);
}

int Quadtree::idealPrune(int low, int high, int trial, int numLeaves) const
{
	
	if(low >= high) 
		return trial;
	int test = pruneSize(trial);
	if(test <= numLeaves)
	 high = trial;
	else
	 low = trial + 1;
	return idealPrune(low, high, (high + low)/2, numLeaves);
}

int Quadtree::pruneSize(int tolerance) const
{
	int count = 0;
	if(root != NULL)
	return pruneSize(count, root, tolerance);
	else return 0;
}

int Quadtree::pruneSize(int count, QuadtreeNode * curr, int tol) const
{
	if(curr->neChild == NULL) 
	{
		count = 1;
		return count;
	}
	if(checkPrune(curr->element, curr, tol))
	{
		count = 1;
		return count;
	}
	count = pruneSize(count, curr->neChild, tol) + pruneSize(count, curr->nwChild, tol) + pruneSize(count, curr->swChild, tol) + pruneSize(count, curr->seChild, tol);
	return count;
}

void Quadtree::prune(int tolerance)	
{
	if(root != NULL)
	 prune(root, tolerance);
	return;
}

void Quadtree::prune(QuadtreeNode * curr, int tol)
{
	if(curr == NULL) return;
	
	if(checkPrune(curr->element, curr, tol))
	{
		clear(curr->neChild);
		clear(curr->nwChild);
		clear(curr->swChild);
		clear(curr->seChild);
		return;
	}
	
	prune(curr->neChild, tol);
	prune(curr->nwChild, tol);
	prune(curr->swChild, tol);
	prune(curr->seChild, tol);
		
}	

bool Quadtree::checkPrune(RGBAPixel avg, QuadtreeNode * curr, int tol) const
{
	if(curr == NULL) return false;
	else
	{
		if(curr->neChild == NULL)
		{
			int r = curr->element.red;
			int g = curr->element.green;
			int b = curr->element.blue;
			int diff = pow((r - avg.red),2) + pow((g - avg.green),2) + pow((b - avg.blue),2);
			if(diff > tol) return false;
			else return true;
		}
	
		return checkPrune(avg, curr->neChild, tol) && checkPrune(avg, curr->nwChild, tol) && checkPrune(avg, curr->swChild, tol) && checkPrune(avg, curr->seChild, tol);
	}
}

void Quadtree::clockwiseRotate()
{
	clockwiseRotate(root);
}

Quadtree::QuadtreeNode* Quadtree::clockwiseRotate(QuadtreeNode * curr)
{
	if(curr/*->neChild*/ == NULL)
		return curr;
	QuadtreeNode *temp = curr->seChild;
	curr->seChild = clockwiseRotate(curr->neChild);
	curr->neChild = clockwiseRotate(curr->nwChild);
	curr->nwChild = clockwiseRotate(curr->swChild);
	curr->swChild = clockwiseRotate(temp);
	temp = NULL;
	return curr;
}
