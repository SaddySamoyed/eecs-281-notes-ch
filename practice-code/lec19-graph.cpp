#include <iostream>
#include <vector>
#include <list>

class GraphMatrix {
private:
    std::vector<std::vector<int>> matrix; // 邻接矩阵
    int vertices;                         // 顶点数

public:
    // 构造函数
    GraphMatrix(int n) : vertices(n) {
        matrix.resize(n, std::vector<int>(n, 0)); // 初始化为0
    }

    // 添加边
    void addEdge(int u, int v, int weight) {
        matrix[u][v] = weight;
        matrix[v][u] = weight; // 无向图对称
    }

    int getVertices() {
        return vertices;
    }

    // 打印矩阵
    void printMatrix() {
        for (const auto& row : matrix) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
};


class GraphList {
private:
    std::vector<std::list<std::pair<int, int>>> adjList; // 邻接表
    int vertices;                                       // 顶点数

public:
    // 构造函数
    GraphList(int n) : vertices(n) {
        adjList.resize(n); // 初始化邻接表
    }

    // 添加边
    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // 无向图添加对称边
    }

    int getVertices() {
        return vertices;
    }

    // 打印邻接表
    void printList() {
        for (int i = 0; i < vertices; ++i) {
            std::cout << i << ": ";
            for (const auto& [neighbor, weight] : adjList[i]) {
                std::cout << "(" << neighbor << ", " << weight << ") ";
            }
            std::cout << std::endl;
        }
    }
};



int main() {
    GraphMatrix graph(5); // 5个顶点
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 4, 5);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 1);
    graph.addEdge(3, 4, 4);

    std::cout << "verticess count: " << graph.getVertices() << std::endl;
    std::cout << "Graph represented by matrix:" << std::endl;
    graph.printMatrix();


    GraphList graphlist(5); // 5个顶点
    graphlist.addEdge(0, 1, 2);
    graphlist.addEdge(0, 4, 5);
    graphlist.addEdge(1, 2, 3);
    graphlist.addEdge(1, 3, 1);
    graphlist.addEdge(3, 4, 4);

    std::cout << "graph represented by list:" << std::endl;
    graphlist.printList();

    return 0;
}
