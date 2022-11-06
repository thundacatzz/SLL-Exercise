#pragma once
#include <iostream>;

class LinkedList
{
	struct node
	{
		int number;
		int index;
		node* next;
	};
	node* head;
	int length;
public:
	LinkedList();
	void InsertNode(int);
	void SortedInsert(int, int);
	void DeleteNode(int);
	void PrintList();
	void Sort();
	void MergeAndSort(LinkedList, LinkedList);
	int Sum();
	float Average();
};

