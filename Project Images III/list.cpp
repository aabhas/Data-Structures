/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
 #include "list.h"
 #include <iostream>
 #include <algorithm>
 using namespace std;
 
template <class T>
List<T>::~List()
{
	/// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
	
    /// @todo Graded in MP3.1
	if(head != NULL)
	{
		ListNode *temp = head;
		while(head->next != NULL)
		{
			temp = head;
			head = temp->next;
			temp->prev = NULL;
			temp->next = NULL;
			delete temp;	
		}
		tail->prev = NULL;
		tail->next = NULL;
		delete tail;
		head = NULL;
		tail = NULL;
		length = 0;
	}
	
	else
	{
		length = 0;
	}
	
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
	/// @todo Graded in MP3.1
	if(head == NULL)
	{
		ListNode *P = new ListNode(ndata);
		P->next = NULL;
		P->prev = NULL;
		head = P;
		tail = P;
		length++;
	}
	
	else
	{
		ListNode *P = new ListNode(ndata);
		P->next = head;
		head->prev = P;
		P->prev = NULL;
		head = P;
		P = NULL;
		length++;
	}
}
/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1
    if(head == NULL)
    {
    	ListNode *P = new ListNode(ndata);
		P->next = NULL;
		P->prev = NULL;
		head = P;
		tail = P;
		length++;
	}
	
    else
    {
		ListNode *P = new ListNode(ndata);
		P->prev = tail;
		tail->next = P;
		tail = P;
		//P->next = NULL;
		P = NULL;
		length++;
	}
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
	reverse(head, tail);
  
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
	
	if(startPoint == endPoint)
	{
		return;
	}
	
	else
		{	
				ListNode *t1 = startPoint;
				ListNode *t2 = startPoint;
				ListNode *t3 = startPoint;
				ListNode *tempStart = startPoint;
				while(t2 != endPoint)
				{
					t2 = t2->next;
					t1->next = t1->prev;
					t1->prev = t2;
					t1 = t2;
				}
				t3 = t1->next;
				t1->next = t1->prev;
				t1->prev = t3;
				//startPoint = endPoint;
				//endPoint = tempStart;
				
				std::swap(startPoint->next, endPoint->prev);
				std::swap(startPoint,endPoint);
		}
}
/*
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{	
	
    /// @todo Graded in MP3.1
    if(n > length) n = length;
	ListNode *startP = head;
	ListNode *endP = head;
	int count = 0;
	cout<<"this "<<length<<endl;
		while(count < length)
		{	
			int j=0;
			while((j<(n-1))&&(endP->next != NULL))
			{
				endP = endP->next;
				count++;
				j++;
				cout<<"this "<<count<<endl;
			}
			
			
			reverse(startP, endP);
			if(head==endP)head = startP;
			else startP->prev->next = startP;
			if(tail==startP)tail=endP;
			else endP->next->prev = endP;
			startP = endP->next;
			endP = startP;
			count++;
			cout<<"this "<<count<<endl;
		}
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    if(head == NULL)
		return;
    /// @todo Graded in MP3.1
	ListNode *curr = head;
	ListNode *temp = curr->next;
	
		while(temp != tail)
		{
			curr->next = temp->next;
			temp->next->prev = curr;
			tail->next = temp;
			temp->prev = tail;
			temp->next = NULL;
			tail = temp;
			curr=curr->next;
			temp = curr->next;
		}	
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
    //return NULL; // change me!
    
   if(start == NULL)
   {
   	return NULL;
   }
   else
   {
		ListNode * t1 = start;
		ListNode * t2 = start;
		int count = 0;
		int temp = splitPoint;
		while(temp != 0)
		{
			if(t1->next != NULL)
			{
				t1 = t1->next;
				count++;
			}
			temp--;
		}
		if(splitPoint > count)
		{
			return NULL;
		}
		else
		{
			t2 = t1->prev;
			t2->next = NULL;
			t1->prev = NULL;
			return t1;
		}
		
	}
	
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
   	ListNode * t1 = first;
	ListNode * t2 = second;
	ListNode * t3 = first;
	if((first != NULL)&&(second != NULL))
	{
		if(t1->data < t2->data)
		{
			t3 = t1;
			t1 = split(t1,1);	
		}
		else
		{
			t3 = t2;
			t2 = split(t2,1);
		}
		ListNode * t4 = t3;
		while((t1 != NULL)&&(t2 != NULL))
		{
			if(t1->data < t2->data)
			{
				t3->next = t1;
				t1->prev = t3;
				t1 = split(t1,1);
				t3 = t3->next;
			}
			else
			{
				t3->next = t2;
				t2->prev = t3;
				t2 = split(t2,1);
				t3 = t3->next;
			}
		}
		if((t1==NULL)&&(t2 != NULL))
		{
			t3->next = t2;
			t2->prev = t3;
		}
		else if((t2==NULL)&&(t1 != NULL))
		{
			t3->next = t1;
			t1->prev = t3;
		}
		return t4;
	}
	else if((first == NULL)&&(second != NULL))
   	{
   		return second;
   	}
   	else return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
    //return NULL; // change me!
    if(chainLength <=1)return start;
    int mid = chainLength/2;
    ListNode * newL = split(start, mid);
	start = mergesort(start, mid);
	newL = mergesort(newL, chainLength-mid);
	return merge(start, newL);
}




