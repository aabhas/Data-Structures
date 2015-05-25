#include <stdio.h>
#include <math.h>
#include "dsets.h"

void DisjointSets::addelements(int num)
{
/**Creates n unconnected root nodes at the end of the vector
 
 *PARAMETERS
 *	num		The number of nodes to create

*/

	for(int i = 0; i < num; i++)
	{
		set.push_back(-1);
	}
}

int DisjointSets::find(int elem)
{
/**This function should compress paths and works as described in lecture.
 
 *RETURNS
 *	the index of the root of the up-tree in which the parameter element resides

*/

	if (set[elem] < 0) return elem;
	return find(set[elem]);
}	

void DisjointSets::setunion(int a, int b)
{
/**This function should be implemented as union-by-size.

 *That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger. This function works as described in lecture, except that you should not assume that the arguments to
 *setunion are roots of existing uptrees.

 *Your setunion function SHOULD find the roots of its arguments before combining the trees. If the two sets are the same size, make the tree containing the second argument point to the tree containing the first. 
 *(Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)
 
 
 *PARAMETERS
 *	a	Index of the first element to union
 *	b	Index of the second element to union
 
 */

	a = find(a);
	b = find(b);
	
	int size = set[a] + set[b];
	if(set[a] <= set[b])
	{
		set[b] = a;
		set[a] = size;
	}
	
	else
	{
		set[a] = b;
		set[b] = size;
	}
}
