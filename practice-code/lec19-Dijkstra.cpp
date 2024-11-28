#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

const int INF = INT_MAX;

// 不使用优先队列的 Dijkstra 算法
void dijkstraWithoutPQ(int n, int source, vector<vector<pair<int, int>>> &graph) {
    vector<int> dist(n, INF);       // 最短距离数组
    vector<bool> visited(n, false); // 是否访问过
    dist[source] = 0;
    for (int i = 0; i < n; ++i) {
        int u = -1;
        int minDist = INF;
        // 找到未访问节点中距离最小的节点
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }
        if (u == -1) break; // 所有节点都访问过或者无法到达
        visited[u] = true;

        // 更新相邻节点的距离
        for (auto &edge : graph[u]) {
            int v = edge.first, weight = edge.second;
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    // 输出结果
    for (int i = 0; i < n; ++i) {
        cout << "Distance from source to node " << i << ": ";
        if (dist[i] == INF) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }
}


// 使用优先队列的 Dijkstra 算法
void dijkstraWithPQ(int n, int source, vector<vector<pair<int, int>>> &graph) {
    vector<int> dist(n, INF); // 最短距离数组
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[source] = 0;
    pq.push({0, source}); // {距离, 节点}

    while (!pq.empty()) {
        auto [curDist, u] = pq.top(); pq.pop();

        if (curDist > dist[u]) continue; // 当前路径不优，不处理

        // 更新相邻节点的距离
        for (auto &edge : graph[u]) {
            int v = edge.first, weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // 输出结果
    for (int i = 0; i < n; ++i) {
        cout << "Distance from source to node " << i << ": ";
        if (dist[i] == INF) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }
}




// 使用优先队列的 Dijkstra 算法，带回溯功能
void dijkstraWithPath(int n, int source, vector<vector<pair<int, int>>> &graph) {
    vector<int> dist(n, INF);          // 最短距离数组
    vector<int> prev(n, -1);           // 前驱节点数组，用于回溯路径
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[source] = 0;
    pq.push({0, source}); // {距离, 节点}

    while (!pq.empty()) {
        auto [curDist, u] = pq.top(); pq.pop();

        if (curDist > dist[u]) continue; // 当前路径不优，不处理

        // 更新相邻节点的距离
        for (auto &edge : graph[u]) {
            int v = edge.first, weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u; // 记录前驱节点
                pq.push({dist[v], v});
            }
        }
    }

    // 输出结果：最短距离和路径
    for (int i = 0; i < n; ++i) {
        cout << "Distance from source to node " << i << ": ";
        if (dist[i] == INF) {
            cout << "INF" << endl;
            continue;
        }
        cout << dist[i] << endl;

        // 回溯路径
        cout << "Path: ";
        vector<int> path;
        for (int at = i; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end()); // 路径需要反转
        for (size_t j = 0; j < path.size(); ++j) {
            cout << path[j];
            if (j < path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}





int main() {
    int n = 5; // 节点数
    vector<vector<pair<int, int>>> graph(n);

    // 添加边：节点 u 到节点 v 的边权为 w
    graph[0].push_back({1, 10});
    graph[0].push_back({4, 5});
    graph[1].push_back({2, 1});
    graph[1].push_back({4, 2});
    graph[2].push_back({3, 4});
    graph[3].push_back({0, 7});
    graph[3].push_back({2, 6});
    graph[4].push_back({1, 3});
    graph[4].push_back({2, 9});
    graph[4].push_back({3, 2});

    std::cout << "Dijkstra without priority queue:" << std::endl;
    dijkstraWithoutPQ(n, 0, graph);
    std::cout << std::endl;
    std::cout << "Dijkstra with priority queue:" << std::endl;
    dijkstraWithPQ(n, 0, graph);
    std::cout << std::endl;
    std::cout << "Dijkstra with priority queue and path:" << std::endl;
    dijkstraWithPath(n, 0, graph);

    return 0;
}
