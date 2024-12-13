Tree Def

1. 无 cycle 的 connected graph
2. 任意两个 node 之间的 paths 都存在唯一的 shortest one. 

Properties:

1. **如果一个 tree 有 n 个顶点，那么它一定有 n-1 个 edges.**
   $$
   |E_{tree}| = |V_{tree}| -1
   $$
   这个性质是源于：tree 是一个连通图。

   **一个有 |V|-1 条边的连通图一定是 tree.** **其实这三条性质：边数n-1，连通，无环中只要有两条就可以推导出另一条并表明这是一个树**

2. **只要往 tree 中加入任意一条新的边，就会形成 cycle**

3. **只要在 tree 中去掉任意一条边，就会 disconnect**

4. 每个 tree 都是二分图. （图是二分图当且仅当不包含奇数长度的环





Binary Tree Array: Root 在 index 1，0dummy，left child of node $i$ 在 index $2i$，right child of node $i$ 在 index $2i + 1$

1. Insert: 平均 O(1)， grow O(n)
2. Remove: 稍微有些麻烦，不能直接 remove 一个节点不管它的 subtree. 根据需求，要么 fix down 要么删除整个 subtree，但是都要 **O(n)**
3. Parent, child: O(1)，直接 n/2, 2n, 2n+1

Space：best case，complete，**O(n)**；worst case: sparse 每层只有一个，**O(2^n)**



#### Transfrom a tree into Binary tree

对于 $v$  的所有 children $\{v_1, v_2, \cdots, v_k\}$，我们把 $v_1$ 变为 new tree 中 $v$ 的 left child，而 $\{v_2, \cdots, v_k\}$ 变为 a chain of right children of $v_1$，Recursively do this to $v_2, \cdots, v_k$ 的 children .



#### DFS (Preorder, Inorder, postorder)

preorder DFS: visit node，visit left subtree，visit right subtree

```c++
void preorder(Node *p) {
  if (!p) return; visit(p->key);
  preorder(p->left); preorder(p->right);
}
```

inorder DFS: visit left subtree，visit node，visit right subtree

postorder DFS: visit left subtree，visit right subtree，visit node

level order BFS: 

```c++
void levelorder(Node *p) {if (!p) return;
  queue<Node *>q; q.push(p);
  while (!q.empty()) {
    Node *n = q.front(); q.pop();
    if (n->left) q.push(n->left);
    if (n->right) q.push(n->right);
  }
}
```

<img src="note-assets/Screenshot 2024-11-17 at 20.56.55.png" alt="Screenshot 2024-11-17 at 20.56.55" style="zoom:50%;" />