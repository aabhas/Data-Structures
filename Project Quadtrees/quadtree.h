// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	
	//Big Three
	Quadtree();
	
	Quadtree(const PNG &source, int resolution);
	
	Quadtree(Quadtree const &other);
	
	~Quadtree();
	
	//member functions
	
	Quadtree const & operator=(Quadtree const &other);
	
	void buildTree(PNG const & source,int resolution);
	
	RGBAPixel getPixel(int x,int y) const;
	
	PNG decompress() const;
	
	
	int idealPrune(int numLeaves)	const;
	int pruneSize(int	tolerance) const;
	void prune(int tolerance);
	void clockwiseRotate();
	//bool operator==(Quadtree const & other) const;
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		int x, y;
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		QuadtreeNode()
		{
			neChild = nwChild = seChild = swChild = NULL;
			element = RGBAPixel();
		}
		
		QuadtreeNode(QuadtreeNode const *other)
		{
			x = other->x;
			y = other->y;
			//res = other->res;
			neChild = nwChild = seChild = swChild = NULL;
			element = other->element;
		}
		
		QuadtreeNode(int xcoord, int ycoord, int resolution)
		{
			x = xcoord;
			y = ycoord;
			//res = resolution;
			neChild = nwChild = seChild = swChild = NULL;
		}

		QuadtreeNode(int xcoord, int ycoord, int resolution, PNG & source)
		{
			x = xcoord;
			y = ycoord;
			//res = resolution;
			neChild = nwChild = seChild = swChild = NULL;
			element = *(source(x,y));
		}
		
		RGBAPixel element;  // the pixel stored as this node's "data"
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	
	int res;
	//Helper functions
	QuadtreeNode* copy(QuadtreeNode *other);
	void clear(QuadtreeNode * &other);
	Quadtree::QuadtreeNode* buildTree(PNG const & source,int resolution, int x, int y);
	RGBAPixel searchPixel(QuadtreeNode * other, int x, int y, int l, int m, int resolution) const;
	int idealPrune(int low, int high, int trial, int numLeaves) const;
	int pruneSize(int count, QuadtreeNode * curr, int tol) const;
	void prune(QuadtreeNode * curr, int tol);
	bool checkPrune(RGBAPixel avg, QuadtreeNode * curr, int tol) const;
	//bool checkSame(QuadtreeNode const * curr, QuadtreeNode const * other) const;
	Quadtree::QuadtreeNode* clockwiseRotate(QuadtreeNode * curr);
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
