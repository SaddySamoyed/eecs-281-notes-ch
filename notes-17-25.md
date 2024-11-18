









## Lec 17 (Trees)

两个 equivalent def of trees:

1. 无 cycle 的 connected graph
2. 一个 graph，其中任意两个 node 之间的 paths 都存在唯一的 shortest one. （这个定义和 1 等价，因为这当且仅当没有 cycle. 如果有 cycle, 那么 cycle 之间一定存在两个点，有多个 path 都是 shortest 的）





### Types: Simple(Undirected) / Rooted(Directed)

Tree 可以被分为 simple tree 和 rooted tree

**tree 中，任何 node 都可以作为 root.** 

1. simple tree 就是不特定选择 root 的 tree，rooted tree 就是选定了一个 node 作为 root 的 tree

   可以视作 **simple tree 是 undirected 的，rooted tree 是 directed 的**。因为 rooted tree 的所有 edges 都可以视作 directed away from the root. 

2. **Ordered tree 是一种 rooted tree**，选定了一个 root 并且给 children of each node 进行 linear ordering

3. **Binary tree 就是任意 node 都有最多两个 children 的 ordered tree**
4. Complete binary tree 是一个 depth 为 d 的 tree，其中 depth 1, ...., d-1 都是满的，而最后一层 depth d 中间不能有空缺，空缺必须至多集中在右边。

<img src="note-assets/Screenshot 2024-11-17 at 19.48.31.png" alt="Screenshot 2024-11-17 at 19.48.31" style="zoom:67%;" />



### Binary Tree 的 array implementation

1. Root 在 index 1（index 0 为 dummy）
2. left child of node $i$ 在 index $2i$
3. right child of node $i$ 在 index $2i + 1$



**binary tree 如果用 arrray 表示，只能以 complete binary tree 的形式进行。**因为我们使用的是连续的内存。当然，tree 本身不一定是 complete 的。在空缺的节点应有标注。

我们发现这个 implementation 的时间复杂度，除了 remove 之外都很好。

1. Insert: **平均 O(1)**，差在结尾。当 tree 当前一层满了要 grow 的时候是 O(n)，全部 copy
2. Remove: 稍微有些麻烦，不能直接 remove 一个节点不管它的 subtree. 根据需求，要么 fix down 要么删除整个 subtree，但是都要 **O(n)**
3. Parent, child: O(1)，直接 n/2, 2n, 2n+1

空间复杂度：tree 越接近 complete 越好，越 sparse 越差。

best case: complete，**O(n)**

worst case: sparse，每层只有一个，**O(2^n)**

```
         1
       /  
      2    
     /     
    4     
```





### Binary Tree 的 pointer-based implementation 

```c++
template <class KEY>
struct Node {
  KEY key,
  Node *left = nullptr;
  Node *right = nullptr;
  Node(const KEY &k)  : key{k} {}
}; 
```



优点：首先在空间上优于 array. 总是 O(n)

并且，moving down a tree from parent to child 更加 efficient





#### Thinking: add `parent` ?

我们看到 pointer-based implementation 获取 parent 的 complexity 是 O(n) 的. 我们想这完全没必要：为什么不添加一个 `parent` 变量来直接把它变成 O(1) 呢？

答案是在使用 pointer-based binary tree 作为 data structure 的模型里，我们通常需要 tree 来实现的是它 recursive 的特点，通常不太会需要知道一个 node 的 parent 是什么。

所以功能性地，我们去掉这个变量来减轻 space complexity. 我们获取 parent 的方法是：traverse 整个树.



我们发现这个 implementation 的时间复杂度，除了 remove 之外都很好。

1. Insert: **best O(1), worst O(n)**. binary tree 一般都有需要维持的不变量，比如 BST。insert takes 一个 root 和一个 Key 作为参数，从 root 一层层往下比较进行 insert. 最好的情况 root 是 null, 直接插入；最坏的情况遍历完一整个树。insert 也是一个 recursive 的函数，一层一层 root 下移。

2. Remove:  **O(n)**. remove 特别复杂。以 BST 为例。

   删除一个节点时分为三种情况：

   - 节点是叶子节点：直接删除。
   - 节点有一个子节点：用子节点替代被删除的节点。
   - 节点有两个子节点：用右子树的最小节点（中序后继）或左子树的最大节点（中序前驱）替代被删除的节点。

3. Parent: **O(n)**，traverse tree

4. child: **O(1)**

空间复杂度：**O(n)**



### Transfrom a tree into Binary tree

如何 transform 任意一个 tree 为一个 binary tree:

我们使用 left/right children 的关系来取代 sibling 的关系

对于 $v$  的所有 children $\{v_1, v_2, \cdots, v_k\}$，我们把 $v_1$ 变为 new tree 中 $v$ 的 left child，而 $\{v_2, \cdots, v_k\}$ 变为 a chain of right children of $v_1$

Recursively do this to $v_2, \cdots, v_k$ 的 children . 这样就把所有信息都保存下来了. 

<img src="note-assets/Screenshot 2024-11-17 at 20.23.52.png" alt="Screenshot 2024-11-17 at 20.23.52" style="zoom:50%;" />











### Binary Tree Traversal

#### DFS (Preorder, Inorder, postorder)

preorder:

1. visit node
2. visit left subtree
3. visit right subtree

```c++
void preorder(Node *p) {
  if (!p) return;
  visit(p->key);
  preorder(p->left);
  preorder(p->right);
}
```



inorder

1. visit left subtree
2. visit node
3. visit right subtree



postorder

1. visit left subtree
2. visit right subtree
3. visit node





### BFS (levelorder)

Visit nodes in order of increasing depth



<img src="note-assets/Screenshot 2024-11-17 at 20.56.55.png" alt="Screenshot 2024-11-17 at 20.56.55" style="zoom:50%;" />

BFS 总是要使用 queue 的. queue 就是一个用来 BFS 的数据结构. 这样总是能保证同一层的被遍历完了开始下一层.

```c++
void levelorder(Node *p) {
  if (!p) return;
  queue<Node *>q;
  q.push(p);
  
  while (!q.empty()) {
    Node *n = q.front();
    q.pop();
    cout << n->key << " ";
    if (n->left) q.push(n->left);
    if (n->right) q.push(n->right);
  }
}
```







## Lec 18 (BST & AVL tree)

















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

