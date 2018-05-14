//Preprocessor directives 
#pragma once
#include "linkedList.h"
#include "PreprocessorManager.h"
//This class serves as a user interface for the linked list class
//Any information for the list has to pass through here 
class CProgram
{
public:
	CProgram();
	~CProgram();
	void Initialize();
	void Update(CLinkedList<int>& List);
	void Shutdown();
	static void menuError();
	void printRuntime(clock_t& rt);
	void setisRunning(bool b);
	bool getisRunning();
	void mainMenu(CLinkedList<int>& List);
	void addMenu(CLinkedList<int>& List);
	void minMaxMenu(CLinkedList<int>& List);
	void deleteMenu(CLinkedList<int>& List);
	void findNode(CLinkedList<int>& List);
	void addFirst(CLinkedList<int>& List);
	void addLast(CLinkedList<int>& List);
	void deleteItem(CLinkedList<int>& List);
	void massInLast(CLinkedList<int>& List, unsigned int total);
	void massInFirst(CLinkedList<int>& List, unsigned int total);
	void autoRun(CLinkedList<int>& List);

private:
	bool isRunning = true;
};