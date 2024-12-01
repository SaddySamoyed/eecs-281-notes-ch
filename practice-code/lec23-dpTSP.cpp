#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int tsp(int n, const vector<vector<int>>& cost) {
    // dp[mask][i] 表示从起点 0 出发，经过 mask 表示的所有城市，最后停留在城市 i 的最短路径长度
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    
    // 初始状态，从起点 0 出发，路径长度为 0
    dp[1][0] = 0;

    // 遍历所有状态 mask
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            // 如果城市 i 不在当前 mask 中，跳过
            if (!(mask & (1 << i))) continue;

            // 尝试从集合 mask 中的其他城市转移到 i
            for (int j = 0; j < n; ++j) {
                if (j != i && (mask & (1 << j)) && dp[mask ^ (1 << i)][j] != INT_MAX) {
                    dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + cost[j][i]);
                }
            }
        }
    }

    // 最后计算从每个终点返回起点的最短路径
    int result = INT_MAX;
    for (int i = 1; i < n; ++i) {
        if (dp[(1 << n) - 1][i] != INT_MAX) {
            result = min(result, dp[(1 << n) - 1][i] + cost[i][0]);
        }
    }

    return result;
}

int main() {
    // 示例输入：城市数量和代价矩阵
    int n = 4;
    vector<vector<int>> cost = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int shortestPath = tsp(n, cost);
    // 输出结果
    if (shortestPath == INT_MAX) {
        cout << "No valid path found." << endl;
    } else {
        cout << "The shortest path length is: " << shortestPath << endl;
    }

    return 0;
}
