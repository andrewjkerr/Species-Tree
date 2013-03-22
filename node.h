/*
 * Author: hasseo
 * COP3530 Project #3
 * Due Date: Friday March 15, 2013
 * ----
 * This project does some crazy stuff with XML and something about slime molds...
 * ----
 * node.h WAS CREATED IN VERSION 1.1.
 * node.h WAS LAST UPDATED IN VERSION 1.1.
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"

using namespace std;

class node{
public:
	node(char* scientific_name, char* common_name, char* rank);
	node(char* scientific_name, char* common_name, char* rank, node* parent);
	void print();
	node* getParent() {return parent;}
	char* scientific_name;
	char* common_name;
	char* rank;
	node* parent;

private:
	int whatever;
};

#endif
