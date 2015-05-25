#include <stdio.h>
#include <math.h>
#include "maze.h"
#include "dsets.h"

using namespace std;

SquareMaze::SquareMaze()
{
/**
 *No-parameter constructor.

 *Creates an empty maze.
*/
	grid.clear();
	gridWidth = 0;
	gridHeight = 0;
}

SquareMaze::cell::cell()
	: rightWall(true), downWall(true)
{}

/*
SquareMaze::triplet::triplet()
{
	index_x = 0;
	index_y = 0;
	count = 0;
}

SquareMaze::triplet::triplet(int a, int b, int c)
{
	index_x = a;
	index_y = b;
	count = c;
}
*/	
		
void SquareMaze::makeMaze(int width, int height)
{
/**
 *Makes a new SquareMaze of the given height and width.

 *If this object already represents a maze it will clear all the existing data before doing so. You will start with a square grid (like graph paper) with the specified height and width. You will select random walls to
 *delete without creating a cycle, until there are no more walls that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.

 *Hints: You only need to store 2 bits per square: the "down" and "right" walls. The finished maze is always a tree of corridors.)
*/
	
	DisjointSets path;
	
	//clear the existing maze
	grid.clear();
	
	for(int i = 0; i < width*height; i++)
	{
		grid.push_back(cell());
	}
	
	gridWidth = width;
	gridHeight = height;
	int wallCounter = 0;
	path.addelements(height*width);
	
	srand(time(NULL));
	while(wallCounter != (width*height - 1))
	{
		int x = rand() % width;
		int y = rand() % height;
		bool side = rand()%2;
		if(side && (x < gridWidth - 1))
		{
			if(path.find(y*gridWidth + x) != path.find(y*gridWidth + x + 1))
			{
				path.setunion(path.find(y*gridWidth + x), path.find(y*gridWidth + x + 1));
				grid[y*gridWidth + x].rightWall = false;
				wallCounter++;
			}
		}
		else if(!side && (y < gridHeight - 1))
		{
			if(path.find(y*gridWidth + x) != path.find((y + 1)*gridWidth + x))
			{
				path.setunion(path.find(y*gridWidth + x), path.find((y + 1)*gridWidth + x));
				grid[y*gridWidth + x].downWall = false;
				wallCounter++;
			}
		}
	}
}
		
bool SquareMaze::canTravel(int x, int y, int dir)const
{
/**
 *This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).

 *For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).

 *dir = 0 represents a rightward step (+1 to the x coordinate)
 *dir = 1 represents a downward step (+1 to the y coordinate)
 *dir = 2 represents a leftward step (-1 to the x coordinate)
 *dir = 3 represents an upward step (-1 to the y coordinate)
 *You can not step off of the maze or through a wall.

 *This function will be very helpful in solving the maze. It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, and to verify
 *your maze solution. So make sure that this function works!
*/
	
	bool pass = false;
	if(( (y*gridWidth + x) < gridWidth*gridHeight) && ((y*gridWidth + x) >= 0))
	{
		if(dir == 0) pass = !grid[y*gridWidth + x].rightWall;
		else if(dir == 1) pass = !grid[y*gridWidth + x].downWall;
		else if(dir == 2)
		{
			if( (y*gridWidth + x -1) >= 0)
				pass = !grid[y*gridWidth + x - 1].rightWall;
		}
		else if(dir == 3)
		{
			if( ((y - 1)*gridWidth + x) >= 0)
				pass = !grid[(y - 1)*gridWidth + x].downWall;
		}
	
	}
	return pass;
}
		
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
/**
 *Sets whether or not the specified wall exists.

 *This function should be fast (constant time). You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. setWall should not prevent
 *cycles from occurring,but should simply set a wall to be present or not present. Our tests will call setWall to copy a specific maze into your implementation.

 *NOTE:	dir -> Either 0 (right) or 1 (down).

*/
	if(dir == 1)
		grid[y*gridWidth + x].downWall = exists;
	else
		grid[y*gridWidth + x].rightWall = exists;
	return;
}
		
vector< int > SquareMaze::solveMaze()
{
/**
 *Solves this SquareMaze.

 *For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), which is defined as the length (measured as a number of steps) of the only path through the maze
 *from the origin to that square.

 *Select the square in the bottom row with the -largest distance from the origin as the destination of the maze. solveMaze() returns the winning path from the origin to the
 *destination as a vector of integers, where each integer represents the direction of a step, using the same encoding as in canTravel().

 *If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.

 *Hint: this function should run in time linear in the number of cells in the maze.
*/
	//vector<int> blaa;
	
	stack<int> s;
	bool touched[gridWidth][gridHeight];
	pair<int,int> parent[gridWidth*gridHeight];
	
	for(int i = 0; i < gridWidth; i++)
	{
		for(int j = 0; j < gridHeight; j++)
		{
			touched[i][j]=false;
		}
	}
	
	int x, y = 0;
	s.push(0);
	touched[0][0] = true;
	parent[0] = make_pair(-1, 1);
	
	while(!s.empty())
	{
		int index = s.top();
		x = index/gridHeight;
		y = index%gridHeight;
		s.pop();
		if(canTravel(x, y, 0) && !touched[x+1][y])
		{
			s.push((x+1)*gridHeight + y);
			touched[x+1][y] = true;
			parent[(x+1)*gridHeight + y] = make_pair(x*gridHeight + y, parent[x*gridHeight+y].second + 1);
		}
		if(canTravel(x, y, 1) && !touched[x][y+1])
		{
			s.push(x*gridHeight + y + 1);
			touched[x][y+1] = true;
			parent[x*gridHeight + y + 1] = make_pair(x*gridHeight + y, parent[x*gridHeight + y].second + 1);
		}
		if(canTravel(x, y, 2) && !touched[x-1][y])
		{
			s.push((x-1)*gridHeight + y);
			touched[x-1][y] = true;
			parent[(x-1)*gridHeight + y]=make_pair(x*gridHeight + y, parent[x*gridHeight+y].second + 1);
		}
		if(canTravel(x, y, 3) && !touched[x][y-1])
		{
			s.push(x*gridHeight + y - 1);
			touched[x][y-1] = true;
			parent[x*gridHeight + y - 1] = make_pair(x*gridHeight + y, parent[x*gridHeight + y].second + 1);
		}
	}
	
	vector<int> route;
	int len = 0, finalCoord = 0;
	for(int i = 1; i <= gridWidth; i++)
	{
		if(len < parent[i*gridHeight - 1].second)
		{
			len = parent[i*gridHeight - 1].second;
			finalCoord = i*gridHeight - 1;
		}
	}
	
	while(finalCoord != -1)
	{
		route.push_back(finalCoord);
		finalCoord = parent[finalCoord].first;
	}
	
	vector<int> output;
	reverse(route.begin(), route.end());
	
	for(int i = 0; i < route.size() - 1; i++)
	{
		if((route[i] - route[i+1]) == gridHeight)
			output.push_back(2);
		else if((route[i]-route[i+1]) == -gridHeight)
			output.push_back(0);
		else if((route[i] - route[i+1]) == 1)
			output.push_back(3);
		else if((route[i] - route[i+1]) == -1)
			output.push_back(1);
	}
	
	return output;
	//return blaa;
}

/*
int SquareMaze::pos(int x, int y)
{
	return y*gridWidth + x;
}
*/
	
PNG * SquareMaze::drawMaze() const
{
/**
 *Draws the maze without the solution.

 *First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). where height and width were the arguments to makeMaze. Blacken the entire topmost row and leftmost column of pixels, except the
 *entrance (1,0) through (9,0). For each square in the maze, call its maze coordinates (x,y). If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall
 *exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

 *The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.
*/

	PNG * output = new PNG();
	output->resize(gridWidth*10 + 1,gridHeight*10 + 1);
	//int i,j,k;
	
	for(int i = 0; i < gridHeight*10 + 1; i++)
	{
		(*output)(0,i)->red = 0;
		(*output)(0,i)->green = 0;
		(*output)(0,i)->blue = 0;
	}
	
	for(int i = 10; i < gridWidth*10 + 1; i++)
	{
		(*output)(i,0)->red = 0;
		(*output)(i,0)->green = 0;
		(*output)(i,0)->blue = 0;
	}
	
	for(int i = 0; i < gridWidth; i++)
	{
		for(int j = 0; j < gridHeight; j++)
		{
			if(grid[j*gridWidth + i].rightWall)
			{
				for(int k = 0; k <= 10; k++)
				{
					 (*output)((i+1)*10, j*10 + k)->red=0;
					 (*output)((i+1)*10, j*10 + k)->green=0;
					 (*output)((i+1)*10, j*10 + k)->blue=0;
				}
			}
			if(grid[j*gridWidth + i].downWall)
			{
				for(int k = 0; k <= 10; k++)
				{
					 (*output)(i*10 + k, (j+1)*10)->red = 0;
					 (*output)(i*10 + k, (j+1)*10)->green = 0;
					 (*output)(i*10 + k, (j+1)*10)->blue = 0;
				}
			}
		}
	}
	
	return output;
}
		
PNG * SquareMaze::drawMazeWithSolution()
{
/**
 *This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.

 *Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 255,0,0 in
 *RGB). Then if the second step is right, color pixels (5,15) through (15,15) red. Then if the third step is up, color pixels (15,15) through (15,5) red. Continue in this manner until you get to the end of the
 *solution vector, so that your output looks analogous the above picture.

 *Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
*/

	//PNG* temp = new PNG;
	//return temp;
	
	PNG* output;
	output = drawMaze();
	vector<int> soln = solveMaze();
	
	//int i,j,k;
	unsigned int x = 5;
	unsigned int y = 5;
	
	for(int i = 0; i < soln.size(); i++)
	{
		if(soln[i] == 0)
		{
			for(int j = 0; j <= 10; j++)
			{
				(*output)(x+j,y)->red = 255;
				(*output)(x+j,y)->green = 0;
				(*output)(x+j,y)->blue = 0;
			}
			x = x + 10;
		}
		else if(soln[i] == 2)
		{
			for(int j=0; j <= 10; j++)
			{
				(*output)(x-j,y)->red = 255;
				(*output)(x-j,y)->green = 0;
				(*output)(x-j,y)->blue = 0;
			}
			x = x - 10;
		}
		else if(soln[i] == 1)
		{
			for(int j = 0; j <= 10; j++)
			{
				(*output)(x,y+j)->red = 255;
				(*output)(x,y+j)->green = 0;
				(*output)(x,y+j)->blue = 0;
			}
			y = y + 10;
		}
		else if(soln[i] == 3)
		{
			for(int j = 0; j <= 10; j++)
			{
				(*output)(x, y-j)->red = 255;
				(*output)(x, y-j)->green = 0;
				(*output)(x, y-j)->blue = 0;
			}
			y = y - 10;
		}
	}
	for(int i = -4; i <= 4; i++)
	{
		(*output)(x+i,y+5)->red = 255;
		(*output)(x+i,y+5)->green = 255;
		(*output)(x+i,y+5)->blue = 255;
	}
	return output;
}

/*
bool touched[gridWidth][gridHeight];
	pair<int, int> coord;
	stack< pair<int, int> > s;
	triplet parent[gridWidth*gridHeight];
	
	for(int i = 0; i < gridWidth; i++)
	{
		for(int j = 0; j < gridHeight; j++)
		{
			touched[i][j] = false;	
		}
	}
	
	int x,y = 0;
	touched[0][0] = true;
	s.push(make_pair(x,y));
	parent[0] = triplet(-1, -1, 1);
	while(!s.empty())
	{
		pair<int, int> index = s.top();
		s.pop();
		x = index.first;
		y = index.second;
		
		if( (canTravel(x, y, 0)) && (!touched[x + 1][y]) )
		{
			index.first = x + 1;
			index.second = y;
			s.push(index);
			touched[x+1][y] = true;
			parent[y*gridWidth + x + 1] = triplet(x, y, parent[y*gridWidth+x].count + 1);
		}
		
		if( (canTravel(x, y, 1)) && (!touched[x][y + 1]) )
		{
			index.first = x;
			index.second = y + 1;
			s.push(index);
			touched[x][y+1] = true;
			parent[(y + 1)*gridWidth + x] = triplet(x, y, parent[y*gridWidth+x].count + 1);
		}
		
		if( (canTravel(x, y, 2)) && (!touched[x - 1][y]) )
		{
			index.first = x - 1;
			index.second = y;
			s.push(index);
			touched[x-1][y] = true;
			parent[y*gridWidth + x - 1] = triplet(x, y, parent[y*gridWidth+x].count + 1);
		}
		
		if( (canTravel(x, y, 3)) && (!touched[x][y - 1]) )
		{
			index.first = x;
			index.second = y - 1;
			s.push(index);
			touched[x][y - 1] = true;
			parent[(y - 1)*gridWidth + x] = triplet(x, y, parent[y*gridWidth+x].count + 1);
		}
	}	
	
	vector<int> route;
	int len, finalCoord = 0;
	
	for(int i = (y-1)*gridWidth; i < y*gridWidth; i++)
	{
		if(len < parent[i].count)
		{
			len = parent[i].count;
			finalCoord = i;
		}
	}
	
	while(parent[finalCoord].index_x != -1)
	{
		route.push_back(finalCoord);
		finalCoord = pos( parent[finalCoord].index_y, parent[finalCoord].index_x );
	}
	
	reverse(route.begin(), route.end());
	//return route;
	vector<int> output;
	
	for(int i = 0; i < route.size(); i++)
	{
		if((route[i]-route[i+1])==gridHeight)
			output.push_back(2);
		else if((route[i]-route[i+1])==-gridHeight)
			output.push_back(0);
		else if((route[i]-route[i+1])==1)
			output.push_back(3);
		else if((route[i]-route[i+1])==-1)
			output.push_back(1);
	}
	
	return output;
*/
