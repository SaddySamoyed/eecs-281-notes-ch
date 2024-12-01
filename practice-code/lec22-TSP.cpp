#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();



struct Node {
    int level;       // 当前深度
    int cost;        // 当前路径的代价
    int bound;       // 当前节点的下界
    vector<int> path; // 当前路径

    // 优先队列的比较函数，小的优先
    bool operator<(const Node& other) const {
        return bound > other.bound;
    }
};

// 计算给定矩阵的最小边界
int calculateBound(const vector<vector<int>>& dist, const vector<int>& path, int n) {
    int bound = 0;

    // 标记已经访问的城市
    vector<bool> visited(n, false);
    for (int city : path) visited[city] = true;

    // 加上路径中已有的代价
    for (size_t i = 1; i < path.size(); ++i) {
        bound += dist[path[i - 1]][path[i]];
    }

    // 为未访问的城市估计下界
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int minCost = INF;
            for (int j = 0; j < n; ++j) {
                if (i != j && !visited[j]) {
                    minCost = min(minCost, dist[i][j]);
                }
            }
            if (minCost != INF) bound += minCost;
        }
    }

    return bound;
}

// TSP 分支限界主函数
int tspBranchAndBound(const vector<vector<int>>& dist) {
    int n = dist.size();
    priority_queue<Node> pq; // 优先队列，按节点的下界排序
    int bestCost = INF;      // 当前最优解
    vector<int> bestPath;    // 最优路径

    // 初始节点
    Node root;
    root.level = 0;
    root.cost = 0;
    root.path = {0}; // 从城市 0 开始
    root.bound = calculateBound(dist, root.path, n);
    pq.push(root);

    // 分支限界搜索
    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        // 如果当前节点的下界大于最优解，剪枝
        if (curr.bound >= bestCost) continue;

        // 如果当前路径包含所有城市并回到起点
        if (curr.level == n - 1) {
            // 计算完整路径的代价
            int totalCost = curr.cost + dist[curr.path.back()][0];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestPath = curr.path;
                bestPath.push_back(0); // 回到起点
            }
            continue;
        }

        // 生成子节点
        for (int i = 0; i < n; ++i) {
            if (find(curr.path.begin(), curr.path.end(), i) == curr.path.end()) {
                Node child;
                child.level = curr.level + 1;
                child.path = curr.path;
                child.path.push_back(i);
                child.cost = curr.cost + dist[curr.path.back()][i];
                child.bound = child.cost + calculateBound(dist, child.path, n);

                // 如果下界小于当前最优解，加入优先队列
                if (child.bound < bestCost) {
                    pq.push(child);
                }
            }
        }
    }

    // 输出最优路径
    cout << "最优路径: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;

    return bestCost;
}


int main() {
    // 示例：距离矩阵
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int result2 = tspBranchAndBound(dist);
    cout << "Shortest path by branch and bound: " << result2 << endl;

    return 0;
}
