Project 7: Mazes

Code Author: Aabhas Sharma

In this Project I have:
 - Implemented the disjoint sets data structure.
 - Created a program to generate random mazes.
 - Understood graphs, graph distances, and graph traversal.
 - Represented a maze and its solution on a PNG.
 
![alt text][maze]
[maze] = https://courses.engr.illinois.edu/cs225/mps/mp7/solved.jpg

Function documentation

 - void DisjointSets::addelements	(	int 	num	)	
        Creates n unconnected root nodes at the end of the vector.
        Parameters
        num	The number of nodes to create
        int DisjointSets::find	(	int 	elem	)	
        This function should compress paths and works as described in lecture.

        Returns
        the index of the root of the up-tree in which the parameter element resides.


 - int DisjointSets::find(int elem)	
        This function should compress paths and works as described in lecture.

        Returns
        the index of the root of the up-tree in which the parameter element resides.

 - void DisjointSets::setunion(int a, int b)		
        This function should be implemented as union-by-size. That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger. This function works as described in lecture, except that you should not assume that the arguments to setunion are roots of existing uptrees.

        Your setunion function SHOULD find the roots of its arguments before combining the trees. If the two sets are the same size, make the tree containing the second argument point to the tree containing the first. (Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)

        Parameters
        a	Index of the first element to union
        b	Index of the second element to union

 - void SquareMaze::makeMaze(int width, int height)		
        Makes a new SquareMaze of the given height and width.

        If this object already represents a maze it will clear all the existing data before doing so. You will start with a square grid (like graph paper) with the specified height and width. You will select random walls to delete without creating a cycle, until there are no more walls that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.

        Parameters
        width	The width of the SquareMaze (number of cells)
        height	The height of the SquareMaze (number of cells)
        
 - bool SquareMaze::canTravel(int x, int y, int dir)
        This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).

        For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).

        dir = 0 represents a rightward step (+1 to the x coordinate)
        dir = 1 represents a downward step (+1 to the y coordinate)
        dir = 2 represents a leftward step (-1 to the x coordinate)
        dir = 3 represents an upward step (-1 to the y coordinate)
        You can not step off of the maze or through a wall.

        This function will be very helpful in solving the maze. It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, and to verify your maze solution. So make sure that this function works!

        Parameters
        x	The x coordinate of the current cell
        y	The y coordinate of the current cell
        dir	The desired direction to move from the current cell
        
        Returns
        whether you can travel in the specified direction

 - void SquareMaze::setWall	(int x, int y, int dir, bool exists)		
        Sets whether or not the specified wall exists.

        This function should be fast (constant time). You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. Our tests will call setWall to copy a specific maze into your implementation.

        Parameters
        x	The x coordinate of the current cell
        y	The y coordinate of the current cell
        dir	Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel). You only need to support setting the bottom and right walls of every square in the grid.
        exists	true if setting the wall to exist, false otherwise

 - vector< int > SquareMaze::solveMaze	(		)	
        Solves this SquareMaze.

        For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.

        Select the square in the bottom row with the largest distance from the origin as the destination of the maze. solveMaze() returns the winning path from the origin to the destination as a vector of integers, where each integer represents the direction of a step, using the same encoding as in canTravel().

        If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.

        Returns
        a vector of directions taken to solve the maze

 - PNG * SquareMaze::drawMaze()	const
        Draws the maze without the solution.

        First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). where height and width were the arguments to makeMaze. Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0). For each square in the maze, call its maze coordinates (x,y). If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

        The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.

        Returns
        a PNG of the unsolved SquareMaze

 - PNG * SquareMaze::drawMazeWithSolution	(		)	
        This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.

        Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 255,0,0 in RGB). Then if the second step is right, color pixels (5,15) through (15,15) red. Then if the third step is up, color pixels (15,15) through (15,5) red. Continue in this manner until you get to the end of the solution vector, so that your output looks analogous the above picture.

        Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.

        Returns
        a PNG of the solved SquareMaze