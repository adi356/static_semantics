#ifndef STATICSEMANTICS_H
#define STATICSEMANTICS_H

#include "scanner.h"
#include "testTree.h"

void insert(Scanner::Token tk, string label);
void verify(Scanner::Token tk, string label);
void staticSemantics(node *n, int depth);

#endif