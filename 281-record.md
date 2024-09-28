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



## Lec 6 - Arrays & Containers

#### 2D dynamic array with double ptr

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

