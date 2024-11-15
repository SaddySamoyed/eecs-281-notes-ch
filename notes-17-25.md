



## Lab 09 (Graphs)



### algorithm problem: decide graph has a cycle

Given: 一个 connected graph with adjacent list



idea:
DFS the graph. 

每次到一个 Node, mark it as visited.

每次 DFS 的时候，我们有：

1. 当前 node 的上一个 node (当前 node 是哪个 node DFS 来的)
2. 当前 node
3. 当前 node 的 adjacent nodes, 等待 DFS

我们传入当前 node 的上一个 node 为 parent；检查每个新到的 node 是不是当前 node 的 parent 或者 unvisited：如果既不是 parent 又已经 visited 了，那么说明它是一个 back route. 于是一定存在 cycle.



```c++
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

}

```

