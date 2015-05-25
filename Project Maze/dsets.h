#ifndef _DSETS_H_
#define _DSETS_H_

#include <vector>

using std::vector;

class DisjointSets{

	public:
		
		//addelements function
		void addelements(int num);
		
		//find function
		/*should run in O(log*n) time*/
		int find(int elem);
		
		//setunion function
		/* to be implemented using Height based union*/
		void setunion(int a, int b);			

	private:
		
		vector<int> set;

};

//#include "dsets.cpp"
#endif
