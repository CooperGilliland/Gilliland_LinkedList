#pragma once
#include "PreprocessorManager.h"
//Macros
template <class T>
class CLinkedList
{
public:
	//public variables
	struct Node //Struct data structure containing smart pointers and a template variable
	{
		T data;
		shared_ptr<Node> next;
		shared_ptr<Node> prev;
	};
	//con/destructor prototypes
	CLinkedList();
	~CLinkedList();
	//Public method prototypes 
	bool getHead();
	bool getTail();
	shared_ptr<Node>& getStorage();
	void resetIterators();
	void insertLast(T addData);
	void insertFirst(T addData);
	void remove(T addData);
	void clearList();
	T front();
	T back();
	int size();
	T maxVal();
	T minVal();
	shared_ptr<Node>& findAddress(T searchKey);
	void delByAddress(shared_ptr<Node>& nodeKey);
private:
	//Private variables
	//Two smart pointers that serve as sentinal nodes
	shared_ptr<Node> head;
	shared_ptr<Node> tail;
	//Smart Pointers that will serve as iterators 
	shared_ptr<Node> iterLast;
	shared_ptr<Node> iterFirst;	
	//Item for storing address values
	shared_ptr<Node> storage;
}; 
//Method definitions //note: with template classes, it is best to keep functions with class prototype
//constructor
template <class T>
CLinkedList<T>::CLinkedList()
{
	cout << "New list created" << endl;
	//0 items means head and tail point to null
	head = NULL;
	tail = NULL;
}
//Destructor
template <class T>
CLinkedList<T>::~CLinkedList()
{
	cout << "Deconstructing List" << endl;
}
/*
* This function is used to check
* if there are items in the list
*/
template <class T>
bool CLinkedList<T>::getHead()
{
	//local variable
	bool temp = false; 
	//Conditional on tail being a null pointer
	if (head != NULL)
	{
		//set temp to true. This will be used
		//To determine if the list currently
		//Contains any elements
		temp = true;
	}
	return temp;
}
/*
 * This function is used to check 
 * if there are items in the list
 */
template <class T>
bool CLinkedList<T>::getTail()
{
	bool temp = false;
	if (tail != NULL)
	{
		//set temp to true. This will be used
		//To determine if the list currently
		//Contains any elements
		temp = true;
	}
	return temp;
}

template <class T>
shared_ptr<typename CLinkedList<T>::Node>& CLinkedList<T>::getStorage()
{
	return storage;
}
//function resets iterators to proper positions after use
template <class T>
void CLinkedList<T>::resetIterators()
{
	iterFirst = head;
	iterLast = tail;
}
/*
* The following function will insert a new node
* into the back of the current list. It does so by first checking
* if the list contains anything.
*/
template <class T>
void CLinkedList<T>::insertLast(T addData)
{
	//Create new node 
	shared_ptr<Node> nodeLast(new Node);
	//Add data
	nodeLast->data = addData;
	//Point next to null
	nodeLast->prev = NULL;
	//conditional on head not pointing to anything 
	if (head == NULL && tail == NULL)
	{
		
		//set head and tail
		head = nodeLast;
		tail = nodeLast;
		//set the pointer associated with the tail struct to null
		tail->prev = NULL;
	}
	//If head points to anything else
	else
	{

		//set the pointer associated with the tail struct to the new node pointer
		nodeLast->next = tail;
		tail->prev = nodeLast;
		//move tail to be the new pointer
		tail = nodeLast;
		//set pointer in til to null
		tail->prev = NULL;
	}
	resetIterators();
}
/*
 * The following function will insert a new node 
 * into the front of the current list. It does so by first checking 
 * if the list contains anything. 
 */
template <class T>
void CLinkedList<T>::insertFirst(T addData)
{
	//Create new node 
	shared_ptr<Node> nodeFirst(new Node);
	//Add data
	nodeFirst->data = addData;
	//Point next to null
	nodeFirst->next = NULL;
	//conditional on head not pointing to anything 
	if (head == NULL && tail == NULL)
	{
		//set head and tail
		head = nodeFirst;
		tail = nodeFirst;
		//set the pointer associated with the tail struct to null
		head->next = NULL;
	}
	//If head points to anything else
	else
	{

		//set the pointer associated with the tail struct to the new node pointer
		nodeFirst->prev = head;
		head->next = nodeFirst;
		//move tail to be the new pointer
		head = nodeFirst;
		//set pointer in til to null
		head->next = NULL;
	}
	resetIterators();
}
/*
 * The following function will take an arguement
 * and iterate through the current list, comparing
 * the agruement to each node's data. If a match 
 * is found, the function directs the adjacent nodes
 * to point at each other, cutting out the 
 * current node for garbage collection.
 */
template <class T>
void CLinkedList<T>::remove(T addData)
{
	//local variables
	T searchKey = addData;
	shared_ptr<Node> tempStorage = NULL;
	//Do this loop until it reaches the list end
	while (iterFirst != NULL)
	{
		//Conditional on a match
		if (searchKey == iterFirst->data)
		{
			//Assign temp to the current node
			tempStorage = iterFirst;
			//move the iterator
			iterFirst = iterFirst->prev;
			//Check if list is now empty
			if (tempStorage->prev == NULL && tempStorage->next == NULL)
			{
				head = NULL;
				tail = NULL;
			}
			else
			{
				//Conditional upon the first item matching
				if (tempStorage->next == NULL)
				{
					//Move the head sentinal and surrender the previous node 
					head = head->prev;
					tail->next = NULL;
				}
				//Conditional upon the last item matching
				else if (tempStorage->prev == NULL)
				{
					//Move the tail sentinal and surrender the previous node 
					tail = tail->next;
					tail->prev = NULL;
				}
				//If the match occures anywhere else in the list
				else
				{
					//point the pointers of the nodes around the temporary node
					//so that the next and previous nodes in the list are both 
					//directly linked
					tempStorage->prev->next = tempStorage->next;
					tempStorage->next->prev = tempStorage->prev;

				}
			}
			//Surrender the temp node to garbage collection
			tempStorage = NULL;
			
		}
		//If there are no matches
		else
		{
			//move the iterator to the next node being evaluated
			iterFirst = iterFirst->prev;
		}
		
	}

	//As always, reassign iterators for use
	resetIterators();
}

/*
 *The following function will iterate through the list
 *from both ends simultaneously, stopping when both
 *iterators have reached each other's current position
 *As it runs, it releases memory, destroying the nodes 
 *in the process by setting them to point to NULL as it passes them
 */
template <class T>
void CLinkedList<T>::clearList()
{
	
	//conditional on head being null
	if (tail == NULL && head == NULL)
	{
		cout << "empty list\n";
	}
	else
	{
		while (iterLast != NULL && iterFirst != NULL && head->prev != NULL && tail->next != NULL)
		{
			//Test output
			//cout << iterFirst->data << " " << iterLast->data << endl;
			//move head to next element
			tail = tail->next;
			head = head->prev;
			iterLast = tail;
			iterFirst = head;	
			head->next = NULL;
			tail->prev = NULL;
		}
		//free memeory being held by sentinals
		head = NULL;
		tail = NULL;
	}
}
/*
*The following function will iterate through the list
*searching for a maximum value. Once completed, it will
*return that value and reset the iterators
*/
template <class T>
T CLinkedList<T>::maxVal()
{
	//Redundancy check against empty list
	if (tail == NULL && head == NULL)
	{
		//if both sentinal nodes are null//return a null value
		//This scope should never be entered as the problem is solved elsewhere 
		T kill = NULL;
		return kill;
	}
	//After null check assign data to temporary variables for storage and comparison 
	T tailIterData = iterLast->data;
	//while current position for both pointers is not null and the pointers haven't passed each other 
	while (iterLast != NULL)
	{
		//cout << iterFirst << " " << iterLast << endl;
		//compare value associated with pointer to value of temp
		if (iterLast->data >= tailIterData)
		{
			//if comparison is true then temp will assume a new value
			tailIterData = iterLast->data;
		}
		else {
		}
		//move current position of both pointers one closer to each other 
		iterLast = iterLast->next;
	}
	//Reassign iterators to their starting position
	resetIterators();
	//Return the minimum value
	return tailIterData;
}
/*
 *The following function will iterate through the list 
 *searching for a minimum value. Once completed, it will 
 *return that value and reset the iterators  
 */
template <class T>
T CLinkedList<T>::minVal()
{
	
	//Redundancy check against empty list
	if (tail == NULL && head == NULL)
	{
		//if both sentinal nodes are null//return a null value
		//This loop should never be entered as the problem is solved elsewhere 
		T kill = NULL;
		return kill;
	}
	//After null check assign data to temporary variables for storage and comparison 
	T tailIterData = iterLast->data;
	//while current position for both pointers is not null and the pointers haven't passed each other 
	while (iterLast != NULL)
	{
		//compare value associated with pointer to value of the data 
		if (iterLast->data <= tailIterData)
		{
			//if comparison is true then the stored data will assume a new value
			tailIterData = iterLast->data;
		}
		else {
		}
		iterLast = iterLast->next;
	}
	//Reassign iterators to their starting position
	resetIterators();
	//Return the minimum value
	return tailIterData;

}
/*
 * The following function will search through the current list
 * comparing user input to the stored data. When a match is found
 * the function returns the memory address of the first matching node
 */
template <class T>
shared_ptr<typename CLinkedList<T>::Node>& CLinkedList<T>::findAddress(T searchKey)
{
	//Iterate throught list, find nodes whose data is equal to
	//the function parameter, return those pointers
	shared_ptr<Node> tempStorage(new Node);
	tempStorage->data = searchKey;
	while (iterFirst != NULL)
	{
		//Conditional on a match
		if (tempStorage->data == iterFirst->data)
		{
			//Assign temp to the current node
			tempStorage = iterFirst;
			//move the iterator
			iterFirst = iterFirst->prev;
			//Conditional upon the first item matching
			cout << "The value you entered exists at address: " << tempStorage << endl;
			//set the storage pointer for further use
			storage = tempStorage;
			resetIterators();
			//Return the first instance of this data
			return storage;
		}
		//If there are no matches
		else
		{
			//move the iterator to the next node being evaluated
			iterFirst = iterFirst->prev;
		}
		//iterLast = iterLast->next;
	}
	//As always, reassign iterators for use
	resetIterators();
	return tempStorage;
}
/*
 * The following function takes a pointer to a memory address and compares it 
 * to the addresses of the current list's nodes. If a match is found, the 
 * function directs the adjacent nodes to point at each other, cutting out the 
 * current node for garbage collection.
 */
template <class T>
void CLinkedList<T>::delByAddress(shared_ptr<Node>& nodeKey)
{
	//iterate through list, if nodeKey == current position, remove current node
	//local variables
	//Do this loop until it reaches the list end
	while (iterFirst != NULL)
	{
		//Conditional on a match
		if (nodeKey == iterFirst)
		{
			//Assign temp to the current node
			nodeKey = iterFirst;
			//move the iterator
			iterFirst = iterFirst->prev;
			//Conditional upon the first item matching
			if (nodeKey->next == NULL)
			{
				//Move the head sentinal and surrender the previous node 
				head = head->prev;
				head->next = NULL;
			}
			//Conditional upon the last item matching
			else if (nodeKey->prev == NULL)
			{
				//Move the tail sentinal and surrender the previous node 
				tail = tail->next;
				tail->prev = NULL;
			}
			//If the match occures anywhere else in the list
			else
			{
				//point the pointers of the nodes around the temporary node
				//so that the next and previous nodes in the list are both 
				//directly linked
				nodeKey->prev->next = nodeKey->next;
				nodeKey->next->prev = nodeKey->prev;

			}
			//Surrender the temp node to garbage collection
			nodeKey = NULL;
		}
		//If there are no matches
		else
		{
			//move the iterator to the next node being evaluated
			iterFirst = iterFirst->prev;
		}
	}
	//As always, reassign iterators for additional use
	storage = NULL;
	resetIterators();
}
//Function will return first piece of data in list
template <class T>
T CLinkedList<T>::front()
{
	//Copy data from head to temp
	T temp = head->data;
	//return temp
	return temp;
}
//Function will return last piece of data in list
template <class T>
T CLinkedList<T>::back()
{
	//Copy data from head to temp
	T temp = tail->data;
	//return temp
	return temp;
}
//function will return size of list
template <class T>
int CLinkedList<T>::size()
{
	int total = 0;
	//start at tail
	//shared_ptr<Node> iterLast = tail;
	iterLast = tail;
	//while current position is not null
	while (iterLast != NULL)
	{
		
		total ++;
		//move current position
		iterLast = iterLast->next;
	}
	//Reassign iterators to their starting position
	resetIterators();
	return total;
} 