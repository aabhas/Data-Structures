/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 * @author CS 225 course staff
 * @date Fall 2009
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template<class T>
void Queue<T>::enqueue(T const & newItem)
{
    /**
     * @todo Your code here!
     */
     /*
	if((!(outStack.isEmpty()))&&(!(inStack.isEmpty())))
	{
		T temp = inStack.pop();
		while(!(outStack.isEmpty()))
    	{
    		T temp2 = outStack.pop();
    		inStack.push(temp2);
    	}
		inStack.push(temp);
		inStack.push(newItem);
	}
	else */
	inStack.push(newItem);
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template<class T>
T Queue<T>::dequeue()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if(outStack.isEmpty())
    {
    	while(!(inStack.isEmpty()))
    	{
    		T temp = inStack.pop();
    		outStack.push(temp);
    	}
    }
    //else if((!(outStack.isEmpty()))&&(!(inStack.isEmpty())))return inStack.pop();
	//return outStack.pop();   
	T temp = outStack.pop();
    return temp;
}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Queue<T>::add( const T & theItem ) {
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to add the element to the Queue.
     */
	enqueue(theItem);
}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Queue<T>::remove() {
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to remove an element from the Queue and return it. You will
     *  need to replace the following line.
     */
    return dequeue();
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template<class T>
T Queue<T>::peek()
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
     if(outStack.isEmpty())
    {
    	while(!(inStack.isEmpty()))
    	{
    		T temp = inStack.pop();
    		outStack.push(temp);
    	}
    	//T temp = outStack.pop();
    	//return temp;
    }
    //else if((!(outStack.isEmpty()))&&(!(inStack.isEmpty())))return inStack.pop();
	return outStack.peek();
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template<class T>
bool Queue<T>::isEmpty() const
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
   bool check = false;
   if((inStack.isEmpty())&&(outStack.isEmpty()))check = true;
   return check;
}
