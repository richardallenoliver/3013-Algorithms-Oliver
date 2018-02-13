///////////////////////////////////////////////////////////////////////////////
//																		     //               
// Title:            Binary Search Tree										 //
// Files:            main.cpp, BSTree.h and BSTree.cpp						 //
// Semester:         Advanced Algorithm, Spring 2018						 //
//																			 //
// Author:           Richard Oliver											 //
// Email:            richardallenoliver@yahoo.com							 //
// Description:																 //
// This program allows the adding and removal of nodes from the binary		 //
// search tree and output codes that allow you to view a graphical			 //	
// representation of the modified tree.										 //
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "BSTree.h"

using namespace std;


int main()
{
	srand(2342); //random number seeding

	BSTree B; //creating an instance of the BSTree

	//inserting nodes into tree
	B.insert(38);
	B.insert(10);
	B.insert(29);
	B.insert(27);
	B.insert(5);
	B.insert(43);
	B.insert(36);
	B.insert(3);
	//B.insert(40);
	//B.insert(45);
	B.printLevelOrder();

	//function call to generate code for the BSTree before deletion
		//code send to text file
	B.GraphVizOut("before.txt");

	//deleting nodes from the tree
	B.deleteNode(38);

	//B.deleteNode(43);
	//B.deleteNode(29);
	//B.deleteNode(27);
	//B.deleteNode(10);
	B.printLevelOrder();

	//function call to generate code for the BSTree after deletion
		//code send to text file
	B.GraphVizOut("after.txt");

	// Continously delete root node, until tree is empty
	while (B.top())
	{
		cout << "removing: " << B.top() << endl;
		B.deleteNode(B.top());		
	}	

	cout << endl;
	system("pause");
	return 0;
}