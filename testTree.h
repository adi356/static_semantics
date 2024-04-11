#ifndef TESTTREE_H
#define TESTTREE_H

#include <set>

#include "scanner.h"

using namespace std; 

enum node_t { 
	PROGRAMn, 
	VARSn, 
	VARLISTn, 
	EXPn, 
	Mn, 
	Nn, 
	Rn, 
	STATSn, 
	MSTATn, 
	STATn, 
	BLOCKn, 
	INn, 
	OUTn, 
	IFn, 
	LOOPn, 
	ASSIGNn, 
	R0n,
};

struct node { 
	node_t label;
	Scanner::Token tk1;
	Scanner::Token tk2;
	Scanner::Token tk3;
	Scanner::Token tk4;
	Scanner::Token tk5;
	node *child1, *child2, *child3, *child4;
}; 



node * createNode(node_t label);
void traversePreorder(node *n, int depth);
void printNode(node *n, int depth);

#endif
