#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

// Prim's Algorithm Implementation
void primMST(vector<vector<pair<int, int>>> &graph, int V) {
    vector<int> minimal_weight(V, INT_MAX);   // To store the minimum weight for each vertex
    vector<bool> inMST(V, false);   // To check if a vertex is included in the MST
    vector<int> parent(V, -1);      // To store the parent of each vertex in the MST

    minimal_weight[0] = 0;   // Start from vertex 0

    for (int count = 0; count < V - 1; count++) {
        int minKey = INT_MAX, u;

        // Find the minimum key vertex not included in the MST
        for (int v = 0; v < V; v++) {
            if (!inMST[v] && minimal_weight[v] < minKey) {
                minKey = minimal_weight[v];
                u = v;
            }
        }

        inMST[u] = true; // Include the vertex in the MST

        // Update key value and parent for adjacent vertices
        for (auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!inMST[v] && weight < minimal_weight[v]) {
                minimal_weight[v] = weight;
                parent[v] = u;
            }
        }
    }

    // Print the MST
    cout << "Prim's MST:\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\n";
    }
}

// Prim's Algorithm Implementation using Heap
void primMSTHeap(vector<vector<pair<int, int>>> &graph, int V) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> key(V, INT_MAX);   // To store the minimum weight for each vertex
    vector<bool> inMST(V, false);  // To check if a vertex is included in the MST
    vector<int> parent(V, -1);     // To store the parent of each vertex in the MST

    key[0] = 0;
    pq.push({0, 0});  // (weight, vertex)

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) {
            continue;
        }

        inMST[u] = true; // Include the vertex in the MST

        // Update key value and parent for adjacent vertices
        for (auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    // Print the MST
    cout << "Prim's MST using Heap:\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\n";
    }
}









// Kruskal's Algorithm Implementation
struct Edge {
    int src, dest, weight;
};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Union-Find Disjoint Set data structure
struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

void kruskalMST(vector<Edge> &edges, int V) {
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(V);
    vector<Edge> mst;

    for (auto &edge : edges) {
        if (ds.find(edge.src) != ds.find(edge.dest)) {
            mst.push_back(edge);
            ds.unite(edge.src, edge.dest);
        }
    }

    // Print the MST
    cout << "Kruskal's MST:\n";
    for (auto &edge : mst) {
        cout << edge.src << " - " << edge.dest << "\n";
    }
}

int main() {
    int V = 5;
    vector<vector<pair<int, int>>> graph(V);

    // Adjacency list representation for Prim's algorithm
    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});

    primMST(graph, V);
    primMSTHeap(graph, V);

    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8}, {1, 4, 5}, {2, 4, 7}
    };

    kruskalMST(edges, V);

    return 0;
}
