









## Lec 17 (Trees)

### Def && Property of trees

两个 equivalent def of trees:

1. 无 cycle 的 connected graph
2. 一个 graph，其中任意两个 node 之间的 paths 都存在唯一的 shortest one. （这个定义和 1 等价，因为这当且仅当没有 cycle. 如果有 cycle, 那么 cycle 之间一定存在两个点，有多个 path 都是 shortest 的）

Properties:

1. **如果一个 tree 有 n 个顶点，那么它一定有 n-1 个 edges.**
   $$
   |E_{tree}| = |V_{tree}| -1
   $$
   这个性质是源于：tree 是一个连通图。

   by induction. 

   base case: 单点图；

   如果要加入一个顶点，那么必须把它连接到当前的图上。所以必须添加 edge.

   但是，由于当前的图是 connected 的，一旦这个新顶点连接了超过一个其他顶点，那么它就会形成 cycle，因为它连接的两个顶点也相互连接了。

   所以，tree 中任意一个新加入的顶点都只带来一条边。

   并且，这条性质还可以用来 decide tree: 

   **一个有 |V|-1 条边的连通图一定是 tree.**

   **其实这三条性质：边数n-1，连通，无环中只要有两条就可以推导出另一条并表明这是一个树**

2. **只要往 tree 中加入任意一条新的边，就会形成 cycle**

   也是 by 连通图的定义

3. **只要在 tree 中去掉任意一条边，就会 disconnect**

4. 每个 tree 都是二分图. （图是二分图当且仅当不包含奇数长度的环

   



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

Dense graph 表示 |E| 和 |V|^2 大小差距较小的 graph. Sparse graph 表示 |E| 和 |V|^2 大小差距较大的 graph (|E| 和 |V| 差不多大).

显然所有 tree 都是 sparse 的，因为 |E| = |V| - 1

<img src="note-assets/Screenshot 2024-11-24 at 22.55.37.png" alt="Screenshot 2024-11-24 at 22.55.37" style="zoom: 33%;" />



区分 dense graph 和 sparse graph 的目的是：**我们通常用 adjacency matrix 来表示 dense graph，用 adjacency list 来表示 sparse graph.** 

adjacency matrix 展现出的是 |V|^2 个 entry，表示每个点和每个点，包括自己和自己之间（容许non-simple）有没有边；可以接受 directed graph，用横竖来表示方向；可以接受 weighted graph，使用其变体 distance matrix. adjacency matrix 的 cost 也大，如果是一个 sparse graph 的话则大部分 entry 都是 0 （distance matrix 的话是 infty）



### Representing a graph: Adjacency matrix

Adjacency matrix 适合用来表示比较 dense 的 graph.（对于 unweighted graph，0 表示无 edge，1表示有 egde；对于 weighted graph，infty 表示无 edge，每个 entry 上表示 edge value）

Space: |V|^2 

查看两个顶点是否有边：O(1)

修改和删除边：O(1)

遍历某个顶点的所有 neighbor: O(|V|)

遍历整个图：O(|V|^2)



<img src="note-assets/Screenshot 2024-11-24 at 23.00.43.png" alt="Screenshot 2024-11-24 at 23.00.43" style="zoom: 33%;" />

<img src="note-assets/Screenshot 2024-11-26 at 20.39.33.png" alt="Screenshot 2024-11-26 at 20.39.33" style="zoom: 33%;" />

#### 在 C++ 中表示 infty

```c++
#include <limits>
double infty = std::numeric_limits<double>::infinity();
```

它和有限非 0 数的任何操作都得到自己

如果使用 VS 的集成编译系统，那么它除以自己得到 1，乘以 0 得到 0，减去自己得到 0

如果自己使用 g++ 编译，那么这三个行为都得到 nan (not a number).



### Representing a graph: Adjacency list

Adjacency list 适合用来表示比较 sparse 的 graph.

它的做法就是建立一个 vector of vectors，第一层数量等于 |V|，每个 vector 都是一个 vertex 的 vertex list

于是：假设 edges 是随机分布的，**每个 vertex 的 vertex list 长度是 O(E/V)**

space 是: O(1+|E|/|V|) for each vertex，**O(|V|+|E|)** 总共（这是显然的因为一共的 entries 数量就是 |E|）

**找到一个 edge 的 time：O(|E| / |V|)**



#### Adajacency list 表示 directed, weighted graph

用 adjacency list 表示 directed graph：很简单，对于 undirected graph，每条边都会在两个顶点的 vertex list 中各出现一次；而对于 directed graph，每条边只会出现在起点的 vertex list.

表示 **unweighted graph：每个 vertex list 是 a list of vertices**；表示 **weighted graph：每个 vertex list 是 a list of pairs，一个 pair 是一个 vertex 和一个表示 weight 的数.**





#### 常见的 Complexity Analysis

1. 查看两点间是否有边

   Matrix: 全部 O(1)，直接 random access

   List: worst O(|V|)，best O(1)，average O(1 + |E| / |V|)，即遍历一个 list

2. 查找离一个点最近的一个点

   Matrix：全部 O(|V|)，找一行

   List：worst O(|V|)，best O(1)，average O(1 + |E| / |V|)，即遍历一个 list



这些是最基本的操作。而我们在图上还有一些常用操作：比如查找最短路径，这是我们在图上最常用的操作

有三个方法：

1. **DFS：只适用于 trees！**在 general 的 graph 上回由于 multiple paths 出现问题
2. **BFS：只适用于 unweighted graph**
3. **Dijstra：广泛适用于 weighted graph**



### DFS 找最短路: 只适用于 tree 性质的图

伪代码：

```
DFS(G):
	mark the root as visited
	push root to stack
	while (stack not empty):
		get and pop top
    for each child of top:
    	if child visited:
    		mark visited
    		push child to top of stack
    		if child is the goal
    			return success
  return failure
```



**DFS 只能找到两个顶点之间的一个 path，但是不保证是什么样的 path**

**如果这个图是一个 tree，那么就可以用 DFS 找最短路，因为任意两个节点之间一定只有一条路，这条路就是最短路**

但是一旦不是 tree，那么找到的 path 就不是最短 path.

方法是把其中一个节点作为 root（recall：tree 中任何节点都可以作为 root！）从它起，深度优先遍历它的所有 subtree，也就是整个 graph



流程：我们放一个 stack，先把作为 root 的起点放进去

while stack 非空：把 top 弹出，top 的所有 neighbor 全部放进 stack

（这样遍历实际上不是一根到底的，而是把 root 所有 children 都放进去，再遍历所有 children 中最右边 children 的所有 chilren，一直遍历到把右节点耗尽，然后从下往上遍历完 root 的最右子树，然后向左传播

time: 

1. for list: O(1 + |E| / |V|) for each vertex list，因而是 **O(|V| + |E|)** 
2. for matrix: O(|V|^2)



<img src="note-assets/Screenshot 2024-11-27 at 19.36.12.png" alt="Screenshot 2024-11-27 at 19.36.12" style="zoom:50%;" />

<img src="note-assets/Screenshot 2024-11-27 at 19.36.33.png" alt="Screenshot 2024-11-27 at 19.36.33" style="zoom:50%;" />



Remember：存一个  parent vector 表示每个 node 的上一个 node 是什么，通过回溯来决定 path 长度



```c++
class GraphMatrix {
public:
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
};
```









### BFS 找最短路: 只适用于 unweighted graph

<img src="note-assets/Screenshot 2024-11-27 at 16.16.02.png" alt="Screenshot 2024-11-27 at 16.16.02" style="zoom: 50%;" />

BFS 的流程和 DFS 的流程唯一的差别是用的是 queue 而不是 stack.

BFS 能够在 unweighted graph 上找到最短路的原因就是：以起点为 root，BFS 每遍历一层，离起点的距离就远了一层。所以第一次找到终点，一定是最短的距离

```c++
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
```

time: 同 BFS

1. for list: O(1 + |E| / |V|) for each vertex list，因而是 **O(|V| + |E|)** 
2. for matrix: O(|V|^2)





### Dijkstra 找最短路

DFS 和 BFS 找最短路本质上都是：遍历图，把找到的第一条路作为最短路。

而它们的限制其实就是在什么情况下它们找到的第一条路就是最短路：DFS 是在只有一条路的情况下，BFS 是在权重全部相同的情况下。这些都是极端情况。

找 single source 最短路的普遍算法是 Dijstra.

Dijstra 可以找到：对于单个 source，其他所有的 nodes 到这个 source 的最短距离



思路：

1. 记一个 distance vector，表示所有 nodes 到 source 的距离

   初始化：dist[source] = 0，dist[其他] = infty

2. 记一个 visited vector，表示哪些端点还没有被 visit 过（visit 指作为主顶点更新和它所有 neighbors 的 min distance）

   一直到所有端点都被 visit 完之前，持续 **visit 当前没有被 visit 过的顶点中 dist 最小的一个，称之为 $u$** ，访问它的所有 neighbors，尝试更新 $u$ 的每个 neighbor $v$ 的 dist 值：经过 $u$ 是否能让它的距离变短？
   $$
   dist[v] = min(dist[v], dist[u] + l(u,v))
   $$

这是一个 greedy 的算法。

```
Dijkstra(G, s)
  for all u ∈ V \ {s}, d(u) = ∞
  d(s) = 0
  R = {}
  while R 6= V
  	pick u not in R with smallest d(u)
  	R = R ∪ {u}
  	for all vertices v adjacent to u
  		if d(v) > d(u) + l(u, v)
  			d(v) = d(u) + l(u, v)
```



#### Proof: Invariant Hypothesis of Dijkstra

Claim:  **每次循环后，如果不是所有的 unvisited nodes 的 dist 都是无穷，那么 unvisited nodes 中 dist 最短的那个一定是最终形态；**

（**因而，我们每次都选择当前 dist 最短的 unvisited node 来 visit，最后一定可以得到所有 nodes 和 source 都是最短距离**）



Base case: source 距离自己的路径长度是 0.

Inductive step: 假设现在所有 visited 的 nodes 的 dist 已经是最终形态，且当前存在dist 非 infty 的 nodes；WTS：目前 unvisited 的 nodes 中当前 dist 最短的 node $u$ 是最终形态

Pf: suppose for contradiction 它不是最终形态

**那么之后存在一条路径达到它，这条路径的距离比更新它的时候检查的所有 neighbors 中转达到它更加短**

关键事实：**这条路径在到达 $u$ 前，要么全部都是当前的 visited nodes，要么存在当前的 unvisited nodes**

case（1）上一个节点是当前的 visited node：由于 visited nodes 的 dist 已经全部 finalize 了，在访问这些 nodes 的过程中已经把它们的 neighbors，包括 $u$ 在内，更新到了当前 visited nodes 能够涵盖的最小。既然这条路所有的 nodes 都 visited 过了，那么这个 path 的长度就是当前的 dist(u). 所以矛盾

case（2）路径上存在至少一个 unvisited node：令 **$v$ 为这条路径上第一个 unvisited node.** 

注意：**决定选择 $u$ 作为准备 visit 的 node 的时候，也查看了 $v$！由于我们选择了 $u$，这个时候从 visit 过的确认是最短路径的任何节点，到其他 unvisited 节点，到 $v$ 要比到 $u$ 更远！** 

那么由于每个 edge 长度都是非负的，从 $v$ 到 $u$ 的这段路径非负，

已知最终的 dist(u) = 当前的 dist(v) + v到u的某段路径，而当前的 dist(v) 又比当前的 dist(u) 大，当前的 dist(u) 比最终的 dist(u) 大。矛盾





下面就是上述的 Dijkstra 的  implementation 

#### Naive Dijkstra

```c++
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
```

复杂度显然是：O(|V|^2 + |E|) 



#### Dijkstra with PQ

由于我们每次都要选取非 infty 的 unvisited 中最短的一个来作为 visited，我们不如建立一个 PQ.

注意到：实际上我们

```c++
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
```







#### Backtracking Dijkstra finding path

这是一个带 backtracking 的 Dijkstra，可以

```c++
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
```



测试:

```c++
int main() {
    int n = 5;
    vector<vector<pair<int, int>>> graph(n);
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
}
```









## Lec 20 (MST)

一个 **weighted undirected connected graph** 的一个 **spanning tree** 就是它的一个 subgraph，其 connect 所有点并且无 cycle（即是一个 tree）

minimal spaning tree 就是它的所有 spanning tree 中总 weights 和最小的 （可以有多个

### Cut Property

Cut Property: **任意地切分一个图（把顶点分为两个集合，其 disjoint union 是整个 V），在 cross 两个顶点集的所有边上，如果其中一条严格小于其他所有边，那么这条边一roof: 个切分，并取它的 crossing edges 中的最短一边。**

假设存在一个 MST，称为 T，不包含这条边 e：

由于 T 是 connected 的，这些边中至少有一条，称为 e' ，在 T 中

by 连通图的性质，**这两个顶点集组成的两个子图都是连通图，所以去掉 e' 加入 e 后仍然是连通的**

于是有
$$
w(T   \backslash \{e\} \; \cup \{e'\}) < w(T)
$$
和 T 是 MST 矛盾了 

#### Corollary: shortest edge for one vertex must be in all MST; in some if unstrict

对于任意一个 edge，我们都可以把它和其他所有顶点分为两个 subgraph（单点集和其他所有点的子图）

所以 by cut property，任意一个顶点 associated 的所有 edges 中如果存在严格最短的，那么这条 edge 一定在所有 MST 中

类似逻辑可证明：**任意一个顶点 associated 的所有 edges 中如果存在多个最短的，那么它们都各自在某个 MST 中.**





（Trivial Collary: Cycle Property

于图中的任意 cycle，如果其中的一条边比 cycle 中的其他边都严格长，那么它一定不在任何 MST 中。This is trivially true.）



### Prim's Algorithm: Using Cut Property















### Minimum-cost egde property

如果 graph 中 minimum cost 的 edge 是 Unique 的，那么它一定在任何 MST 中

proof: 假设存在一个 MST 没有这一边，那么把它放进 T 中 形成一个循环，去掉任意一个其他边仍然是一个 tree



#### Corollary: sorting property

对一个 connected graph 的所有边长**进行排序，前 k 个不形成 cycle 的 edges 一定是某个 MST 的 subgraph**。

（因而，前 |V| -1 个不形成 cycle 的 edges 一定一个 MST.）

proof: 

Proof by induction.

Base case: k = 0. 

Inductive step: 假设 $e_1, ..., e_{k-1}$ 是某个 MST $T$ 的 subgraph，并且 e_k 是接下来的最小且和 $e_1, ..., e_{k-1}$ 不形成 cycle

那么我们看向 $T$：把  $e_k$ 加入到 $T$ 中形成了一个 cycle，于是把其中一个边去掉又是一个 tree. 由于有其他边长都大于等于 $e_k$，那么一定可以用 $e_k$ 来替换这个边



实际上我们可以这么想：

一个 spanning tree 是由一个点作为起点，每加入一条边就是新加入一个顶点。加入 $|V|-1$ 次就结束了

因而当我们固定起点，其实**每个新加入的顶点都 associate 了它被加入时的边。**

MST 就是让加入每个顶点时它 associate 的边尽量最短

我们**选择一个加入后不形成 cycle 的边，其实就是加入一个新的顶点。**

我们把所有边都排序好，**选择前 $|V|-1$ 个最短的不形成 cycle 的边，就是加入 $|V|-1 $ 个其他顶点，并且确保它们的 weights 总和达到最小**. 任何其他选择都只不过是换一换两个点加入的顺序和它们加入时 associate 的边，但是这个选择一定不会比我们通过排序获得的选择更好。



### Krustal's Algorithm: Using sorting property

 













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





