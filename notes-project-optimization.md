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





## Project-2A Stock Market Simulation 

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

### CML

四个 no argument: v, m, i, t		

v: 需要 generate verbose output 

m: 需要 generate median output

i: 需要在 output 中包括 trader details

t: 需要生成 time traveller 的 output.



### Market Logic

market 会受到一系列 Orders. 一个 Order 就是一个 buy/sell 某个 stock 的 shares 的 request. 由下面六个变量组成：

1. timestamp: order 时间
2. trader ID: 谁发起的
3. Stock ID: 买卖哪个 stock
4. Buy/sell ? 
5. trader 愿意 pay/receive 的 Max/min price per share
6. quantity of shares

对于每一单，我们都 check 这个 new order 是否 match 某个 previous order

match 条件：

1.  same stock ID，一个 Buy 一个 sell
2.  seller 愿意收的 min price <= buyer 愿意出的 max price （我们使用PQ 来 match 最低的 seller 和最高的 Buyer）

match 后交易价格：

如果是 seller 先到，出价是 seller 列出的 limit (最低价)，因为 buyer 想用最低的钱来买；如果是 buyer 先到，出价是 buyer 列出的 limit (最高价)，因为 seller 看到之后想赚尽可能多的钱

match 并交易完之后，大概率一方的需求没有耗尽，继续留在队伍里



### Output

Processing orders...

。。。

启动v 则 Trader <BUYING_TRADER_NUM> purchased <NUM_SHARES> shares of Stock <STOCK_NUM> from Trader <SELLING_TRADER_NUM> for $<PRICE>/share

启动 m 则Median match price of Stock <STOCK_ID> at time <TIMESTAMP> is $<MEDPRICE> （**If no trades have been made for a given stock, it does not have a median, and thus nothing should be printed for that stock’s median**）

---Trader Info---
Trader 0 bought 0 and sold 2 for a net transfer of $166

Trader 1 bought 63 and sold 0 for a net transfer of $-5359

Trader 2 bought 24 and sold 85 for a net transfer of $5193

...

---End of Day---
Trades Completed: <TRADES_COMPLETED><NEWLINE>



### 数据结构

```c++
priority_queue<int, vector<int>, greater<int>> pqMin;`
```

我们需要一个 Stock class

对于每个 stock 我们都需要一个  buyer PQ，一个 seller PQ

我现在要使用 priority queue 来表示一个 stock 的运行情况。对于一个 stock, 我设置两个 PQ: 一个是 buyer PQ，一个是 seller PQ。于是，每一次我读入一个 Order 时，如果是 buyer 我就把它和 seller PQ 里面的 orders 尝试 match，如果是 seller 我就把它和 buyer PQ 里面的 orders 尝试 match.  

buyer 是按照愿意出的最高价排队的，seller 的价格是愿意卖的最低价。

所以对于一个 seller order，我们只需要看 Price 最高的 buyer 就可以，如果 price 最高的 buyer 的 price 都不合想法，那么下面肯定也不合，直接入队了。所以 buyer PQ 是一个 max heap

对于一个 buyer order，我们只需要看 price 最低的 seller 就可以，如果 price 最低的 seller 的 price 都不够低那么下面就更低。seller PQ 是一个 min heap

**对于一个 match: 不论 current 是 buyer 还是  seller，都是按照 PQ 里 top 弹出来的价格进行交易，为了自身利益最大化。**



且 Issue 2：怎么确定 PQ 的 priority：在价格相同时，选择 eariler one

这个就是 comparator 的问题。comparator 应该首先考虑价格，不等时再比较时间



match:  buyer: .price >= top.price.

seller: price <= top.price



所以整体逻辑：

1. 查看 PQ top

2. match 则交易，不 match 则入队\

   while (和 top match && current.quantity != 0)

   {

   ​	比较 quantity, 

   如果 current 的 quantity >= top.quantity, 那么 top 被 pop，current 的 quantity -= top.quantity; 

   如果 current 的 quantity < top.quantity，则 current.quantity = 0， top 的 quantity -= current.quantity

   }

   如果 current.quantity = 0，continue

   否则 current 入队。





我们先做一个 4 个 mode 都不开的。这个今天 finish 掉了

明天的任务是：finish 掉正式的 version 的初稿，写一点 test case；起步 PQ

以及370的5个 lec.....



写过了基础后我们开始写 median:

median 主要就是快速取 median 的算法.

#### max-min heap 动态更新 median

**Max Heap**：存储当前所有元素的较小一半，堆顶是这部分的最大值

**Min Heap**：存储当前所有元素的较大一半，堆顶是这部分的最小值。

add 元素：

- 首先比较这个元素与最大堆的堆顶（如果最大堆非空）。如果新元素小于或等于最大堆的堆顶，将其加入最大堆；否则，加入最小堆。
- 加入元素后，检查两个堆的大小，确保大小之差不超过1。如果某个堆的大小比另一个堆大2或以上，需要重新平衡。

- 如果最大堆的元素比最小堆多，将最大堆的堆顶元素弹出并将其插入到最小堆；反之，如果最小堆的元素比最大堆多，将最小堆的堆顶元素弹出并将其插入到最大堆。

**获取中位数**：

- 如果两个堆的总元素数是奇数，则中位数是元素更多的那个堆的堆顶。
- 如果是偶数，则中位数是两个堆堆顶的平均值。



下午 finish 完了除了 time traveller 之外的东西。。

现在开始 time traveller

time traveller 的意思是对于每一个 stock，在整个 timestamp 中最大的卖和买之间的差价。每个 stock 的 timetraveller 对应了一个该 stock 的 sell order 和一个 later 的 buy order.

所以这其实是一个很弱鸡的版本，不用考虑数量不用考虑中间其他人买入和补货，只需要找到一单卖和一单买，使得差价最大，subject to 条件 that 卖单比买单早就可以。

所以这其实是个 optimization 问题

   "cwd": "${fileDirname}",

state: initial

首先在出现第一个 sell 时，state 变为: can buy

一直等到第一个 buy，state: complete；等待过程中如果发现价格更低的 sell 也更新 sell 但不更新 state

complete 状态之后每次读取新 Order 有两个方向

1. 新 Order 是 buy：是否价格更高？是则更新 buy 为新 buy，state 仍然为 complete

2. 新 Order 是 sell 且更低，进入 state: potential

   potential state 保留了原来的 sell 和 buy，但是总是存储一个新的 sell，这个 sell 比原 sell 更低.

   （如果新 order 是 sell 且更高，那么by 贪心原则忽略它）

potential 状态之后，我们有一对 complete （不再变动）的 sell-buy 对，以及一个随时可以更新的更低 sell2；并且，一旦出现某个 buy2 使得（buy2 - sell2）的值比 complete 中存储的 （buy1 - sell2）更高，那么就更新 pair 为这对，回到 state: complete



终于过了 spec。。。



### Debug: 设置 conditional break point

发现了一个好东西。。设置断点之后可以在断点上设置 condition，到达某个条件/count 之后进入断点，这就使得 debug 大型文件和小型文件一样简单了

### Debug: LeakSanitizer does not work under ptrace 

总是会出现这个 bug。查询了发现是 LeakSanitizer 与 debugger（如 `gdb` 或 `strace`）不兼容，很 sad.

根源在于 LeakSanitizer 无法在启用 `ptrace` 的环境下运行，`ptrace` 是 Linux 系统中用于进程间调试的一个机制。

解决方法：要么不使用 LeakSanitizer 要么不使用 gdb。也就是说一次用一个，查两次就好了。

**禁用 LeakSanitizer 或禁用调试器：**

如果只需要 LeakSanitizer 来检测内存泄漏而不需要进行调试，可以直接运行程序而不启动 `gdb`。

```bash
./your_program
```

甚至直接：

```sh
export LSAN_OPTIONS=detect_leaks=0
```

然后等下再

```sh
unset LSAN_OPTIONS
```

就好了。

#### 输出更多 verbose output

for debugging:

```sh
export LSAN_OPTIONS=verbosity=1:log_threads=1
```



#### debug log

现在 large 的普通 output 还有问题。。第一个问题在 981 行，T3 的 order 13 个 stock 7，应该是先向 T9 买 8个再向 T11 买5个，我们这里是直接向 T11 买了 13 个

note: line = 1058. 这里 input 在 1064 行，等于说 offset 是 -6.

查了之后发现我们的 T9 居然在 T11 下面。。

T9 的readinNum = 915，T11 的 readinNum = 943. T9 理应优先。

复盘：我们从 920 行读取了 T9 卖八个 S7，出价80块钱的 order，之后它一直没被买掉，也没有 。所以它理应

948行碰到了出价80的 T11

我们不妨看看 943 行的情况。

确认了，刚刚被放进去的时候它确实是在 T9 下面的。结果到 1058 行它跑到上面去了

readinNum 1050: 这个时候有一单 T5 买 34 个 S7，正好我的 s[7].sell[] 的 第一个是一个 T8卖的 34 个.

nextOrder.quantity 真好等于 topOrder.quantity.

于是 s[7].sell pop 了一个。

然后 943 上来了来到了 0 ？？？？？？？？？？ wtf？？？？同样的 Price 难道不应该优先 fix up 更早的 915 吗？？？？？？？？

我有点恍惚。。。



我现在出现了这样的情况：

我的 PQ 中，位置 0 的元素的 price 是 41，位置 1 和位置 2 的元素的 Price 都是 80.

但是位置 2 的元素，timeStamp 更大，

现在我 Pop 出 p[0]。根据我的 Comparator 的 implementation，理应原先的 p[1] 被 fix up，但是结果却是 p[2] 被 fix up. 为什么？

破案：STL 当然没问题，既然 debug 到这里明确发现这个情况那就是 obviously 只能是 comparator 写错了

发现写错了一个变量。。



终于！解决所有 time travller 问题。并且通过我的 P2random 生成的 test case 找到了 一些 bugs. 老P限制了一个 test 只能 30 行，还防了一手我们暴力搜索。。

以及其他报错终于知道了。。原来是我的 Median 忘关了。这波我不开 median 看看输出对不对



增加了 error checking 之后发现反而有几个莫名其妙 exit(1) 了。 281最人性化的事情是告诉你你自己的 test 的结果跑的对不对，其实写test就能得到官网的test结果。

最后发现是插入 return 和 exit 顺序反了



### test case 想法

现在 test-2-m:

3 4 5 10 13 15

test-8-t:

6 8 11 12

test-4-v:

1

test-3-t

3

test-3-v:

7

一共13个，还差：9, 14, 16 

把別人的 test 改了一頓結果別人找到的 Bug 不见了。。

想法：

1. 自己买自己卖出去的
2. 同价格时间戳也一样
3. 同价格时间戳不一样
4. 买卖恰好合计0，弹出
5. 买溢出，不上队
6. 卖溢出，队上消耗两人，最后一人正好耗完
7. （专门为了 median: 中位数的奇偶和取整
8. （专门为了 time travel）有一次 potential，potential 掉一买一卖最后成功
9. （专门为了 trader_info）有正有负

以及 INV 的问题。error checking:

1. timestamp 任何地方都不能小于 0，且非严格递增
2. trader ID, stock ID 范围
3. price，quantity 为正（严格



## Project-2B PQ

Modify: 

SortedPQ.hpp

BinaryPQ.hpp

ParingPQ.hpp

提供了正确的 PQ：unorderedPQ, unorderedFastPQ. 
UnorderedFastPQ 也没什么 fast 的地方，，，所谓的 fast 单纯只是在 top 方法时顺便存储了下位置，以便下次 pop 前如果没有改动那么 pop 就是 const time 的

显然 unordered PQ 并不好。我们

我门只能使用 `std::swap()`, `std::size_t` 和 `std::less<TYPE>`

sorted PQ 中多允许使用 `std::sort` 和 `std::lower_bound` 和 vector

BInaryPQ 中多允许使用 和 vector

PairingPQ 中多允许使用 duque 和 queue，但不能作为 private member.





### Note: `std::less` 作为 comparator 产生的是 max PQ

一个 counterintuitive 的事情：当我们使用 std::less 而不是 greater 的时候，我们是把大的元素放在前面的。std 其他函数和 ordered ds 也是这样。

std::greater 反而是 min PQ

### Sorted PQ

只用 <= 10 行就可以写完的屑 PQ

维持 sorted 就可以

### Binay (heap) PQ

课上讲的 binary heap PQ.

唯一需要主义的点是我们的伪代码是 1-based 的，这是为了方便 k / 2 就是 parent. 而实际上我们的代码肯定是 0-based 的. 这个问题的解决方案很简单，就是用一个 getElement 的函数获取 data[k-1] 来代替直接 Indexing vector



### Paring PQ

要看一篇老论文再 implement 的 PQ。。不想看直接扔给 GPT



pairing 的 核心是 melt.

melt 两个 Node 就是把其中小的一个作为另一个的 leftmost 子树

Node 有三个关联变了：parent, sibling, child

child 就是 Leftmost 子树的 node 

sibling 是同级别的右边一个 node





1. **put操作**：
   - 要将一个元素加入pairing heap中，首先创建包含该单个元素的新pairing heap，然后将其与已有的pairing heap进行`meld`合并。
2. 

1. **isEmpty、size和getMax操作**：

   - `isEmpty`、`size`操作通过维护数据结构中的元素数目来完成。
   - `getMax`操作通过直接返回根节点（最大元素）来完成。

   

2. **put操作**：

   - 要将一个元素加入pairing heap中，首先创建包含该单个元素的新pairing heap，然后将其与已有的pairing heap进行`meld`合并。

3. **increaseKey操作**：

   - 如果某节点的键值增加，可能会违反堆的最大性质，需要采取纠正措施：
     1. 将包含该节点的子树从原始树中移除。
     2. 合并剩下的树。
   - 增加键值时，不会检查是否真的需要调整，而是直接移除并重新合并。

4. **removeMax操作**：

   - 最大元素在根节点处，移除后会产生零个或多个子树。
   - 在“两遍合并”策略下，先从左到右合并每一对子树，然后从最右侧的树开始，逐一将其他树从右往左合并。
   - 例如，移除根后得到多个子树，先左到右配对合并，然后右到左合并。

5. **remove操作**：

   - 当要移除的节点是根节点时，按`removeMax`操作处理。
   - 如果节点不是根节点，移除操作步骤如下：
     1. 从树中分离包含该节点的子树。
     2. 删除该节点，并使用“两遍合并”或“多遍合并”策略将其子树合并为单个树。
     3. 将剩余的树合并为一个树。

6. **实现考虑**：

   - Pairing heap可通过树的二叉树表示法来实现，兄弟节点通过双向链表相连，每个节点有三个指针字段：`previous`、`next`和`child`。
   - 双向链表使得任意元素的移除可以在`O(1)`时间内完成。



implement 的时候发现了一件惊人的事情，就是 PQ 原来不是 FIFO 的。。。它等于说是一个弱化版的 ordered container。它的时间复杂度比 ordered PQ 小，但是功能也受到限制。

所以说 priority queue 其实就是弱化版的 ordered set，使用比较简单的时间复杂度来实现每次都 Pop 最高优先级的元素中的一个。







## Project-3 Bank

bank wire transfer simulator



commands:

```
./bank -vf registration.txt < commands.txt > out.txt
```

opt1: `--help/-h`，立刻打印 helpmessage 然后 `exit(0)`

opt2: `--file/-f filename` required argument，file in 的 reg file

opt3: `--verbose/-v`，输出增强

registration



input:

1. `fin` 一个 account file for  user registrations

   `REG_TIMESTAMP|USER_ID|PIN|STARTING_BALANCE`

   > 08:01:01:40:22:34|paoletti|372819|40000
   > 08:01:04:20:43:55|mmdarden|196204|30000
   > 08:01:07:94:92:10|mertg|080499|20000

2. `cin` redirected, 一个 command files

   command file 由两个部分组成. operations 和 queries.

   

   operations: 每一条都是 five defined operations 中的一个

   **#** (comment) ：`#..`

   **login**：`login <USER_ID> <PIN> <IP>`

   (log)**out**：`out <USER_ID> <IP>`

   **balance**：`balance <USER_ID> <IP>`

   **place** (transaction)：`place <TIMESTAMP> <IP> <SENDER> <RECIPIENT> <AMOUNT> <EXEC_DATE> <o/s>`

   $$$

   Queries: 每一条都是 4 

   





login: If both match, this user is allowed to start placing transaction requests, and their IP address is saved in a user-specific valid IP list for future processing

logout: If the user has an active session and the IP is an IP the user logged in with before, this logs them out, and removes the IP from the valid IP list for that user. Logged out users cannot place transaction requests from the same IP without logging back in. 

balance: If the user has an active session and the IP is an IP the user logged in with before, this displays their balance as of the most recently known timestamp.

