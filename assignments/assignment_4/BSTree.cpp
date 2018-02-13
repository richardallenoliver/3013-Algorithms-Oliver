//Richard Oliver
//Assignment 2: Binary Search Tree

//This .cpp file has the definition for all the member functions listed
//in the .h file


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "BSTree.h"

//http://www.webgraphviz.com/

using namespace std;

//purpose: counts the total number of nodes in the tree
int BSTree::count(node *root)
	{
		if (!root)
		{
			return 0;
		}
		else
		{
			return 1 + count(root->left) + count(root->right);
		}
	}

//purpose: inserts a node in the tree in it's correct position
void BSTree::insert(node *&root, node *&temp)
	{
		if (!root)
		{
			root = temp;
		}
		else
		{
			if (temp->data < root->data)
			{
				insert(root->left, temp);
			}
			else
			{
				insert(root->right, temp);
			}
		}
	}


void BSTree::print_node(node *n, string label)
	{
		if (label != "")
		{
			cout << "[" << label << "]";
		}
		cout << "[[" << n << "][" << n->data << "]]\n";
		if (n->left)
		{
			cout << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
		}
		else
		{
			cout << "\t\\-->[L][null]\n";
		}
		if (n->right)
		{
			cout << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
		}
		else
		{
			cout << "\t\\-->[R][null]\n";
		}
	}

	/**
	* type = ['predecessor','successor']
	*/

//returns a pointer the smallest node in the right of the subtree, if not 
	//present returns a pointer to the largest node in the left of the 
	//subtree
BSTree::node* BSTree::minValueNode(node *root)
	{
		node *current = root;

		if (root->right)
		{
			current = root->right;
			while (current->left != NULL)
			{
				current = current->left;
			}
		}
		else if (root->left)
		{
			current = root->left;
			while (current->right != NULL)
			{
				current = current->right;
			}
		}
		return current;
	}

//purpose: deletes selected node from tree
BSTree::node *BSTree::deleteNode(node *&root, int key)
{
	if (!root)
	{
		return NULL;
	}

	//if root is being deleted
	if (key == root->data)
	{
		//if right part of tree is empty
		//left child becomes the new root
		if (root->right == NULL)
		{
			node *temp = root;
			root = root->left;
			delete temp;
			return root;
		}   
		//if left part of tree is empty
		//right child becomes the new root
		else if (root->left == NULL)
		{
			node *temp = root;
			root = root->right;
			delete temp;
			return root;
		}
		//return root;
	}

	//find key in left side of tree
	if (key < root->data)
	{
		cout << "going left" << endl;
		root->left = deleteNode(root->left, key);
	}
	//find key in right side of tree
	else if (key > root->data)
	{
		cout << "going right" << endl;
		root->right = deleteNode(root->right, key);
	}
	else
	{
		//node with one child on right of tree
		if (root->left == NULL)
		{
			node *temp = root->right;
			delete root;
			return temp;
		}
		//node with one child on left of tree
		else if (root->right == NULL)
		{
			node *temp = root->left;
			delete root;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		node *temp = minValueNode(root);

		print_node(temp, "minvaluenode");

		// Copy the inorder successor's content to this node
		root->data = temp->data;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->data);
	}
	return root;
}

//purpose: gives the height of the tree
int BSTree::height(node *root)
	{
		if (!root)
		{
			return 0;
		}
		else
		{
			int left = height(root->left);
			int right = height(root->right);
			if (left > right)
			{
				return left + 1;
			}
			else
			{
				return right + 1;
			}
		}
	}

//print nodes at a given level
void BSTree::printGivenLevel(node *root, int level)
	{
		if (root == NULL)
			return;
		if (level == 1)
		{
			print_node(root);
		}
		else if (level > 1)
		{
			printGivenLevel(root->left, level - 1);
			printGivenLevel(root->right, level - 1);
		}
	}

	//************************************************************************
	// Method to help create GraphViz code so the expression tree can
	// be visualized. This method prints out all the unique node id's
	// by traversing the tree.
	// Recivies a node pointer to root and performs a simple recursive
	// tree traversal.
	//************************************************************************
void BSTree::GraphVizGetIds(node *nodePtr, ofstream &VizOut)
	{
		static int NullCount = 0;
		if (nodePtr)
		{
			GraphVizGetIds(nodePtr->left, VizOut);
			VizOut << "node" << nodePtr->data
				<< "[label=\"" << nodePtr->data << "\\n"
				//<<"Add:"<<nodePtr<<"\\n"
				//<<"Par:"<<nodePtr->parent<<"\\n"
				//<<"Rt:"<<nodePtr->right<<"\\n"
				//<<"Lt:"<<nodePtr->left<<"\\n"
				<< "\"]" << endl;
			if (!nodePtr->left)
			{
				NullCount++;
				VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
			}
			GraphVizGetIds(nodePtr->right, VizOut);
			if (!nodePtr->right)
			{
				NullCount++;
				VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
			}
		}
	}

	//************************************************************************
	// This method is partnered with the above method, but on this pass it
	// writes out the actual data from each node.
	// Don't worry about what this method and the above method do, just
	// use the output as your told:)
	//************************************************************************
void BSTree::GraphVizMakeConnections(node *nodePtr, ofstream &VizOut)
	{
		static int NullCount = 0;
		if (nodePtr)
		{
			GraphVizMakeConnections(nodePtr->left, VizOut);
			if (nodePtr->left)
				VizOut << "node" << nodePtr->data << "->"
				<< "node" << nodePtr->left->data << endl;
			else
			{
				NullCount++;
				VizOut << "node" << nodePtr->data << "->"
					<< "nnode" << NullCount << endl;
			}

			if (nodePtr->right)
				VizOut << "node" << nodePtr->data << "->"
				<< "node" << nodePtr->right->data << endl;
			else
			{
				NullCount++;
				VizOut << "node" << nodePtr->data << "->"
					<< "nnode" << NullCount << endl;
			}

			GraphVizMakeConnections(nodePtr->right, VizOut);
		}
	}

//default constructor
BSTree::BSTree()
	{
		root = NULL;
	}

//destructor
BSTree::~BSTree()
	{
	}

//calls the private count function to get the number of nodes in the tree
int BSTree::count()
	{
		return count(root);
	}

//public insert function that calls private insert function
void BSTree::insert(int x)
	{
		node *temp = new node(x);
		insert(root, temp);
	}

//pulic deletenode function that calls private deletenode function
void BSTree::deleteNode(int key)
	{
		deleteNode(root, key);
	}

//public minValue function that calls private minvaluenode function
void BSTree::minValue()
	{
		print_node(minValueNode(root), "minVal");
	}


//public height function that calls the private height function
int BSTree::height(int key)// = -1)
	{
		if (key > 0)
		{
			//find node
		}
		else
		{
			return height(root);
		}
		return 0;
	}

//returns data in the root node if present 0 otherwise
int BSTree::top()
	{
		if (root)
			return root->data;
		else
			return 0;
	}

/* Function to line by line print level order traversal a tree*/
void BSTree::printLevelOrder()
	{
		cout << "Begin Level Order===================\n";
		int h = height(root);
		int i;
		for (i = 1; i <= h; i++)
		{
			printGivenLevel(root, i);
			cout << "\n";
		}
		cout << "End Level Order===================\n";
	}

	//************************************************************************
	// Recieves a filename to place the GraphViz data into.
	// It then calls the above two graphviz methods to create a data file
	// that can be used to visualize your expression tree.
	//************************************************************************
void BSTree::GraphVizOut(string filename)
	{
		ofstream VizOut;
		VizOut.open(filename);
		VizOut << "Digraph G {\n";
		GraphVizGetIds(root, VizOut);
		GraphVizMakeConnections(root, VizOut);
		VizOut << "}\n";
		VizOut.close();
	}


