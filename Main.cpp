#include "linkedList.h"
#include "CProgram.h"
void main()
{
	srand(time(NULL));
	//instantiate and initialize program object
	CProgram program;
	program.Initialize();
	//Instantiate a new list object
	CLinkedList<int> newList;
	//Loop until user decides to exit
	while(program.getisRunning())
	{
		//run update function with a referene to the current list
		cin.clear();
		program.Update(newList);
		PAUSE;
	}
	system("CLS");
	program.Shutdown();
	PAUSE;
}