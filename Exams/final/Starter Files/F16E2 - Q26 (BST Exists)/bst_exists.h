/*
 * bst_exists.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F16E2 Q26.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef BST_EXISTS_H
#define BST_EXISTS_H

struct Node {
  int val;
  Node* right;
  Node* left;
};

bool exists(Node *node, int val);

#endif
