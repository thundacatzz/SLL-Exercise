#include "LinkedList.h"

//Default constructor for linked list objects. Sets head to NULL and length to 0.
LinkedList::LinkedList()
{
	head = NULL;
	length = 0;
}

//Creates new node containing a random int value between 1 and 100. Inserts it at the tail of the linked list object that is calling the method.
void LinkedList::InsertNode(int ind)
{
	//Creating the new node and initializing its values.
	node* newNode = new node;
	newNode->index = ind;
	newNode->number = (rand() % 100) + 1;
	newNode->next = NULL;

	length++; //Increments the length of the calling object.
	
	//If there is no head, make this new node the head.
	if (head == NULL)
	{
		
		head = newNode;
		return;
	}

	//If there is a head, traverse to the end of the list, then add the new node on to the end.
	if (head != NULL)
	{
		node* temp = head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = newNode;
	}
}

//This method is almost identical to the one above, but it updates the old index of the node to the index it should be within the newly sorted list.
void LinkedList::SortedInsert(int ind, int num)
{
	node* newNode = new node;
	newNode->index = ind;
	newNode->number = num;
	newNode->next = NULL;
	int newIndex = 0;
	length++;

	if (head == NULL)
	{
		newNode->index = newIndex;
		head = newNode;
		return;
	}
	if (head != NULL)
	{
		node* temp = head;

		while (temp->next != NULL)
		{
			temp = temp->next;
			newIndex++;
		}

		newNode->index = newIndex + 1;
		temp->next = newNode;
	}
}

//Deletes a node from the calling object based on its "index" within the list. This is not the index value assigned to the node when it is created, but its actual position in the list.
void LinkedList::DeleteNode(int deleteIndex)
{
	//These variables are used to traverse the list.
	node* temp = head;
	node* prev = head;
	int listLength = 0;

	//The function will not delete anything if the list is already empty.
	if (head == NULL)
	{
		std::cout << "List empty. Nothing to delete.";
		return;
	}

	//Traverse the list and figures out how long it is.
	while (temp->next != NULL)
	{
		listLength++;
		temp = temp->next;
	}
	
	//If the length of the list doesn't contain the index the user wants to delete, it will output an error message and return.
	if (listLength < deleteIndex)
	{
		std::cout << "No node at Index " << deleteIndex << std::endl;
		return;
	}

	temp = head;// Brings the temp pointer back to the head of the list.

	//Block for deleting the head of the list.
	if (deleteIndex == 0)
	{
		head = head->next;
		delete temp;
		length--;
		return;
	}

	//Block for deleting any node other than the head. Traverses the list then, when it finds the node to be deleted, points the previous node to the next node and deletes the current node.
	for (int i = 0; i <= deleteIndex; i++)
	{
		if (i == deleteIndex)
		{
			prev->next = temp->next;
			delete temp;
			length--;
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

//Prints the numbers of the nodes in the linked list.
void LinkedList::PrintList()
{
	//Won't print anything if list is empty.
	if (head == NULL)
	{
		std::cout << "List empty. Nothing to print.";
		return;
	}
	else
	{
		//Traverses the list and prints the number contained within each node. At the end it will also print the length of the list.
		node* temp = head;
		while (temp->next != NULL)
		{
			std::cout << temp->number << ", ";
			temp = temp->next;
		}
	
		std::cout << temp->number << std::endl << "Number of nodes: " << length << std::endl << std::endl;
	}
}

//Method to sort the calling object. Also omits nodes that contain duplicate values.
void LinkedList::Sort()
{
	node* temp = head;
	
	if (head == NULL)
	{
		std::cout << "List empty. Nothing to sort.";
		return;
	}

	else
	{
		//Create a new list to store the sorted nodes.
		LinkedList sorted;

		//This pointer and these variables will track which of the nodes within the list being sorted contain the smallest value. The lastSmallest variable will track the previous smallest object inserted into the sorted list.
		node* smallestPtr = NULL;
		int smallestNum = 101;// Initialized to a number that is larger than any of the numbers within the nodes will be.
		int lastSmallest = 0;// Initialized to a number that is smaller than any of the numbers within the nodes will be.
	
		bool unsorted = true;//Boolean that will track whether the list is completely sorted.
		while (unsorted)
		{
			unsorted = false;//If the loop completes without any smaller numbers than the last number being detected, it will exit the loop.
			
			//Traverse the list, checking the number within each node to see if it is smaller than the last smallest number detected. If the number is smaller, set that to the new smallest number and set a temporary pointer to point
			//to that node. Also sets unsorted to true so it will loop again.
			while (temp->next != NULL)
			{
				if (temp->number < smallestNum && temp->number > lastSmallest)
				{
					smallestNum = temp->number;
					smallestPtr = temp;
					unsorted = true;
				}
				temp = temp->next;
			}

			//Check the last node of the list.
			if (temp->number < smallestNum && temp->number > lastSmallest)
			{
				smallestNum = temp->number;
				smallestPtr = temp;
				unsorted = true;
			}
			
			//If unsorted has been set to true, that is, a new smallest number found, then set the lastSmallest to that number so it will not be retrieved again. Then insert the node containing that number into the sorted list object
			//and assign it the proper index via the SortedInsert method. Reset the temp pointer to the head of the list to be sorted and smallestNum to a number larger than is contained within the list.
			if (unsorted)
			{
				lastSmallest = smallestPtr->number;

				sorted.SortedInsert(smallestPtr->index, smallestPtr->number);

				temp = head;
				smallestNum = 101;
			}
		}
		//After all the nodes are sure to have been sorted, point the head of the calling list to the head of the sorted list, returning a completely sorted list.
		head = sorted.head;
	}
}

//This method effectively functions the same as sort, but takes two lists as arguments and traverses both of them, sorting through them and inserting nodes into the calling object instead of a local sorted list object.
//Also omits nodes that contain duplicate values.
void LinkedList::MergeAndSort(LinkedList one, LinkedList two)
{
	node* temp1 = one.head;
	node* temp2 = two.head;
	node* smallestPtr = NULL;

	int smallestNum = 101;
	int lastSmallest = 0;

	bool unmerged = true;
	while (unmerged)
	{
		unmerged = false;

		//Checking first list
		while (temp1->next != NULL)
		{
			if (temp1->number < smallestNum && temp1->number > lastSmallest)
			{
				smallestNum = temp1->number;
				smallestPtr = temp1;
				unmerged = true;
			}
			temp1 = temp1->next;
		}
		if (temp1->number < smallestNum && temp1->number > lastSmallest)
		{
			smallestNum = temp1->number;
			smallestPtr = temp1;
			unmerged = true;
		}
		
		//Checking second list
		while (temp2->next != NULL)
		{
			if (temp2->number < smallestNum && temp2->number > lastSmallest)
			{
				smallestNum = temp2->number;
				smallestPtr = temp2;
				unmerged = true;
			}
			temp2 = temp2->next;
		}
		if (temp2->number < smallestNum && temp2->number > lastSmallest)
		{
			smallestNum = temp2->number;
			smallestPtr = temp2;
			unmerged = true;
		}

		//Adding node to merged list
		if (unmerged)
		{
			lastSmallest = smallestPtr->number;

			this->SortedInsert(smallestPtr->index, smallestPtr->number);

			temp1 = one.head;
			temp2 = two.head;
			smallestNum = 101;
		}
	
	head = this->head;

	}
}

//Sums all the numbers within the nodes of the calling list, then returns the sum.
int LinkedList::Sum()
{
	node* temp = head;
	int sum = 0;
	
	while (temp->next != NULL)
	{
		sum += temp->number;
		temp = temp->next;
	}
	sum += temp->number;

	return sum;
}

//Sums all the numbers within the nodes of the calling list, then returns the average of those numbers.
float LinkedList::Average()
{
	node* temp = head;
	float average = 0;

	while (temp->next != NULL)
	{
		average += temp->number;
		temp = temp->next;
	}
	average += temp->number;
	average /= length;

	return average;
}