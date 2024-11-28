/*  Identifier = 15C1680EE94C640EC35E1694295A3625C3254CBA

    EECS 281 Lab 4: Connected Components

    For this lab, you will write a program that calculates the
    number of connected components in an undirected graph.

    Your program will receive an input file in the following format:
    1) The first line of input contains the number of vertices V and number
       of edges E in the graph.
    2) The next E lines list out the connections between vertices in the
       graph in the format of "u v", which indicates the existence of an edge
       between u and v.

    For example, the following input file would be read as follows:
    4 2  (the graph has 4 vertices numbered from 0-3, and two edges exist in
          the graph)
    0 1  (the first of these edges connects vertex 0 with vertex 1)
    0 2  (the second of these edges connects vertex 0 with vertex 2)

    In this case, vertices {0, 1, 2} form a connected component, and vertex
    {3} forms a connected component (since 3 is not connected to anything).
    Thus, your program should print out 2.

    You will be using union-find to complete this lab. The following starter
    code has been provided. Feel free to modify this code in your
    implementation. Good luck!
*/

#include <cstdint>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;


class Graph {
    uint32_t V;
    uint32_t E;
    // TODO: add any additional member variables, as needed
    // QL: done
    vector<uint32_t> parent;
    vector<uint32_t> connected;

public:
    // Graph constructor that initializes the graph and its member variables
    Graph(uint32_t v, uint32_t e): V(v), E(e) {
        parent.resize(v);
        connected.resize(v,0);
        for (uint32_t i = 0; i < V; ++i) { parent[i] = i; }

        uint32_t vertice1 = 0;
        uint32_t vertice2 = 0;
        // cin
        for (uint32_t i = 0; i < E; ++i) {
            cin >> vertice1 >> vertice2;
            // if vertice1 is a represent, need to connect them, update parent of it to vertice2
            if (parent[vertice1] == vertice1) {
                if (vertice1 != find_set(vertice2)) {
                    parent[vertice1] = vertice2;
                }
            } else {
                if (parent[vertice1] != vertice2) {
                    union_set(vertice1, parent[vertice2]);
                }
            }
        }

    } // Graph()


    uint32_t find_set(uint32_t v) {
        // TODO: implement the find_set function
        // QL: done. Find root, it stops when root==itself, which means that this is real root
        while (parent[v] != v) { v = parent[v]; }
        return v;
    }  // find_set()


    void union_set(uint32_t a, uint32_t b) {
        // TODO: implement the union_set function
        // QL: done
        int rootA = find_set(a);
        int rootB = find_set(b);
        int finalRoot = 0;
        int which = 0;

        // union the smaller root to the bigger root by vertice1resentative
        if (rootA < rootB) {
            parent[rootB] = rootA;
            which = b;
            finalRoot = rootA;
        } else {
            parent[rootA] = rootB;
            which = a;
            finalRoot = rootB;
        }
        
        // path compression
        int mark = 0;
        while (which != finalRoot) {
            mark = parent[which];
            parent[which] = finalRoot;
            which = mark;
        }

    }  // union_set()


    uint32_t count_components() {
        // TODO: implement the count_components function
        // QL: done. use dummy vector to record whether connected
        uint32_t components = 0;
        for (uint32_t i = 0; i < parent.size(); ++i) {
            if (parent[i] == i) { connected[i] = 1; } 
            else { connected[find_set(i)] = 1; }
        }
        
        for (uint32_t j = 0; j < connected.size(); ++j) {
            if (connected[j] == 1) { components++; }
        }
        return components;
    }  // count_components()
};  // Graph{}


int main() {
    // You do not need to modify main.
    std::ios_base::sync_with_stdio(false);
    uint32_t vertex_count, edge_count = 0;

    cin >> vertex_count;
    cin >> edge_count;

    Graph g(vertex_count, edge_count);

    cout << g.count_components() << endl;
    return 0;
}  // main()
