#include "testTree.h"

#include <cstdio>
#include <fstream>
#include <iostream> 
#include <string> 
#include <set>
#include <stack>

using namespace std; 

std::set <string> idList;

string nonTerminal_names[] = {
        "PROGRAM", "VARS", "VARLIST", "EXP", "M", "N", "R", "STATS", "MSTAT", "STAT", "BLOCK", "IN", "OUT", "IF", "LOOP", "ASSIGN", "R0",
};



node * createNode(node_t r) {
	node * root = new node;
	root -> label = r;

	Scanner::Token token1;
	Scanner::Token token2;
	Scanner::Token token3;
	Scanner::Token token4;
	Scanner::Token token5;
	root -> tk1 = token1;
	root -> tk2 = token2;
	root -> tk3 = token3;
	root -> tk4 = token4;
	root -> tk5 = token5;
	root -> child1 = NULL;
	root -> child2 = NULL;
	root -> child3 = NULL;
	root -> child4 = NULL;
	return root;
}

// start at root and visit each node before child node 
void traversePreorder(node *n, int depth) {
	if(n) {
		printNode(n, depth);
		traversePreorder(n -> child1, depth+1);
		traversePreorder(n -> child2, depth+1);
		traversePreorder(n -> child3, depth+1);
		traversePreorder(n -> child4, depth+1);
	}
}

// Visits nodes and prints parse tree
// TODO: need to figure out how to connect similar levels of tree
void printNode(node *n, int depth) { 
	string space = "";

	for (int i = 0; i < depth*2; i++) {
		space=space + " ";
	}

	cout << space << nonTerminal_names[n -> label] << ": ";

	if(n -> tk1.value != "") {
		cout << n->tk1.value << " ";
	}
	if(n -> tk2.value != "") {
		cout << n->tk2.value << " ";
	}
	if(n -> tk3.value != "") {
		cout << n->tk3.value << " ";
	}
	if(n -> tk4.value != "") {
		cout << n->tk4.value << " ";
	}
	if(n -> tk5.value != "") {
		cout << n->tk5.value << " ";
	}
	cout << endl;
}

//added staticSemantics for P3
void staticSemantics(node *n, int depth) {
	if(n) {
		
		insert(n->tk1, nonTerminal_names[n->label]);
		insert(n->tk2, nonTerminal_names[n->label]);
		insert(n->tk3, nonTerminal_names[n->label]);
		insert(n->tk4, nonTerminal_names[n->label]);
		insert(n->tk5, nonTerminal_names[n->label]);

		verify(n->tk1, nonTerminal_names[n->label]);
		verify(n->tk2, nonTerminal_names[n->label]);
		verify(n->tk3, nonTerminal_names[n->label]);
		verify(n->tk4, nonTerminal_names[n->label]);
		verify(n->tk5, nonTerminal_names[n->label]);

		staticSemantics(n->child1, depth+1);
		staticSemantics(n->child2, depth+1);
		staticSemantics(n->child3, depth+1);
		staticSemantics(n->child4, depth+1);
		//return semanticError;
	}
}

// added insert for P3
void insert(Scanner::Token tk, string label){
	if(tk.value != "" && tk.type == "IDENTIFIER" && label == "VARLIST"){
		auto it = idList.find(tk.value);
		if (it != idList.end()) {      	// Found in idList, throw detailed error msg       
        	std::cout << "SEMANTICAL ERROR: redefinition of " << tk.value;
			std::cout << " on line " << tk.line << "\n";
		} else {                       	// Not found in idList, add to idList		
			idList.insert(tk.value);
		}
	}	
}


// added verify for P3
 void verify(Scanner::Token tk, string label) {
	if(tk.value != "" && tk.type == "IDENTIFIER" && label != "VARLIST") {
		auto it = idList.find(tk.value);
		if (it == idList.end()) {
			std::cout << "SEMANTICS ERROR: use without declaration " << tk.value;
			std::cout << " on line " << tk.line << "\n";
		}
	}
 }
 
