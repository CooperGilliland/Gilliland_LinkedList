#include "linkedList.h"
#include "CProgram.h"
CProgram::CProgram()
{
}
CProgram::~CProgram()
{
}
void CProgram::Initialize()
{
	cout << "\t\t+#################################################+\n"; //Window Dressing
	cout << "\t\t+---------Programmer: Cooper Gilliland------------+\n";
	cout << "\t\t+-------------Project: Linked List----------------+\n";
	cout << "\t\t+---------------Date: 6/03/2017-------------------+\n";
	cout << "\t\t+#################################################+\n";
	PAUSE;
}
//Update function runs whenever Main loops 
void CProgram::Update(CLinkedList<int>& List)
{
	mainMenu(List);
}
void CProgram::Shutdown()
{
	cout << "Exiting Program" << endl;
}
//output function gives feedback to user
void CProgram::menuError()
{
	cout << "Your input is unsupported. Your current work will be saved, \nand you will be returned to the main menu." << endl;
}
//mutator function for private boolean
//passing false to this will ensure that
//The program goes into its exit sequence
void CProgram::setisRunning(bool b)
{
	isRunning = b;
}
//Accessor function for private boolean
//Used by main to determine if the program
//Should run for another loop
bool CProgram::getisRunning() 
{
	return isRunning;
}
/*
 * This function uses user input to
 * determine what action will be executed 
 * against the current list object
 */
void CProgram::mainMenu(CLinkedList<int>& List)
{
	//format menu 
	cin.clear();
	system("CLS");
	char input = ' ';
	cout << "Please select from the provided options: " << 
		"\n1. Add Data \n2. Find and/or Delete Node Addesses by Value. " << 
		"\n3. Locate the Minimum and Maximum Values. \n4. Remove Items \n5. List size. \n6. Run the auto test feature complete with a runtime analysis. \n7. Quit Program" << endl;
	//use input for switch statement 
	cin >> input;
	switch(input)
	{
	case '1':
		//add items menu
		addMenu(List);
		break;
	case '2':
		//Search through the list 
		findNode(List);
		break;
	case '3':
		//Check if list contains any elements
		if (List.getHead() == false && List.getTail() == false)
		{
			//Give user feedback and exit the menu function
			cout << "This list is empty." << endl;
		}
		//If list exists send user to next menu
		else
		{
			//min/max menu
			minMaxMenu(List);
		}
		break;
	case '4':
		//remove items
		deleteMenu(List);
		break;
	case '5':
		//output current list size
		cout << "Size: " << List.size() << endl;
		break;
	case '6':
		autoRun(List);
		break;
	case '7': 
		//exit program
		setisRunning(false);
		break;
	default:
		//Error message
		system("CLS");
		menuError();
		break;
	}
}
/*
 * This function provides the user with 
 * various input options related to the 
 * current list object
 */
void CProgram::addMenu(CLinkedList<int>& List)
{
	cin.clear();
	char input = ' ';
	cout << "Please select from the provided options: \n1. Auto generate 1000000 node list of random numbers."
		<< "\n2. Manually add a single number to the front of the current list. \n3. Manually add a single number to the back of the current list." << endl;
	//use input for switch statement 
	cin >> input;
	switch (input)
	{
	case '1':
		//mass add to list
		massInLast(List, 1000000);
		break;
	case '2':
		//add single item to front
		addFirst(List);
		break;
	case '3':
		//add single item to end
		addLast(List);
		break;
	default:
		//error message
		system("CLS");
		menuError();
		break;
	}
}
/*
 * This function will allow the user to display
 * the minimum and maximum values of the current 
 * list object
 */
void CProgram::minMaxMenu(CLinkedList<int>& List)
{
	cin.clear();
	char input = ' ';
	cout << "Please select from the provided options: " 
	<< "\n1. Find the minimum value. \n2. Find the Maximum value. \n3. Find min and max." << endl;
	//use input for switch statement 
	cin >> input;
	switch (input)
	{
	case '1':
		//find min
		cout << "Min: " << List.minVal() << endl;
		break;
	case '2':
		//find max
		cout << "Max: " << List.maxVal() << endl;
		break;
	case '3':
		//find both
		cout << "Minimum: " << List.minVal() << ", Maximum: " << List.maxVal() << endl;
		break;
	default:
		system("CLS");
		menuError();
		break;
	}
}
/*
 * This function provides the user with 
 * multiple options for deleting nodes 
 * from the current list object
 */
void CProgram::deleteMenu(CLinkedList<int>& List)
{
	cin.clear();
	char input = ' ';
	cout << "Please select from the provided options: \n1. Delete Items by Value. \n2. Clear entire List." << endl;
	cin >> input;
	switch (input)
	{
	case '1':
		deleteItem(List);
		break;
	case '2':
		List.clearList();
		break;
	default:
		system("CLS");
		menuError();
		break;
	}
}

void CProgram::findNode(CLinkedList<int>& List)
{
	cin.clear();
	int valueToBeFound;
	char switchIn = ' ';
	cout << "Enter Search Key: ";
	//collect input and hand it off to the list for a search function
	cin >> valueToBeFound;
	List.findAddress(valueToBeFound);
	cout << "Would you like to delete this node? \n1. Yes \n2. No" << endl;
	cin.clear();
	//use input for switch statement 
	cin >> switchIn;
	switch(switchIn)
	{
	case '1':
		//Delete the node currently stored in the lists temp storage item 
		List.delByAddress(List.getStorage());
		cout << "Node deleted." << endl;
		break;
	case '2':
		cout << "You have chosen to keep the selected node." << endl;
		PAUSE;
		break;
	default:
		system("CLS");
		menuError();
		break;
	}
	//clear input for next program loop 
	cin.clear();
	cin.ignore(1024, '\n');
}

void CProgram::addFirst(CLinkedList<int>& List)
{
	cin.clear();
	int addData;
	cout << "Please enter an integer now: ";
	//use user input to populate list 
	cin >> addData;
	List.insertFirst(addData);
}

void CProgram::addLast(CLinkedList<int>& List)
{
	cin.clear();
	int addData;
	cout << "Please enter an integer now: ";
	//use user input to populate list 
	cin >> addData;
	List.insertLast(addData);
}

/*
 * This function takes input from the user
 * and uses that value to remove all nodes 
 * associated with that value from the 
 * current list object.
 */
void CProgram::deleteItem(CLinkedList<int>& List)
{
	cin.clear();
	int itemToBeDeleted;
	cout << "Enter Item being removed" << endl;
	cin >> itemToBeDeleted;
	List.remove(itemToBeDeleted);
}
//mass input function for testing purposes 
void CProgram::massInLast(CLinkedList<int>& List, unsigned int total)
{
	for (unsigned int i = 0; i < total; i++)
	{
		List.insertLast(RAND(-10000, 10000)));
	}
}
//mass input function for testing purposes 
void CProgram::massInFirst(CLinkedList<int>& List, unsigned int total)
{
	for (unsigned int i = 0; i < total; i++)
	{
		List.insertFirst(i);
	}
}

void CProgram::autoRun(CLinkedList<int>& List)
{
	clock_t runTime = clock();
	cout << "Inserting to Front" << endl;
	runTime = clock();
	List.insertFirst(2);
	printRuntime(runTime);	
	cout << "Inserting to Back" << endl;
	runTime = clock();
	List.insertLast(1);
	printRuntime(runTime);
	cout << "Removing from Front." << endl;
	List.remove(2);
	cout << "Removing from Back." << endl;
	List.remove(1);
	cout << "Inserting 5 million Nodes of random value into the list" << endl;
	runTime = clock();
	massInLast(List, 5000000);
	printRuntime(runTime);
	if (List.getHead() == false && List.getTail() == false)
	{
		cout << "This list is empty" << endl;
	}
	else
	{
		runTime = clock();
		cout << "Max: " << List.maxVal() << endl;
	}
	printRuntime(runTime);
	if (List.getHead() == false && List.getTail() == false)
	{
		cout << "This list is empty" << endl;
	}
	else
	{
		runTime = clock();
		cout << "Min: " << List.minVal() << endl;
	}
	printRuntime(runTime);
	cout << "Current Size: " << List.size() << endl;
	printRuntime(runTime);
	cout << "Emptying List" << endl;
	List.clearList();
	printRuntime(runTime);
	cout << "Current Size: " << List.size() << endl;
	//isRunning = false;
}
//This function is only for testing runtime. See included lab report for additional information 
void CProgram::printRuntime(clock_t& runTime)
{
	runTime = clock() - runTime;
	printf("It took %d clicks (%f seconds).\n", runTime, ((float)runTime) / CLOCKS_PER_SEC);
	runTime = clock();
}