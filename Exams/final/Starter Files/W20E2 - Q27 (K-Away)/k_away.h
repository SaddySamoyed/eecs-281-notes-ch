/*
 * k_away.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 W20E2 Q27.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef K_AWAY_H 
#define K_AWAY_H

struct Node {
  Node* left;
  Node* right;
  bool selected;
};

unsigned int k_away(Node *root, int k);

#endif
