# 281-record

## Lab 1

### Lab 流程

发现其实很简单：

1. 在 lab 上做好 notes 并完成手写

2. 在 lab 后直接 assignment pdf，一步一步做就可以。其中一部分是 quiz 一部分是 autograder.

### 关于 CAEN

直接在 VSCode 里打开

```sh
ssh rynnefan@login.engin.umich.edu
```

连接到 remote 服务器，我自己的 remote 文件夹。VSCode 有一个非常人性化的点是会记得 remote 文件夹。打开了一次 lab1 之后下次打开 VSCode Remote 就有一个通往这个 /home/rynnefan/eecs-281/lab1 的快捷方式了。

我们的东西必须兼容 CAEN 的环境才能得分。其实并不是一个必要的事情，因为远程 linux 和本地 linux 差别不大。但是这样的好处就是在 mac 上我也可以编辑用 linux 环境了。

在本地运行，把本地的文件夹一整个复制到 remote 的一个文件夹中。：

```sh
scp -r ../auto-Music-Sorting rynnefan@login.engin.umich.edu:/home/rynnefan/eecs-281/lab1
```

如果要传回本地就倒过来，在本地运行:

```sh
scp -r rynnefan@login.engin.umich.edu:/home/rynnefan/eecs-281/lab1/example-Perf ~/desktop
```



如果只要复制一个文件就去掉 `-r`.

这个东西麻烦就在于不能使用 rsa免密。。。。每次连接远程都需要输入密码

### Mac mission control

F3 直接打开 mac mission control 来控制桌面会快很多。。

### Makefile

看起来很长但其实只要做四件事情：

1. 根据 spec 更改 `IDENTIFIER`
2. 根据 spec 更改 `EXECUTABLE` 
3. 把 `PROJECTFILE` 更改成有 main 函数的那个 cpp 文件（直接把 main 放在 EXECUTABLE 同名 cpp 里就可以）
4. 更改 dependency 

### Perf

Perf 是一个 linux 系统的 profiling tool. 

必须要 -g3 flag 才可以运行。不过我们的 Makefile 的 debug 模式已经加上了。

所以先 make debug：

```sh
make debug
perf record -F 1000 --call-graph dwarf -e cycles:u ./executable_debug
perf report
```

用 symbol 表示只显示用户程序中的库和符号

```sh
perf report --sort symbol
```

### Valgrind

Valgrind 可以检测未初始化的变量；out of bound 的读写；memory leak；

并且可以 memory profiling.

运行十分方便。

```sh
make valgrind
valgrind ./executable_valgrind
```

用 more 指令可以让结果分页，这样不会刷屏。more 模式下，空格进入下一页，enter进入下一行

```sh
valgrind ./exeutable_valgrind |& more
```

### `vector::reserve`

如果你试图向 `vector` 中插入超过 `capacity()` 的元素，那么 `vector` 会进行内存重新分配。

`reserve` 只是增加了 `vector` 的容量（即 `capacity()`），但不会增加或减少 `vector` 中的元素。如果提前 reserve，那么当 `vector` 的元素数量达到预留的容量时，不会触发内存重新分配操作，避免性能上的开销。

### 一个冷知识: C++并不支持 `int x,y = 1` 的 initialization syntax

```
int x, y = 1;
```

In this case, only `y` is initialized to `1`, while `x` remains uninitialized. 

但是可以:

```
int x=1, y=1;
```

### `getopt_long`

```c++
{"level", required_argument, nullptr, 'l'}
```

`required-argument` 表示如果加了这个 option 必须带参数；`option-argument` 表示这个 option 可以不带参数; `no_argument` 表示这个 option 并没有参数.

(`nullptr`) is used to indicate there’s no flag variable associated with this option (or another specific value can be used if a variable is needed).

`l` 是这个 option 的简写.

```c++
    while ((option = getopt_long(argc, argv, "p:h", longOpts, &option_index)) != -1) {
        switch (option) {
            case 'p':
                //...
         		case 'h':
            		//...
```

其中 `p:h` 表示所有的选项。 一个选项之后的冒号取决于：

- **无冒号**：``no_argument``，选项不接受参数。例如，`p` 表示选项 `-p` 不需要任何参数。
- **一个冒号 (`:`)**：`required-argument`， 选项 **必须** 带有一个参数。例如，`d:` 表示选项 `-d` 需要一个参数。
- **两个冒号 (`::`)**：`option-argument`，选项的参数是 **可选的**。例如，`o::` 表示选项 `-o` 可以有一个参数，但它是可选的。



## Lec 2

### heap

heap 是一种树形数据结构，分为 max_heap 和 min_heap. 

**最大堆（Max Heap）**：在最大堆中，每个节点的值都大于或等于其子节点的值。因此，根节点始终包含整个堆中的最大值。

**最小堆（Min Heap）**：在最小堆中，每个节点的值都小于或等于其子节点的值。因此，根节点始终包含整个堆中的最小值。

       10
      /  \
     5    3
    / \  / \
    4  1 2  0
    //max heap
c++ 具有 built-in 的 make_heap 函数，对于所有支持 random access 的 container 都可以使用，`make_heap()` 是一种排序方式，允许你**使用自己定义的比较函数来对一个 container 进行 heap 排序.**

三个参数： container 的 begin(), container的 end() 以及比较函数。第三个参数可以忽略, for built in data 

```c++
#include <iostream>
#include <vector>
#include <algorithm>  // 包含 heap 操作的函数
struct Task {
    int id;
    int priority;
    Task(int id, int priority) : id(id), priority(priority) {}
};
// 比较函数，定义最小堆的排序规则
bool compareTasks(const Task& t1, const Task& t2) {
    return t1.priority > t2.priority;
}
int main() {
    std::vector<Task> tasks;
    tasks.emplace_back(1, 10);
    tasks.emplace_back(2, 5);
    tasks.emplace_back(3, 20);
  
    // 创建最小堆
    std::make_heap(tasks.begin(), tasks.end(), compareTasks);
  
  	// 新加入元素, 重新调整堆.
  	v.push_back(25);
    std::push_heap(v.begin(), v.end()); // 重新调整堆
  
  	std::cout << "Tasks in heap order:" << std::endl;
}
```

### vector/deque + `make_heap` 实现Priority Queue

PQ 的 underlying container 是赋予 heap 性质的 vector

```c++
class PriorityQueue {
public:
    // 插入元素到堆中，并调整堆结构
    void push(Task element) {
        data.push_back(element);           // 插入到 vector 的末尾
        std::push_heap(data.begin(), data.end(), comp); // 调整堆结构（上浮）
    }
    // 删除堆顶元素，并调整堆结构
    void pop() {
        std::pop_heap(data.begin(), data.end(), comp); // 最大元素放到末尾
        data.pop_back();                        // 删除末尾元素
    }
    
    T& top() const {return data.front();}
    bool empty() const {return data.empty();}
  	sizer_t size() const {return data.size();}

private:
    std::vector<Task> data; // 用于存储堆的 vector 
  	Compare comp; // 比较函数
};
```

### 使用 stl built-in 的 PQ

三个参数，一个是 data type，还有两个可选，一个是想要用什么 container（默认vector），一个是比较函数（默认从大到小比较 built-in data type）.

```c++
std::priority_queue<Task, std::vector<Task>, CompareTask> queue;
```

## Lec 3

### Amortized complexity

我们知道 resize vector 的 complexity 是 O(n)，而平时的 push 操作则是 O(1). 但是对于一个 linear growth 的 vector，通常每当我们 push O(n) 个元素，才会 resize 一次.

我们可以把一系列操作 amortize(摊销) 来获得“这一系列操作的平均 complexity".

比如 linear growth 的 vector 的 "push" 这一操作的 amortized complexity 是 
$$
\frac{O(n) + n \cdot O(1)}{n} = O(1)
$$
的 amortized cost.

但是 constant growth 的 vector 则是：

假设 vector 每次 grow const $c$ 个单位

那么 constant growth 的 vector 的 "push" 这一操作的 amortized complexity 是 
$$
\frac{O(n) + c \cdot O(1)}{c} = O(n)
$$
这就是为什么我们通常采取 linear growth 而不是 const growth.



## Project-1

最大的问题就是 memory 优化的问题。time 反而还好

这次的经验：

### test files

1. 起步写 test files. 本质上刚刚写完一初稿就应该直接写三四个 test files 尽力把 bug 都找到了，并且其实简单的。不用大型的 tests，只需要吧本质的情况变化拉出来就可以了。然后一直修改直到跑过了自己所有的 test files，这个时候跑 sample 的大型 files 基本也是对的，可以跑一下做确认然后直接提交，之后就是优化的事情了。所以 281 本质上不算复杂，完全可以 module development。

### Memory 优化





### Time 优化

1. 读数据：通常情况下直接  `>>` 是比使用 `getline` 要快的。getline 本质上是一个比直接 stream 移动复杂一点的方法。但是！有时候

### 发现的一些 WSL 上好的 GUI

`nautilus` 文件管理系统

`xeyes` 一个好玩的眼睛追踪器

`chromium-nbrowser` 开源浏览器


## Lec 5 - Recursion

### Fourth Condition of Master Thm

我们知道 master thm apply to:
$$
T(n) = aT({n \over b}) + f(n) \;\;, f(n) \in \Theta(n^c)
$$
直观上 a 越大，b 越小，f(n) 越大则 $T$ 越大. 可以得到:

如果 $a > b^c$，那么  $a,b$ 的组合 dominate， $T(n) \in \Theta(n^{\log_b a}) $

如果 $a = b^c$，那么 $a,b$ 的组合和 $f$ 同时 take dominance，$T(n) \in \Theta(n^c \log n)$

如果 $a < b^c$，那么 $f$ take dominance，$T(n) \in \Theta(n^c)$



使用的条件比较严格。for ex: $T(n) = T(n-1) + n$ 就无法使用，需要手动归纳，结果是 $\Theta(n^2)$.



但是如果 $f(n) \in \Theta(n^{\log_b a} \log^k n)$ 时是一个特殊情况，称为 fourth condition，此时可以直接得到 $T(n) \in \Theta(n^{\log_b a} \log^{k+1} n)$.

比如 $T(n) = 2T({n \over 2}) + n \log n$，那么 $T(n) = \Theta(n \log^2 n)$



#### **Algorithm Problem: 2D table search**

在一个 row, col 都 ordered 的 2D table 中 找到一个元素：

<img src="note-assets/{5E9B3521-4665-444A-95A3-8DCA56A3A9E2}.png" alt="{5E9B3521-4665-444A-95A3-8DCA56A3A9E2}" style="zoom:75%;" />

普通算法：$O(n^2)$

我们可以使用 Binary Partition 来进行 $O(n)$ 的搜索.

1. 把 table 差不多均分分成四块（多一个行少一列没关系）
2. binary search 中间列，看要搜索的元素的大小在哪两个元素之间
3. 可以排除掉四块中的两块。recursion

$T(n) = 2T({n\over 2}) + c \log n = O(n)$

## Lec 6 - Arrays & Containers

### 2D dynamic array with double ptr

```c++
size_t rows, cols, r, c;
int **a = new int *[rows];
for (r = 0; r < rows; ++r)
    a[r] = new int[cols];

for (r = 0; r < rows; ++r)
    for (c = 0; c < cols; ++c) 
        a[r][c] = 0;
```

### Pros and Cons of fixed/dymc array

Fixed array is allocated on the stack.

Pros:

1. 出 scope 时自动被 deallocated
2. **`a[i][j]` 只使用一次 Memory operation 而不是两次（连续 Memory）**

Cons:

1. 无法 work for large size，stack 太小
2. size fixed
3. 作为参数传给函数会有问题。会自动转成ptr，容易越界访问.



Double pointer dynamic array is allocated on the heap.

Pros:

1. 支持 **triangular arrays.**
2. 可以 copy 以及 swap rows quickly (one operation)
3. size 可变

Cons:

1. `a[i][j]` random access 略慢一些
2. 有 leak memory 的风险

#### C++11 range-based for loop

```c++
for (int &item: my_array)
    item *= 2;

for (int i = 0; i < 5; ++i)
    my_array[i] *= 2;
```

time / memory 和语义完全一样. 

记得要加 reference for range based.



#### **Algorithm Problem: Finding the majority element**

如果一个 array 中有一个 element 数量超过 50%，可以通过 Moore's voting algorithm 找到它：

Idea: 

- variable `string candidate`, `int count`
- Traverse the array once:
  - If  `count` = 0, set `candidate`  to the current element and set `count` to one.
  - If the current element 是 `candidate`，则 `count++`
  - If the current element 不是 `candidate`，则 `count--`

这个 算法利用了这个元素数量过半的特点，达到了 $O(n)$ time 和 $O(1)$ space.

```c++
int majorityElement(const vector<int>& arr) {
    int n = arr.size();
    int candidate = -1;
    int count = 0;

    // Find a candidate
    for (int num : arr) {
        if (count == 0) {
            candidate = num;
            count = 1;
        } else if (num == candidate) {
            count++;
        } else {
            count--;
        }
    }

    // Validate the candidate
    count = 0;
    for (int num : arr) {
        if (num == candidate) {
            count++;
        }
    }

    // If count is greater than n / 2, return the candidate; otherwise, return -1
    if (count > n / 2) {
        return candidate;
    } else {
        return -1;
    }
}
```



如果这个元素的数量并不过半，而是要找到最多的元素，那么只能用 hash map， $O(n)$ time 和 $O(n)$ space.

```c++
int majorityElement(const vector<int>& arr) {
    int n = arr.size();
    unordered_map<int, int> countMap;

    // Traverse the array and count occurrences using the hash map
    for (int num : arr) {
        countMap[num]++;
      
        // Check if current element count exceeds n / 2
        if (countMap[num] > n / 2) {
            return num;
        }
    }

    // If no majority element is found, return -1
    return -1;
}
```





### Containers

Containers: 

vectors, lists, stack, queue, map, heaps, trees & graphs,...

需要能够 copy/edit/sort/order many objs at once.

containers within containers 用以 implement complex data structures. 比如 Database 也是一种 container.



**accessing container items 的方法：**

1. sequential

   Find n-th item by 从头开始增加 index n 次达到 n-th item 的位置.

   Used by disk in computers, slow

2. random access

   go directly to n-th item

   Used by main memory in computers (LDUR, SDUR, ...), fast

#### 使用 double ptr instead of random access to traversal

```c++
const size_t SIZE = 4;
double src_ar[] {3,5,6,1};
double dest_ar[SIZE];

// with no ptr
for (size_t i = 0; i < SIZE; ++i)
  dest_ar[i] = src_ar[i];

// with double ptr: faster
double *sptr = srca_ar;
double *dptr = dest_ar;

while (sptr != src_ar + SIZE)
  *dptr++ = *sptr++;
```

好处是使用 1 次 sequntial access 而不是 n 次 random access，速度更快.

random access 的时间消耗相比 dereference 要大。使用 1 次 sequntial access 比 1 次 random access 耗时大，但使用 1 次 sequntial access 比 n 次 random access 耗时显著小。所以如果要 traversal 应该使用 double ptr.

#### What to Store/Get in a container

Store:

1. Value: **最常用**. 只有 container 可以 edit，安全. 但是缺点是 copy large objects 行为 costly

2. ptr: copy objects 速度快，但是 unsafe，因为其他 object 也可以修改 container 里面的 objects. 且容易造成 double delete.

   defensive programming tip: 使用 `ptr = nullptr;` after `delete ptr;`

3. reference：无法 delete by reference，不实用.

Get:

1. Value: copy large objects 行为 costly.
2. Ptr: unsafe， ptr may be invalid
3. Reference:  **good choice**，尤其是 const ref if 不想 edit.



#### Use dynamic array in C++

`new[]` 在 heap 中生成一个 array 并对其中每个 object call default ctor

`delete[]` 对 array 中每个 object call tor.

```c++
class Array {
  size_t length = 0;
  double *data = nullptr;
  
  public:
  Array(size_t len) : length{len};
  								data{new double[length]} {} // dynamic array
  
  ~Array() {
    delete[] data;	//delete dynamic array
    data = nullptr;
  }
}
```



### Best deep copy 方法：copy-swap method

普通方法：在 operator= 中，先 `delete[] data;` 然后 `data = new double[length];` 然后 loop 进行 deep copy.

Copy-swap method: 

```c++
#include <utility> //为了使用 std::swap

Array(const Array &other) : Length{other.length},
														data{new double[length]} {
	for (size_t i = 0; i < length; ++i)
    data[i] = other.data[i];
}

Array &=operator=(const Array &other) {
  Array temp(other);	//temporary object
  
  // assign by swap, 原 object 数据和 temp 交换
  std::swap(length, temp.length);
  std::swap(data, temp.data);
  
  return *this;	//temp out of scope 自动被 dtor 掉
}
```

这个方法去除了 explicit deallocation in the assignment operator，同时很好地处理了 Self-Assignment Handling. 



### C++11: Move ctor for r-value

Big 5 for using dynamic memory

1. dtor
2. copy ctor
3. `operator=()`
4. **copy ctor from r-value**
5. **`operator=()` from r-value**



在 C++11 中，"copy constructor from r-value" 通常指的是 **Move Constructo**

当被 copy 的 obj 是一个右值（r-value）时，可以减少不必要的 deep copy

- 在 C++ 中，**左值（l-value）**是指有名字并且持久存在的对象，而**右值（r-value）**是临时的、不持久的对象。
  - **左值（l-value）**：像变量 `int a = 5;` 中的 `a` 是一个左值，因为它有一个名字且在作用域内持续存在。
  - **右值（r-value）**：像表达式 `5` 或者函数返回的临时对象 `a + b` 是右值，它们的生命周期很短，只在语句中使用时存在。

在 C++11 之前，所有的复制操作都只能通过  copy ctor 来完成，

 对于短生命周期的临时对象，deep copy 会增加不必要的 cost.

为了更好地处理这种情况，C++11 引入了
1. **Move Constructor**：用来从右值中“移动”资源，而不是复制。
2. **Move `operator=()`**.



move ctor 的参数是一个右值引用（r-value reference），即使用 `&&` 来表示。例如：

```cpp
Array(Array &&other) noexcept {
    length = other.length;
    data = other.data;
    other.length = 0;
    other.data = nullptr;
}
Array& operator=(Array &&other) noexcept {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = other.data;
        other.length = 0;
        other.data = nullptr;
    }
    return *this;
}
```

- **右值引用 (`Array&& other`)**：`&&` 表示一个右值引用，可以绑定到一个右值（例如临时对象）。
- 在移动构造函数中，我们**直接接管**了右值 `other` 的资源：
  - `data = other.data;`：把 `other` 的指针直接赋值给当前对象，而不是进行深拷贝。
  - `other.data = nullptr;`：将 `other` 的指针置为 `nullptr`，表示它不再管理这块内存。
  - 这样，数据的所有权被转移，而不是拷贝，极大提高了效率，尤其是对于大规模数据对象。

使用例：

```c++
Array createArray(size_t len) {
    return Array(len); // 返回一个临时对象 (r-value)
}

int main() {
    Array a(5); 
    Array b = a; // deep copy

    Array c = createArray(10); // 使用 move ctor

    Array d(3);
    d = createArray(15); // 使用 move opertor=

    return 0;
}
```

#### Move syntax 的好处

c++11 之后：

```c++
vector<string> readData() {
    vector<string> data;
    string temp;
    while (cin >> temp)
        data.push_back(temp);
    return data;  
} // data 返回时不会被 copy 而是 move 到左边的 object 上, 节省 time
```

(Note: vector 是在 heap 上的，相当于 dynamic array)

函数返回的 data 是临时对象，是一个 r-value. 返回时会直接 move 到左边的 vector 上而不会 deep copy. 节省了 deep copy 的 time.



### Array class operation: `[]` 和 `insert`

对于 `[]` 我们需要一个 const version 和一个 nonconst version. compiler 会自行选择. 

const version 可以 **help compiler optimize code for speed.**

```c++
double &operator[](size_t i) {
  if (i < length)
    return data[i];
  throw runtime_error("bad i");
}

const double &operator[](size_t i) const {
  if (i < length)
    return data[i];
  throw runtime_error("bad i");
}

// const 的参数，compiler 会自动选择 const 的 operator
ostream &operator<<(ostream &os, const Array &a) {
  //...
}
```



Insert:

```c++
bool Array::insert(size_t index, double val) {
  if (index >= length)
    return false;
  for (size_t i = length - 1; i > index; --i)	//at most n-1 times
    data[i] = data[i-1];
  data[index] = val;
  return true;
}
```

会向右 shift 整个 array 一格.

## Lec 7 - STL



## Lec 8 - Heap & Heapsort





## Project 2A: Stock Market

Your program market will receive a series of “**orders**,” or intentions to buy or sell shares of a certain stock. An order consists of the following information:

- Timestamp - the timestamp that this order comes in
- Trader ID - the trader who is issuing the order
- Stock ID - the stock that the trader is interested in
- Buy/Sell Intent - whether the trader wants to buy or sell shares
- Price Limit - the max/min amount the trader is willing to pay/receive per share
- Quantity - the number of shares the trader is interested in

As each order comes in, your program should see if the new order can be matched with any previous orders. A new order can be matched with a previous order if:

- Both orders are for the same stock ID
  - Trader ID does not matter; traders are allowed to buy from themselves.
- The buy/sell intentions are different. That is, one trader is buying and the other trader is selling.
- The selling order’s price limit is less than or equal to the buying order’s price limit.

A buyer will always try to buy for the lowest price possible, and a seller will always try to sell for the highest price possible. Functionally, this means that whenever a possible match exists, it will **always** occur at the price of the *earlier* order. When trying to match orders, use priority queues to identify the *lowest-price* seller and the *highest-price* buyer.



If the SELL order arrived first, then the price of the match will be at the price listed by the seller. If the BUY order arrived first, the match price will be the price listed by the buyer.

In the event of a tie (e.g. the two cheapest sellers are offering for the same price), **always match using the order that arrived earliest.**
