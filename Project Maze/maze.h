#ifndef _MAZE_H_
#define _MAZE_H_

#include "png.h"
#include <vector>
#include <stack>
#include "dsets.h"
#include <utility>
#include <algorithm>

using std::vector;

class SquareMaze{

	public:
		/** includes member function declarations*/


		SquareMaze();
		
		void makeMaze(int width, int height);
		
		bool canTravel(int x, int y, int dir)const;
		
		void setWall(int x, int y, int dir, bool exists);
		
		vector< int > solveMaze();
		
		PNG *drawMaze() const;
		
		PNG *drawMazeWithSolution();	
	
	private:
		
		//int pos(int x, int y);		
		
		class cell
		{
			public:
			bool downWall;
			bool rightWall;
			cell();
		};
		
		/*
		class triplet
		{
			public:
			int index_x;
			int index_y;
			int count;
			triplet();
			triplet(int a, int b, int c);
		};	
		*/
		
		//array of pointers
		vector<cell> grid;
		int gridWidth, gridHeight;
};

//#include "maze.cpp"
#endif
