//Richard Oliver
//Assignment 2: Binary Search Tree

//This .h file has the node structure, constructors and delcarations for the
//member functions

#pragma once

using namespace std;

class BSTree
{
private:
	struct node //node structure
	{
		int data;
		node *left;
		node *right;

		node() //default constructor
		{
			data = -1;
			left = NULL;
			right = NULL;
		}

		node(int x) //perimeterized constructor
		{
			data = x;
			left = NULL;
			right = NULL;
		}		
	};

	//declaration of the root pointer that will be used throughout the program
	node *root;

	//purpose: counts the total number of nodes in the tree
	//requires: root pointer
	//returns: integer value for total number of nodes in tree
	int count(node *root);

	//purpose: inserts a node in the tree at it's correct position
	//requires: root and temp pointers
	//returns: does not return a value
	void insert(node *&root, node *&temp);

	void print_node(node *n, string label = "");

	//purpose: //returns a pointer to the smallest node in the right of the  
				//subtree, if not present returns a pointer to the largest  
				//node in the left of the subtree.
	//requires: root pointer
	//returns: pointer to smallest node in left or largest in right of tree
	node *minValueNode(node *root);

	//purpose: deletes selected node from tree
	//requires: root pointer and the key to be deleted
	//returns: pointer to root 
	node *deleteNode(node *&root, int key);

	//purpose: gives the height of the tree
	//requires: root pointer
	//returns: integer value for height of the tree
	int height(node *root);

	//purpose: print nodes at a given level
	//requires: root pointer and level to be printed
	//returns: does not return a value but prints the nodes at a given level
	void printGivenLevel(node *root, int level);

	//purpose: this method prints out all the unique node id's by traversing 
		//the tree.
	//requires: node pointer and outfile
	//returns: does not return a value
	void GraphVizGetIds(node *nodePtr, ofstream &VizOut);

	//purpose: works with GraphVizGetIds and it writes out the actual data from each node.
	//requires: node pointer and outfile
	//returns: does not return a value
	void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut);

public:
	BSTree(); //default constructor
	~BSTree(); //destructor

	//purpose: calls the private count function to get the number of nodes in the tree
	//requires: does not require any variable
	//returns: returns the number of nodes in the tree
	int count();

	//purpose: calls the private insert function to insert a node into the tree
	//requires: value for the node to be inserted into the tree
	//returns: does not return a value
	void insert(int x);

	//purpose: calls the priveate delete node function to remove a node from  
				//the tree
	//requires: key for node to be deleted
	//returns: does not return a value
	void deleteNode(int key);

	//purpose: calls the private minvalue function to get the smallerst value 
				//in right subtree or largest value in left subtree
	//requires: does not require a variable
	//returns: does not return a value
	void minValue();

	//purpose: public height function that calls the private height function
	//requires: key value
	//returns: integer value for the height of three
	int height(int key = -1);

	//purpose: returns data in the root node if present 0 otherwise
	//requires: does not require a variable
	//returns: returns data in the root node if present 0 otherwise
	int top();

	//purpose: function to line by line print level order traversal a tree
	//requires: does not require a variable
	//returns: does not return a value but print level order traversal a tree
	void printLevelOrder();

	//purpose: creates a data file that can be used to visualize your expression tree
	//requires: outputfile
	//returns: does not return a value creates a data file that can be used to visualize your expression tree
	void GraphVizOut(string filename);
};
