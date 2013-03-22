/*
 * Author: hasseo
 * COP3530 Project #3
 * Due Date: Friday March 15, 2013
 * ----
 * This project does some crazy stuff with XML and something about slime molds...
 * ----
 * tree.h WAS CREATED IN VERSION 1.1.
 * tree.h WAS LAST UPDATED IN VERSION 1.1.
 */

#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <vector>
#include <stack>


using namespace std;

class tree{
public:
	tree(node* root);
	node* search(const char* searchTerm);
	void addNode(node* node);
	node* root;
	vector<node* > nodeVector;

private:

};

#endif
