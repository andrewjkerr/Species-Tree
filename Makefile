###########################################
# Author: hasseo
# COP3530 Project #3
# Due Date: Friday March 15, 2013
# ----
# This project does some crazy stuff with XML and something about slime molds...
# ----
# Makefile WAS CREATED IN VERSION 1.2.
# Makefile WAS LAST UPDATED IN VERSION 1.2.
###########################################

tree : main.o tree.o node.o
	g++ -o tree main.o tree.o node.o
       
main.o : main.cpp tree.h node.h rapidxml.hpp rapidxml_print.hpp rapidxml_utils.hpp
	g++ -c main.cpp
 
tree.o : tree.cpp tree.h node.h
	g++ -c tree.cpp
 
node.o : node.cpp node.h
	g++ -c node.cpp