/*
 * descendant_averages.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 W20E2 Q26.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef DESCENDANT_AVERAGES_H 
#define DESCENDANT_AVERAGES_H

#include <vector>

struct Node {
    double val;
    std::vector<Node *> children;
    Node(double x) : val{x} { }
};

std::vector<double> query_descendant_averages(Node *root,
                                         const std::vector<int>& indices);

#endif
