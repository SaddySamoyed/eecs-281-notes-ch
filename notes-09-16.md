## Lec 9 - ordered & sorted containers

### Types of Containers

container: 可以 `add`, `remove` 

searchable container: 可以 `find` 的 container

sequential container: 可以 iterate over elements 的 container

ordered container: elements 的顺序**通过它们被加入的顺序来决定**的 sequential container（比如 stack, queue...)，但是可以 **arbitrarily insert 元素到任意位置**

sorted container: 有 pre-defined order 的 container，不可以 arbitrarily insert 元素，**只能 add/remove 到 pre-defined order 的位置上** （比如 PQ



implement sorted/ordered container 的两种 style: connected 或者 contiguous，典型的是 underlying d.s. 是 linked list / array

 

### Complexities of array/list based

For ordered container:

(add 的复杂度是 $O(1)$, 因为直接加在最后）

|                      | array-based | link-list-based |
| -------------------- | :---------: | :-------------: |
| add                  |      1      |        1        |
| remove(val)          |      n      |        n        |
| **remove(iterator)** |    **n**    |      **1**      |
| find(val)            |      n      |        n        |
| op*                  |      1      |        1        |
| **op[]**             |    **1**    |      **n**      |
| **insert**           |    **n**    |      **1**      |

For sorted:

（add 的复杂度是 n, 因为先要找到应该加入的位置）

|                      | array-based  | link-list-based |
| -------------------- | :----------: | :-------------: |
| add                  |      n       |        n        |
| remove(val)          |      n       |        1        |
| **remove(iterator)** |    **n**     |      **1**      |
| **find(val)**        | **$\log n$** |      **n**      |
| op*                  |      1       |        1        |
| **op[]**             |    **1**     |      **n**      |

从 ordered 到 sorted container，除了 add 变了外唯一的区别是 array_based 的 `find(val)`  复杂度降了，因为可以在 contiguous 的内存上使用 Binary search. 

所以对于 sorted 的 container，使用 array instead of list 作为 underlying d.s. 在 find 上有额外的好处. 



### Binary Search

$O(n \log n)$

#### Binary Search on array

```c++
int bsearch(double a[], double val, int left, int right) {
    while (right > left) {
        int mid = left + (right - left) / 2;
        if (val == a[mid])
            return mid;
        if (val < a[mid])
            right = mid;
        else
            left = mid + 1
    }
    
    return -1; // not found
}
```

#### Speed up BS

我们知道 `==` 是 rarely happen 的. 

所以把 `==` 放到 else 上，先check <，然后 check >

```c++
int bsearch(double a[], double val, int left, int right) {
    while (right > left) {	//comp1
        int mid = left + (right - left) / 2;
        
        if (a[mid] < val)	//comp2
            left = mid + 1
        else if (val < a[mid])	//comp3(only halfs the time)
            right = mid;
        else
            return mid;
    }
    
    return -1; // not found
}
```



#### `lower_bound()`, `upper_bound()`

一个更快的 version: 总是只有两次 comp，但是无法检测 value 不在 array 里的情况.

```c++
int lower_bound(double a[], double val, int left, int right) {
    while (right > left) {	//comp1
        int mid = left + (right - left) / 2;
        
        if (a[mid] < val)	//comp2
            left = mid + 1
        else
            right = mid;
    }
    
    return left
}
```

所以称之为 **lower_bound.** 会**返回 array 里第一个大于等于 target 的 item.** （不论 value 在不在 array 里.）

dually 我们还有 upper_bound 函数.

以及 equal_range，检测一段范围里是否所有 items 都有等于 target.



### Representing sets

我们可以让一个 container 拥有 set 的性质，if

我们需要 union, intersect, difference 和 symmetric difference

以及添加 element, 去除 element, 判断是否是 element 的运算.



