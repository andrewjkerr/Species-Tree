/*
 * Author: hasseo
 * COP3530 Project #3
 * Due Date: Friday March 15, 2013
 * ----
 * This project does some crazy stuff with XML and something about slime molds...
 * ----
 * main.cpp WAS CREATED IN VERSION 1.0.
 * main.cpp WAS LAST UPDATED IN VERSION 2.0.
 */

#include "node.h"
#include "tree.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "rapidxml.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;
using namespace rapidxml;

// Parses the tree into a tree
tree* parseTree(xml_node<>* root_node){

	// Creates the root node
	node* root = new node("ROOT", "ROOT", "ROOT");
	
	// Creates a new tree
	tree* speciesTree = new tree(root);
	
	xml_node<>* next_node = root_node->first_node();

	// Creates a stack of parent nodes. Allows for fifo!
	stack<node* > parentNodes;
	
	// Push the root node so that it's actually the root!
	parentNodes.push(root);

	// Let's parse this suckah!
	while(next_node){

		xml_node<>* node1;
		
		// Checks whether the node is a <taxonomy> node (since that's the only node that has information in it.
		if(next_node->first_node("taxonomy") != 0){

			// Sets the node to the "taxonomy" node.
			next_node = next_node->first_node("taxonomy");
			
			// Set the char*s to a space in case there isn't one of them in the xml_node
			char* scientific_name = " ";
			char* common_name = " ";
			char* rank = " ";
			
			// Grab the values from the nodes
			if(next_node->first_node("scientific_name") != 0){
				node1 = next_node->first_node("scientific_name");
				scientific_name = node1->value();
			}
			if(next_node->first_node("rank") != 0){
				node1 = next_node->first_node("rank");
				rank = node1->value();
			}
			if(next_node->first_node("common_name") != 0){
				node1 = next_node->first_node("common_name");
				common_name = node1->value();
			}
			
			// Makes the current node
			node* currNode = new node(scientific_name, common_name, rank, parentNodes.top());

			// Let's add the node to the tree vector!
			speciesTree->addNode(currNode);

			// And now let's add the node to the parentNodes
			parentNodes.push(currNode);

			// Checks if it needs to go back to parent
			while(next_node->next_sibling() == 0){
				if(next_node == root_node){
					break;
				}

				next_node = next_node->parent();

				// Pops the node when parent() is called since it's obviously not a parent
				if(parentNodes.size() > 1 && parentNodes.top() != root && next_node->first_node("taxonomy") != 0){
					parentNodes.pop();
				}
			}

			next_node = next_node->next_sibling();
		}
		
		// If it's not a clade node nor a taxonomy node let's keep going!
		// Nothing to do with the tree/nodes, just keeping the parsing running
		else if(next_node->first_node("clade") == 0){

			// Check whether it needs to go to the parent or not
			while(next_node->next_sibling() == 0){
				if(next_node == root_node){
					break;
				}
				next_node = next_node->parent();
			}
			next_node = next_node->next_sibling();
		}

		// If it's a clade node, move to the next node
		else{
			next_node = next_node->first_node();
		}
	}
	
	// Return dat tree!
	return speciesTree;
}

// This gets the lineage of a species that is passed in via the const char* searchParameter
void searchTree(tree* speciesTree, const char* searchParameter){

	// Searches the tree for the node that matches the parameters
	node* foundNode = speciesTree->search(searchParameter);

	node* currNode = foundNode;

	// i is just for keeping track of the ">>"s that print out
	int i = 0;
	while(currNode){

		// Print out an appropriate amount of ">"s
		for(int j = 0; j < i; j++){
			cout << ">>";
		}
		cout << " ";
		currNode->print();

		// Get the parent node
		currNode = currNode->getParent();
		i++;
	}
}

// This finds the common lineage of two species
void findCommon(tree* speciesTree, const char* search1, const char* search2){

	// Searches the tree for the nodes that match the species passed in
	node* foundNode1 = speciesTree->search(search1);
	node* foundNode2 = speciesTree->search(search2);

	// Creates the stack that will be used for searching
	/*
	 * Q - 	Why use a stack?
	 *
	 * A - 	Well, since it goes from node->parents, it's in an incorrect format for finding the common lineage.
	 *		Using a stack allows it to fill up node first, then it's parents so that the parents can be accessed first.
	 */
	stack<node* > searchStack1;
	stack<node* > searchStack2;

	// Goes through each node and fills up the stack so that the root node is the first one!
	while(foundNode1){
		searchStack1.push(foundNode1);
		foundNode1 = foundNode1->getParent();
	}
	while(foundNode2){
		searchStack2.push(foundNode2);
		foundNode2 = foundNode2->getParent();
	}

	// curLevel is just the level that the comparison is at
	int curLevel = 0;

	// Comparison between the two stacks to get the "common ancestors"
	while(strcmp(searchStack1.top()->scientific_name, searchStack2.top()->scientific_name) == 0){
		cout << "Level[" << curLevel << "] Common Ancestor: ";
		searchStack1.top()->print();
		curLevel++;

		// Just makes sure that there are no seg faults
		if(searchStack1.size() > 1){
			searchStack1.pop();
		}
		if(searchStack2.size() > 1){
			searchStack2.pop();
		}
	}

	cout << endl;

	// Creates two different "levels"
	int stack1Level = curLevel;
	int stack2Level = curLevel;

	// Outputs the ancestry unique to the first species passed in
	cout << "Ancestry unique to " << search1 << endl;
	while(searchStack1.size() > 1){
		cout << "Level[" << stack1Level << "] ";
		searchStack1.top()->print();
		searchStack1.pop();
		stack1Level++;
	}

	cout << "Level[" << stack1Level << "] Species of interest: ";
	searchStack1.top()->print();

	cout << endl;

	// Outputs the ancestry unique to the second species passed in
	cout << "Ancestry unique to " << search2 << endl;
	while(searchStack2.size() > 1){
		cout << "Level[" << stack2Level << "] ";
		searchStack2.top()->print();
		searchStack2.pop();
		stack2Level++;
	}
	cout << "Level[" << stack2Level << "] Species of interest: ";
	searchStack2.top()->print();
}

// Dat main method
int main(int argc, char* argv[]){

	cout << "**************************************************" << endl;
	cout << "**                                              **" << endl;
	cout << "**      Welcome to my Tree of Life program!     **" << endl;
	cout << "**      -- VERSION 2.0 | March 15, 2013 --      **" << endl;
	cout << "**    -- We got stacks on stacks on stacks --   **" << endl;
	cout << "**                                              **" << endl;
	cout << "**************************************************" << endl;

	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	ifstream theFile ("species.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);

	// Find our root node
	root_node = doc.first_node();

	tree* speciesTree = parseTree(root_node);

	// currentInput keeps track of the current argv[] index
	int currentInput = 1;

	bool keepRunning = true;
	while(keepRunning){
		cout << "Please choose from the following options:" << endl;
		cout << "\t1.Get the lineage of a species" << endl;
		cout << "\t2.Get the commmon lineage of two species" << endl;
		cout << "\t3.Exit program" << endl;

		// Gets what the argument needs to be
		int currentArg;
		if(argc == currentInput){
			cin >> currentArg;
		}
		else{
			currentArg = atoi(argv[currentInput]);
			currentInput++;
		}

		// Get the lineage
		if(currentArg == 1){
			const char* species = " ";
			if(argc <= currentInput){
				cout << "Please enter the name of the species of interest:" << endl;
				string str;
				getline(cin, str);

				// This second getline() is in here because the first one wouldn't actually accept input...
				getline(cin, str);

				// Turns a string into const char* in order to pass it into method
				species = str.c_str();
			}
			else{
				species = argv[currentInput];
				currentInput++;
			}
			searchTree(speciesTree, species);
		}

		// Get the common lineage
		if(currentArg == 2){
			const char* species1 = " ";
			const char* species2 = " ";
			if(argc <= currentInput){
				cout << "Please enter the name of the first species: " << endl;
				string str;
				getline(cin, str);

				// This second getline() is in here because the first one wouldn't actually accept input...
				getline(cin, str);

				// Turns a string into const char* in order to pass it into method
				species1 = str.c_str();
				string str2;
				cout << "Please enter the name of the second species: " << endl;
				getline(cin, str2);

				// Turns a string into const char* in order to pass it into method
				species2 = str2.c_str();
			}
			else{
				species1 = argv[currentInput];
				currentInput++;
				species2 = argv[currentInput];
				currentInput++;
			}
			findCommon(speciesTree, species1, species2);
		}

		// Exits
		if(currentArg == 3){
			cout << "The program will now exit." << endl;
			keepRunning = false;
		}
	}

	return 0;
}
