/*
 * Author: hasseo
 * COP3530 Project #3
 * Due Date: Friday March 15, 2013
 * ----
 * This project does some crazy stuff with XML and something about slime molds...
 * ----
 * node.cpp WAS CREATED IN VERSION 1.1.
 * node.cpp WAS LAST UPDATED IN VERSION 1.1.
 */

#include "node.h"

using namespace std;
 
 node::node(char* scientific_name, char* common_name, char* rank){
	this->scientific_name = scientific_name;
	this->common_name = common_name;
	this->rank = rank;
	this->parent = 0;
 }
 
 node::node(char* scientific_name, char* common_name, char* rank, node* parent){
	this->scientific_name = scientific_name;
	this->common_name = common_name;
	this->rank = rank;
	this->parent = parent;
 }
 

 void node::print(){
	cout << common_name << " (" << scientific_name << ", " << rank << ")" << endl;
}
