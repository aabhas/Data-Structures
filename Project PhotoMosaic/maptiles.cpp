/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
	
	//return NULL;
	
	int row = theSource.getRows();
	int col = theSource.getColumns();
	
	MosaicCanvas * final = new MosaicCanvas(row, col);

	vector< Point<3> > tree;
	map<Point<3>, TileImage> theMap;
	
	for(int i = 0; i < theTiles.size(); i++)
	{
		RGBAPixel avg = theTiles[i].getAverageColor();
		Point<3> key(avg.red, avg.green, avg.blue);
		theMap[key] = theTiles[i];
		tree.push_back(key);
	}
	
	KDTree<3> fin(tree);
	
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			RGBAPixel c = theSource.getRegionColor(i, j);
			Point<3> p(c. red, c.green, c.blue);
			Point<3> output = fin.findNearestNeighbor(p);
			TileImage temp = theMap[output];
			final->setTile(i, j, temp);
		}
	}

	return final;
}
