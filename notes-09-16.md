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

|                      | array-based |       link-list-based       |
| -------------------- | :---------: | :-------------------------: |
| add                  |      1      |              1              |
| remove(val)          |      n      |              n              |
| **remove(iterator)** |    **n**    | **n (1 for doubly linked)** |
| find(val)            |      n      |              n              |
| op*                  |      1      |              1              |
| **op[]**             |    **1**    |            **n**            |
| **insert**           |    **n**    | **n (1 for doubly linked)** |

For sorted:

（add 的复杂度是 n, 因为先要找到应该加入的位置）

|                      | array-based  |       link-list-based       |
| -------------------- | :----------: | :-------------------------: |
| add                  |      n       |              n              |
| remove(val)          |      n       |              1              |
| **remove(iterator)** |    **n**     | **n (1 for doubly linked)** |
| **find(val)**        | **$\log n$** |            **n**            |
| op*                  |      1       |              1              |
| **op[]**             |    **1**     |            **n**            |

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

我们可以让一个 container 拥有 set 的性质：需要 union, intersect, difference 和 symmetric difference

以及添加 element, 去除 element, 判断是否是 element 的运算.



`std::set_union` 依赖于 sortedness. 对于两个 set （或者任意储存同种数据类型的 container），它可以在某段范围上实现 set union 的效果.

```c++
template<class ForIterator1, class ForIterator2, class OutIterator, class Compare>
OutIterator set_union(ForIterator1 first1, ForIterator1 last1,
                      ForIterator2 first2, ForIterator2 last2,
                      OutIterator result, Compare compare) {
    while (first1 != last1 && first2 != last2) {
        if (compare(*first1, *first2)) {	//compare 返回的是 (x<=y)
            *result++ = *first1++;  // set1 element less than set2 element
        } else if (compare(*first2, *first1)) {
            *result++ = *first2++;  // set2 element less than set1 element
        } else {	//else: 两个元素相等, both index++
            *result++ = *first1++;
            ++first2;
        }
    }
  	// get remainings elements
    while (first1 != last1)
        *result++ = *first1++; 
    while (first2 != last2)
        *result++ = *first2++; 
    return result;  // sorted union of set1 and set2
}
```



#### Complexity of set operations

Initialize: $O(1)$ 如果 unsorted；$O(n\log n)$ if sorted（需要排序）;

clear: $O(n)$ 

isMember: $O( \log n)$ ，需要binary search

copy: $O(n)$，即和空集 union

union, intersect：$O(n)$



## Lec 10 Sorting

Elementary sorts:

1. bubble sort
2. selection sort
3. insertion sort
4. counting sort (限于 int)

High performance sorts:

1. quicksort
2. mergesort
3. heapsort
4. radix sort (限于 int, char*, ...)



Array 和 Linked lists container 都可以被 sort. 并且同一个 method 对 array/linked list 的 sorting performance 会不一样.

STL sorting based on iterators。我们这里只用 array 和 indices 来举例。



## Lab 5 (Sorting)

#### Algorithm Problem: sort 一个 0,1,2 组成的 vector, O(n) time, O(1) space

我用两个 index i = 0,j = n 来追踪首末的位置，每次监测到0就和 v[i] 交换上并且 i++，检测到 2 就和 v[j] 交换并且 j++. 这样最后所有 0 都在前面，所有2都在后面，中间一定都是1

Note: 用来存 lowindex 的变量和用来 iterate 的变量必须区分开，否则有 bug. 所以是三个变量

```c++
void sort012(vector<int>& nums) {
    int low = 0, scan = 0;
    int high = nums.size() - 1;

    while (scan <= high) {
        if (nums[scan] == 0) {
            std::swap(nums[low], nums[scan]);
            low++;
            scan++;
        } else if (nums[scan] == 2) {
            std::swap(nums[high], nums[scan]);
            high--;
        } else {
            scan++;
        }
    }
}
```
