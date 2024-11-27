/* 
 * cycle.cpp 
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 9 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convenience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "cycle.h"

using namespace std;

// complexity: O(V + E)
bool is_graph_cyclic(const vector<vector<int>> &adj_list) {
    unordered_set<int> visited;

    // Since the graph is connected, we only need to start from one node (e.g., node 0 or 1)
    return hasCycleDFS(0, -1, adj_list, visited);
}

bool hasCycleDFS(int node, int parent, 
                const vector<vector<int>>& adjList, 
                unordered_set<int>& visited) {
    visited.insert(node);

    for (int neighbor : adjList[size_t(node)]) {
        // If the neighbor is not visited, recurse
        if (visited.find(neighbor) == visited.end()) {
            return hasCycleDFS(neighbor, node, adjList, visited);
        }
        // If the neighbor is visited and not the parent, we found a cycle
        else {
          if (neighbor != parent)
            return true;
        }
    }
    // reach here: all neighbors are visited, and not parent, then ends
    return false;
}



int main() {
    // Example: Input graph
    const vector<vector<int>> adjList = {
        {2, 3}, //0
        {2},  //1
        {0, 1}, //2
        {0} //3
    };

    if (is_graph_cyclic(adjList)) {
        cout << "Graph contains a cycle" << endl;
    } else {
        cout << "Graph does not contain a cycle" << endl;
    }

    return 0;
}
