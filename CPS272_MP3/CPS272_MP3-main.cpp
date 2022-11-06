#include "LinkedList.h"

//This program creates several linked list objects, sorts them, prints them to the console, then creates a third list and merges the first two into it, omitting nodes that share values. It then prints the final list, prints the sum of all 
//the numbers within its nodes, and the average of all of those numbers.
//Written by Logan Skura, 11/4/2022

int main()
{
	LinkedList list1;
	LinkedList list2;
	
	for (int i = 0; i < 20; i++)
	{
		list1.InsertNode(i);
	}
	for (int i = 0; i < 15; i++)
	{
		list2.InsertNode(i);
	}
	
	list1.Sort();
	list2.Sort();
	
	list1.PrintList();
	list2.PrintList();

	LinkedList merged;

	merged.MergeAndSort(list1, list2);
	merged.PrintList();
	std::cout << "Sum of numbers in final list is: " << merged.Sum() << std::endl << "Average of numbers in final list is: " << merged.Average() << std::endl;
}