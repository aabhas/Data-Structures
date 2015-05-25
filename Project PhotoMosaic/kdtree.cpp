/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <math.h>

//return true if first has a smaller (or equal) value than the second
template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    	
    	if(first[curDim] == second[curDim])
		if(first < second)
			return true;
			
	return (first[curDim] < second[curDim]);
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
     
    /*int dist_curBest, dist_poten = 0;
    for(int i = 0; i < Dim; i++)
    {
    	dist_curBest = dist_curBest + pow(currentBest[i] - target[i], 2);
    	dist_poten = dist_poten + pow(potential[i] - target[i], 2);
    }
   	if(dist_curBest != dist_poten) return dist_curBest > dist_poten;
    return (dist_poten < dist_curBest);*/
    
    if(dist(potential, target) < dist(currentBest, target)) return true;
    else if(dist(potential, target) > dist(currentBest, target)) return false;
    return(potential < currentBest);
}

template<int Dim>
int KDTree<Dim>::dist(const Point<Dim> &x, const Point<Dim> &y) const
{
	//return pow((x - y), 2);
	int total = 0;
	for(int i = 0; i < Dim; i++)
	{
		total = total + pow((x[i] - y[i]), 2);
	}
	return total;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	points = newPoints;
	if(points.size() != 0)
    	buildKDTree(0, newPoints.size()-1, 0);
}

template<int Dim>
void KDTree<Dim>::buildKDTree(int left, int right, int dimension)
{
	if(left >= right) return;
	
	select(left, right, (left+right)/2, dimension % Dim);
	
	buildKDTree((left+right)/2 + 1, right, (dimension+1) % Dim);
	buildKDTree(left, (left+right)/2 - 1, (dimension+1) % Dim);
}

template<int Dim>
int KDTree<Dim>::partition(int left, int right, int mid, int dim)
{
	Point<Dim> pivot_val = points[mid];
	points[mid] = points[right];
	points[right] = pivot_val;
	int l_bound = left;
	for(int i = left; i < right; i++)
	{
		if(smallerDimVal(points[i], points[right], dim))
		{
			Point<Dim> temp = points[i];
			points[i] = points[l_bound];
			points[l_bound] = temp;
			l_bound++;
		}
	}
	Point<Dim> temp = points[l_bound];
	points[l_bound] = points[right];
	points[right] = temp;
	return l_bound;
}

template<int Dim>
void KDTree<Dim>::select(int left, int right, int mid, int dimension)
{
	if(left >= right) return;
	 
	int pivot_index = partition(left, right, (left+right)/2, dimension);
	
	if(mid == pivot_index) return;
	if(mid > pivot_index) select(pivot_index+1, right, mid, dimension);
	else select(left, pivot_index-1, mid, dimension);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
	Point<Dim> curBest = points[(points.size()-1)/2];
    if(points.size() != 0)
    	curBest = findNearestNeighbor(0, points.size() - 1, query, curBest, -1);
    return curBest;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(int left, int right, const Point<Dim> & query, Point<Dim> & curBest, int dim) const
{
    if(left >= right)
    {
    	if(shouldReplace(query, curBest, points[left]))
    		curBest = points[left];
    	return curBest;
    }
    
    dim = (dim+1)%Dim;
    
    int radius = 0;
    int mid = (left+right)/2;
    //int distance = dist(query[dim%Dim], points[mid][dim%Dim]);
    
    if(shouldReplace(query, curBest, points[mid])) curBest = points[mid];
    
    //smallerDimVal takes first, second, curDim, returns whether first <= curBest
    if(smallerDimVal(points[mid], query, dim))
    {
    	curBest = findNearestNeighbor((left+right)/2 + 1, right, query, curBest, dim);
    	for(int i = 0; i < Dim; i++)
    		radius+= pow(query[i] - curBest[i], 2);
		if(pow(points[mid][dim%Dim] - query[dim%Dim], 2) <= radius)
			curBest = findNearestNeighbor(left, (left+right)/2 - 1, query, curBest, dim);	
	}
	else
	{
		curBest = findNearestNeighbor(left, (left+right)/2 - 1, query, curBest, dim);
		for(int i = 0; i < Dim; i++)
    		radius+= pow(query[i] - curBest[i], 2);
		if(pow(points[mid][dim%Dim] - query[dim%Dim], 2) <= radius)
			curBest = findNearestNeighbor((left+right)/2 + 1, right, query, curBest, dim);
	}
	
	return curBest;
}

