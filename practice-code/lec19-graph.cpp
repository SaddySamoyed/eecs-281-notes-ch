#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <limits>

class GraphMatrix {
private:
    std::vector<std::vector<int>> matrix; // 邻接矩阵
    int vertices;                         // 顶点数

    // DFS 只能确保在最短路唯一的情况下找到最短路，其他情况找到的路径不是最短的
    int dfs(int start, int target) {
        int path_length = 0;
        std::vector<int> path;
        std::vector<bool> visited(vertices, false);
        std::stack<int> search;
        std::vector<int> parent(vertices, -1);
        search.push(start);
        visited[start] = true;

        while (!search.empty()) {
            int current = search.top(); search.pop();
						
            // found: backtrace
            if (current == target) {
                int v = target;
                path_length = 0;
                while (v != -1) {
                    path.push_back(v);
                    int p = parent[v];
                    if (p != -1) {
                        path_length += matrix[p][v];
                    }
                    v = p;
                }
                return path_length;
            }

            for (int i = 0; i < vertices; ++i) {
                if (matrix[current][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    parent[i] = current;
                    search.push(i);
                }
            }
        }
        return -1;
    }

    // BFS 找最短路（仅适用于无权图或等权图）
    int bfs(int start, int end) {
        std::queue<int> q;
        std::vector<bool> visited(vertices, false);
        std::vector<int> distance(vertices, -1);
        std::vector<int> parent(vertices, -1);
        q.push(start);
        visited[start] = true;
        distance[start] = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == end) {
                int pathLength = 0;
                int node = end;
                while (node != -1 && node != start) {
                    node = parent[node];
                    pathLength+=1;
                }
                return pathLength;
            }

            for (int i = 0; i < vertices; ++i) {
                if (matrix[current][i] != 0 && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                    parent[i] = current;
                    distance[i] = distance[current] + 1;
                }
            }
        }
        return -1; // 未找到路径
    }

    // Dijkstra 算法
    std::vector<int> dijkstra(int start) {
        std::vector<int> dist(vertices, INT_MAX); // 到每个节点的最短距离
        std::vector<bool> visited(vertices, false); // 是否访问过
        dist[start] = 0;

        for (int i = 0; i < vertices; ++i) {
            // 找到当前未访问节点中距离最小的节点
            int u = -1;
            for (int j = 0; j < vertices; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INT_MAX) break; // 剩余节点不可达

            visited[u] = true;

            // 更新相邻节点的距离
            for (int v = 0; v < vertices; ++v) {
                if (matrix[u][v] > 0 && !visited[v]) { // 存在边且未访问
                    dist[v] = std::min(dist[v], dist[u] + matrix[u][v]);
                }
            }
        }

        return dist;
    }

    

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

    int DFSShortestPathOnlyForTree(int start, int end) {
        return dfs(start, end);
    }

    int BFSShortestPathOnlyForUnweighted(int start, int end) {
        return bfs(start, end);
    }

    int DijkstraShortestPath(int start, int end) {
        std::vector<int> dist = dijkstra(start);
        return dist[end];
    }
};


class GraphList {
private:
    std::vector<std::list<std::pair<int, int>>> adjList; // 邻接表
    int vertices;                                       // 顶点数

    // DFS 只能在最短路唯一的情况下找到最短路，其他情况找到的路径不是最短的
    bool dfs(int current, int target) {
        std::vector<bool> visited(vertices, false);
        std::vector<int> path;
        std::stack<int> search;
        int path_length = 0;
        std::vector<int> parent = std::vector<int>(vertices, -1);
        visited[current] = true;
        path.push_back(current);

        while (!search.empty()) {
            int current = search.top(); search.pop();
            if (current == target) {
                int v = target;
                path_length = 0;
                while (v != -1) {
                    path.push_back(v);
                    int p = parent[v];
                    if (p != -1) {
                        path_length += 1;
                    }
                    v = p;
                }
                return path_length;
            }

            for (const auto& [neighbor, weight] : adjList[current]) {
                if (!visited[neighbor]) {
                    search.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }
        return -1;
    }

    // BFS 找最短路（仅适用于无权图或等权图）
    int bfs(int start, int end) {
        std::queue<int> q;
        std::vector<bool> visited(vertices, false);
        std::vector<int> distance(vertices, -1);
        q.push(start);
        visited[start] = true;
        distance[start] = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == end) {
                return distance[current];
            }

            for (const auto& [neighbor, weight] : adjList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    distance[neighbor] = distance[current] + 1;
                }
            }
        }
        return -1; // 未找到路径
    }

    // Dijkstra 算法
    std::vector<int> dijkstra(int start) {
        std::vector<int> dist(vertices, INT_MAX); // 到每个节点的最短距离
        dist[start] = 0;

        using Node = std::pair<int, int>; // {距离, 节点}
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq; // 最小堆

        pq.emplace(0, start); // {距离, 起点}

        while (!pq.empty()) {
            auto [currentDist, u] = pq.top();
            pq.pop();

            if (currentDist > dist[u]) continue; // 忽略已更新的节点

            // 更新相邻节点的距离
            for (const auto& [v, weight] : adjList[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v); // 将更新后的距离加入优先队列
                }
            }
        }

        return dist;
    }

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
    
    int DFSShortestPathOnlyForTree(int start, int end) {
        return dfs(start, end);
    }

    int BFSShortestPathOnlyForUnweighted(int start, int end) {
        return bfs(start, end);
    }

    int DijkstraShortestPath(int start, int end) {
        std::vector<int> dist = dijkstra(start);
        return dist[end];
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

    std::cout << "DFS shortest path: " << graph.DFSShortestPathOnlyForTree(0, 2) << std::endl;
    std::cout << "BFS shortest path: " << graph.BFSShortestPathOnlyForUnweighted(0, 2) << std::endl;
    std::cout << "Dijkstra shortest path: " << graph.DijkstraShortestPath(0, 2) << std::endl;


    std::cout << std::endl << std::endl << "Graph represented by list:" << std::endl;
    GraphList graphlist(5); // 5个顶点
    graphlist.addEdge(0, 1, 2);
    graphlist.addEdge(0, 4, 5);
    graphlist.addEdge(1, 2, 3);
    graphlist.addEdge(1, 3, 1);
    graphlist.addEdge(3, 4, 4);

    std::cout << "graph represented by list:" << std::endl;
    graphlist.printList();
    std::cout << "DFS shortest path: " << graph.DFSShortestPathOnlyForTree(0, 2) << std::endl;
    std::cout << "BFS shortest path: " << graph.BFSShortestPathOnlyForUnweighted(0, 2) << std::endl;
    std::cout << "Dijkstra shortest path: " << graph.DijkstraShortestPath(0, 2) << std::endl;


    return 0;
}

