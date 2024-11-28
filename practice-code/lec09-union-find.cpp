#include <vector>
#include <iostream>
using namespace std;

class UnionFind {
private:
    vector<int> parent;  // 存储每个节点的父节点
    vector<int> rank;    // 用于按秩优化

public:
    // 构造函数，初始化 n 个节点
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);  // 初始秩为 0
        for (int i = 0; i < size; ++i) {
            parent[i] = i;  // 每个节点的初始父节点是自己
        }
    }

    // 查找操作，带路径压缩
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 递归查找根节点并路径压缩
        }
        return parent[x];
    }

    // 合并操作，按秩优化
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX] += 1;  // 如果秩相同，提升 rootX 的秩
            }
        }
    }

    // 判断两个节点是否属于同一集合
    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    UnionFind uf(10);  // 创建包含 10 个节点的 Union-Find 结构

    // 合并一些节点
    uf.unionSets(1, 2);
    uf.unionSets(2, 3);
    uf.unionSets(4, 5);

    // 检查连通性
    cout << "1 and 3 are connected: " << uf.isConnected(1, 3) << endl;  // 输出 1 (true)
    cout << "1 and 5 are connected: " << uf.isConnected(1, 5) << endl;  // 输出 0 (false)

    // 再次合并
    uf.unionSets(3, 4);

    // 检查连通性
    cout << "1 and 5 are connected: " << uf.isConnected(1, 5) << endl;  // 输出 1 (true)

    return 0;
}