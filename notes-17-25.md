









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

BST 是一个 Binary tree, 并满足：

**任意一个 node 都比它的 left subtree 中的所有 nodes 要大，比它的 right subtree 中的所有 nodes 要 <=（可以有 duplicate** 



<img src="note-assets/Screenshot 2024-11-17 at 21.52.02.png" alt="Screenshot 2024-11-17 at 21.52.02" style="zoom:50%;" />



THM：inorder traverse 一个 BST 获得一个 non-decreasing seq.

Which means: 我们可以 do binary search / upper/lower_bound on BST. 

并且这个 binary search 由于树的结构，比 array 上的更简单



### binary search on BST

```c++
Node *tree_search(Node *x, KEY k) {
  while (x != nullptr && k!= x->key) {
    if (k < x-> key) x = x-> left;
    else x = x-> right;
  }
  return x;
}
```

得到的是一个自顶向下的 path.

O(logn) average.

worst case: 退化成链表的 BST. 一个 stick. 只有这种极端情况有 O(n).







### `insert` in BST

和 search 相似.

找到 upper bound 和 lower bound，在中间插入.

<img src="note-assets/Screenshot 2024-11-17 at 22.00.41.png" alt="Screenshot 2024-11-17 at 22.00.41" style="zoom:50%;" />

注意：我们需要一个没有唯一答案的 deterministic policy 来处理 duplicate. 放在左边还是右边？取决于我们对

v ? current then search left

v ?  current then search right 

的处理. STL 使用 <, >=

（也可以使用 <=, >



```c++
void BST_insert(Node *&x, KEY k) {
  if (x == nullptr)
    x = new Node(k);
  else if (k < x-> key)
    BST_insert(x->left, k);
  else 
    BST_insert(x->right, k);
}
```

不论是插入还是搜索，处理 binary tree 的核心在于 rebase root，对左子树和右子树分别处理.



Complexity:

对于 well-balanced BST，O(log n)

对于 stick, 退化成链表的 BST，worst case，O(n)

average O(log n)



实际上对于任意一组数据，都存在一个排列方式能触发 worst case（比如 sorted 的）

实际上触发 worst case 居然挺容易的。

这也是为什么我们需要一个可以 self balance 的 binary tree. 等下讲



#### exercise: find min

找到 leftmost 即可

```c++
Node *tree_min(Node *x) {
  if (x == nullptr)
    return nullptr;
 	while (x->left)
    x = x->left;
  return x;
}
```

Average: O(log n)

Worst: O(n)



### `remove` in BST

Cases:

1. no children (trivial)
2. no left child
3. no right child
4. has two children

**case 2,3 即：replace the current node by its left/right child.** 也是等于 trivial 的. 



case 4 有一点难度.

#### when `v` has both children

observe: left subtree 中所有的元素，都比 right subtree 要小！

**所以：我们把 right subtree 中最小的一个元素（一定是 leaf）拿出来 replace `v` 就可以了**

称这个

<img src="note-assets/Screenshot 2024-11-17 at 22.22.04.png" alt="Screenshot 2024-11-17 at 22.22.04" style="zoom:50%;" />

```c++
template <class T>
void BinaryTree<T>::remove(Node *&tree, const T &val) {
	Node *nodeToDelete = tree;
  Node *inorderSuccessor;
  
  // first find the position containing the value to remove
  if (!tree) return;
  else if (val < tree->value) remove(tree->left, val);
  else if (val > tree->value) remove(tree->right, val);
  
  // do remove
  else {
    // two trivial cases
    if (tree->left == nullptr) {
      tree = tree->right;
      delete nodeToDelete;
    }
    if (tree->right == nullptr) {
      tree = tree->left;
  		delete nodeToDelete;
    }
    // real shit
    else {
      inorderSuccessor = tree->right;
      //find the inorderSuccessor
      while (inorderSuccessor->left != nullptr){
        inorderSuccessor = inorderSuccessor->left;
      }
      // replace the value of the node with the value of the succssor
      nodeToDelete->value = inorderSuccessor->value;
      // do one more round, just to remove the original inorderSuccessor
      remove(tree->right, inorderSuccessor->value);
    }
  }
}
```

仍然是 average O(logn)，worst O(n).







### AVL tree

BST 不足之处在于 worst case 总是 O(n) 的. 当数据插入的顺序不巧比较 sorted 时，我们会得到一个几乎退化成链表的 BST，使得所有行为都接近 O(n). 我们希望有一个能自动 balance 自己的 BST.

所以就有了 AVL tree. 名字来自发明者



AVL tree 是一种 self-balancing BST. Self-balancing 的意思是 AVL tree 有 **Height Balance Property: 对于任意 internal node，它的左右 subtrees 的 height 差别 <=1**

这个性质的实现是它依靠 rotation 来 correct imbalance.

Height Balance Property 使得 AVL tree 的 search, insert, remove 达到 **worst case O(logn)**

<img src="note-assets/Screenshot 2024-11-17 at 23.33.07.png" alt="Screenshot 2024-11-17 at 23.33.07" style="zoom: 50%;" />

虽然这很显然，但是我们也可以证明它:

不妨考虑 AVL 树的最极端情况：任意左右树 height 都相差了 1

Let $n(h)$ 表示 height $h$ 的 tree 的 ndoes 数量：

Then
$$
n(h) = 1 + n(h-1) + n(h-2)
$$
for all h >= 2

因而
$$
n(h) > 2 \times n(h-2)
$$
By induction
$$
n(h) > 2^i \times n(h-2i)
$$
因而 
$$
h < 2 \log n(h) + 2 = \Theta(\log n)
$$


### AVL: insert

AVL tree 的 search 和 sort 就是普通的 BST.

它维持 Height Balance Property 的方法是 insertion 时维持. (以及 remove)

基本 idea: 先正常 insert，然后 rearrange tree to balance height





#### compute `balance`

AVL tree 中的每个元素都 record 其 height.

计算一个 node 的 balance factor:

```c++
balance(n) = height(n->left) - height(n->right)
```

balance = 0, 1, -1 的都是 AVL-balanced node.

|balance| > 1: out of balance



<img src="note-assets/Screenshot 2024-11-17 at 23.48.22.png" alt="Screenshot 2024-11-17 at 23.48.22" style="zoom: 33%;" />





#### rotation

rotation 是一个 local change involving 三个 subtree ptrs 和两个 nodes.



right rotation:

让 left child $L$ and left subtree of $L$ 提到 root 上, 再把原本的 root $V$ 作为它的 right subtree，wtih $L$ 原本的 right subtree 成为 $V$ 的 left subtree

left rotation:

把 right child $R$ and right subtree of $R$ 提到 root 上，再把原本的 root $V$ 作为它的 left subtree，with $R$ 原本的 left subtree 成为 $V$ 的 right subtree

(dually)

容易验证，这保持了 BST 结构.

<img src="note-assets/Screenshot 2024-11-18 at 00.00.51.png" alt="Screenshot 2024-11-18 at 00.00.51" style="zoom:50%;" />

```c++
AVL::Node* AVL::rotate_left(AVL::Node* node) {
    Node *rightchild = node->right;
    Node *rightleftchild = rightchild->left;
    node->right->left = node;
    node->right = rightleftchild;
    fixHeightBelow(rightchild);
    return rightchild;
}

AVL::Node* AVL::rotate_right(AVL::Node* node) {
    Node *leftchild = node->left;
    Node *leftrightchild = leftchild->right;
    node->left->right = node;
    node->left = leftrightchild;
    fixHeightBelow(leftchild);
    return leftchild;
}
```





#### how to keep balance in AVL

到底应该以哪个 Node 为 root 来 rotate 左右 subtree 呢？

冷静分析：

 AVL tree，在插入一个节点前一定保持平衡，

插入一个节点后，它下面的 subtree 的任意节点 balance factor 一定不变，而它的 siblings 以及它们的 subtree 的任意节点的 balance factor 也一定不变。换言之，**balance factor 可能改变以至于不 balance 的只有它到 root 的这段 path 上的节点.** 并且显然，balance 的绝对值至多为 2.

一旦检测到 balance 绝对值为 2，设想这个时候，我们**找到第一个 unbalance 的节点 $V$ ：它的 left, right subtree 不平衡，高度差距 =2. ** 这其中蕴含了一个推论，就是**它的两个 subtree 中至少有一边一定 >= 两层.**

并且，由于之前所有的 node 的 balance factor 绝对值都 <=1，我们知道**这两个 subtree 中长的一边的左右 subtree ($V$ 的subsubtree) 的左右一定从等高变成了不等高，否则之前就不会平衡.** 

所以，这里一定出现了三个高度：

1. $V$ 的短子树，最短
2. $V$ 的长子树的一边子树，其中间
3. $V$ 的长子树的另一边子树，最长

并且注意到，**$V$ 的长子树的两边子树高度差距正好为 1，否则在插入前就不平衡；而 $V$ 的长子树的长子树和 $V$ 的短子树的高度差距正好为 2，导致了这个 imbalance.**

所以只要把这三个树的顺序换一换就好了



#### Four cases of balance = 2 problem

example:

<img src="note-assets/Screenshot 2024-11-18 at 00.16.29.png" alt="Screenshot 2024-11-18 at 00.16.29" style="zoom: 50%;" />

我们发现，一次 rotation 并不能保证解决一切问题. 但是所幸，两次可以解决一切问题。因为一共只有 4 个情况。

我们称为 left left, right right, left right, right left case

LL, RR 最简单. 旋转一次如图.

<img src="note-assets/Screenshot 2024-11-18 at 23.53.13.png" alt="Screenshot 2024-11-18 at 23.53.13" style="zoom:67%;" />

<img src="note-assets/Screenshot 2024-11-18 at 23.53.04.png" alt="Screenshot 2024-11-18 at 23.53.04" style="zoom:67%;" />



LR, RL 旋转两次. (第一次先转换成 LL, RR.)

<img src="note-assets/Screenshot 2024-11-18 at 23.54.08.png" alt="Screenshot 2024-11-18 at 23.54.08" style="zoom:80%;" />





具体的代码：

我们根本不需要在 imbalance 被发现时遍历树来找到第一个 imbalanced node，而是通过 recursion 找到应该插入的点时自动检测 imbalance，而后直接查询是四个情况中的哪一个. 

recursion 是自顶向下的，但是 stack 是自底向上一个一个完成的。insert 的复杂度等于 search，因为它等于我们 search 并在每个 stack 都完成一次 fix_height 和可能 rotate. 这两个行为是 O(1) 的.

search 是 O(log n) 的, insert 等于执行 O(log n) 个 O(1) behavior，是 O(log n) 的.

```c++
AVL::Node* AVL::insert_node(AVL::Node* node, int datum) {
    if (node == nullptr) {
        // at a leaf position in the tree, so create a new node
        return new Node{ datum, 1, nullptr, nullptr }; // it has height 1
    }
  
    if (datum < node->datum) {
        node->left = insert_node(node->left, datum);
        node->fix_height(); // remember to fix the height of a node after modifying its children

       // Left Left Case
        if (node->balance()>1 && node->left->balance() >=0) return rotate_right(node);
        // Right Right Case
        if (node->balance()<-1 && node->right->balance()<=0) return rotate_left(node);
        // Left Right Case
        if (node->balance()>1 && node->left->balance()<0) {node->left = rotate_left(node->left);
            return rotate_right(node);}
        // Right Left Case
        if (node->balance()<-1 && node->right->balance()>0) {node->right = rotate_right(node->right); return rotate_left(node);}
    }
    else {
        node->right = insert_node(node->right, datum);
        node->fix_height(); // remember to fix the height of a node after modifying its children

        // Left Left Case
        if (node->balance()>1 && node->left->balance() >=0) return rotate_right(node);
        // Right Right Case
        if (node->balance()<-1 && node->right->balance()<=0) return rotate_left(node);
        // Left Right Case
        if (node->balance()>1 && node->left->balance()<0) {node->left = rotate_left(node->left);
            return rotate_right(node);}
        // Right Left Case
        if (node->balance()<-1 && node->right->balance()>0) {node->right = rotate_right(node->right); return rotate_left(node);}
    }
    return node;
}
```

















## Lec 19 (Graphs)

graph.  set of a vertices collection and an edges collection.

simple / non-simple ？

(non-simple: 可以有同一个顶点到自己的 edge)

directed / undirected  ？

(directed 的表示方式是一条 edge 的第一个第二个顶点表示顺序)

weighted / unweighted ？

(weighted 的表示方式是 edge 加一个组成部分)





### Complete / Dense / Sparse graph

Complete graph: 每个节点都和其他所有节点 connect，一共有 |V| * |V-1| / 2 等于 |V|*2 - 2|V| + 1 个 edges

Dense graph 和 sparse graph 不是严格的数学概念。

Dense graph 表示 |E| 和 |V|^2 大小差距较小的 graph. Sparse graph 表示 |E| 和 |V|^2 大小差距较大的 graph.

<img src="note-assets/Screenshot 2024-11-24 at 22.55.37.png" alt="Screenshot 2024-11-24 at 22.55.37" style="zoom:50%;" />



区分 dense graph 和 sparse graph 的目的是：**我们通常用 adjacency matrix 来表示 dense graph，用 adjacency list 来表示 sparse graph.** 

adjacency matrix 展现出的是 |V|^2 个 entry，表示每个点和每个点，包括自己和自己之间（容许non-simple）有没有边；可以接受 directed graph，用横竖来表示方向；可以接受 weighted graph，使用其变体 distance matrix. adjacency matrix 的 cost 也大，如果是一个 sparse graph 的话则大部分 entry 都是 0 （distance matrix 的话是 infty）



adjacency list 可以充分且 low cost 地表示 sparse graph. 这是一个





<img src="note-assets/Screenshot 2024-11-24 at 23.00.43.png" alt="Screenshot 2024-11-24 at 23.00.43" style="zoom:50%;" />

<img src="note-assets/Screenshot 2024-11-24 at 23.03.12.png" alt="Screenshot 2024-11-24 at 23.03.12" style="zoom:50%;" />









## Lec 20 (MST)

一个 graph 的一个 minimal spaning tree 就是

















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





















## Lec 21 (Algorithm Family)









## Lec 22 (Backtracking, branch and bound, TSP)















## Lec 23 (DP)













## Lec 24 (Knapsack and Dijkstra's algorithm)











## Lab 10 (DP)











## Lec 25 (Computational geometry)





