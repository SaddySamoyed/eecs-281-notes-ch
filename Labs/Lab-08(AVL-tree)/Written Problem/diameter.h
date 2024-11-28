/*
* diameter.h
* University of Michigan, Ann Arbor
* EECS 281 Lab 8 Written.
* DO NOT SUBMIT TO GRADESCOPE.
* If submitted, this file will be ignored.
*/

#ifndef DIAMETER_H
#define DIAMETER_H

struct BinaryTreeNode {
  BinaryTreeNode* left;
  BinaryTreeNode* right;
  int value;
  BinaryTreeNode(int n) : left{nullptr}, right{nullptr}, value{n} {}
};

int diameter(const BinaryTreeNode* tree);

#endif