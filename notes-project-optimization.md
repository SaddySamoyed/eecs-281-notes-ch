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


### regfile

1. `fin` 一个 account file for  user registrations

   `REG_TIMESTAMP|USER_ID|PIN|STARTING_BALANCE`

   > 08:01:01:40:22:34|paoletti|372819|40000
   > 08:01:04:20:43:55|mmdarden|196204|30000
   > 08:01:07:94:92:10|mertg|080499|20000



### Operations

2. `cin` redirected, 一个 command files 

   command file 由两个部分组成. operations 和 queries.



operations: 每一条都是 five defined operations 中的一个

**#** (comment) ：`#..`

**login**：`login <USER_ID> <PIN> <IP>`

(log)**out**：`out <USER_ID> <IP>`

**balance**：`balance <USER_ID> <IP>`

**place** (transaction)：`place <TIMESTAMP> <IP> <SENDER> <RECIPIENT> <AMOUNT> <EXEC_DATE> <o/s>`

$$$



timestamp: 每一个时值都可以是 0-99

这意味着我们可以把它变成一个 unsigned long long，即 uint64 处理



comment: 无视



login: 输入 ID, pin，如果两个都 Match 了则 login，login 才能 Place trans

login 表示： IP address is saved in a user-specific valid IP list for future processing.

如果 verbose 则 print 一条 `User <USER_ID> logged in.`

如果不 Match 则print `Login failed for <USER_ID>.`



logout: 输入ID，IP

如果 user-specific valid IP list 中有这个 IP，则 logout：把这个 IP 移除出 user 的 IP list 中.

如果 verbose 则 print 一条 `User <USER_ID> logged out.`

如果 user 的 IP list 中找不到这个 IP，那么 `Logout failed for <USER_ID>.`







balance: 报 balance. 时间点选在最新的一条 Place.

但是不能靠我的pq.top 来查询。因为可能已经全部处理完了。所以我的 bank 里要留一个最近一条 trans 的时间。 uint64

这里还有一个事情是 fraud 检测。fraud 就是 IP list 非空但是却没有当前IP







place:

主要问题在 execute

我们使用一个 pq 来存储所有的 executions.

只有 place 这个 Op 是带有 timestamp 的。意味着它代表了我们当前的 timestamp.

当我们读取到了比 pq.top <= 的 timestamp 的时候，我们一口气处理当前 pq 里面的 transactions，一直 pop 到 PQ.top 的 timestamp 比当前 place 指令的 timestamp 更大为止。（记得判断是否 empty。empty 则忽略

并且，一旦我们读取到$$$意味着 ops 读取结束，我们一口气处理 PQ 里面所有剩下的 trans

以上是 execute 的东西. 在 Place 的函数体的内部首先要做这件事情。



下面是  check error:

1. invalid ID

2. not logged in

3. same sender/rec

4. timestamp >= current time

5. within 3 days (<=3000000)

   

以下是几个问题：

1. 如果这次 trans 无效，那么是否还要++ 时间？是否还要执行交易？





### Queries



We've noticed that the H4v test case is giving some students unexpected issues with memory. One of the major reasons for this is rather subtle and unintended because we didn't test all possible containers for storing incoming/outgoing transactions for users. If you're using deques or queues (queue is implemented with deque) to store the incoming/outgoing transactions for each user, we strongly recommend that you use a different container. The alternative containers that you can use are vectors or linked lists.

We're not 100% sure why this is the case yet, but we apologize for the difficulties this may have caused you!







Queries: 一共四种

1. list transactions

   列举 一段时间之内 execute 的所有 transactions

2. bank revenue

   列举一段时间内的 Bank revenue 

3. customer history

   customer History: customer 自己的 incoming 和 outgoing transactions 

   各至多 Latest 十条。用一个 vector 存。

4. summarize day

   summarize 一条之内的所有 transactions



所以是这样的一个事情：我们不得不记录历史的 transactions. 并且，我们需要能够找到时间（在哪一天开始）对应的 trans. 

因而我们需要的是一个 vector：每次 PQ 弹出一个 transaction，都往 vector 里面塞一个。这样就可以 binary search transaction. 

而对于每个 account，为了统计 Incoming 和 outcoming 的 transactions，我们最好设置一个 queue，并 track size，到了 10 之后开始. 但是貌似 queue 会超



对于 PQ 中的 transactions: 一定是按时间戳严格排序的。对于失败的交易：

you should discard the transaction: it will not appear in either user’s completed transaction, and no balances would change.









### 工程进度

1. 写 opt （ok！
2. 写 read regfile （ok！
3. 写 read operations（ok！
4. 重写比较 transaction，加上 ID 的比较。当前 ID 还没有加入 struct 里
5. dd



目前工程初稿完成。



### Debug

目前理论完成了 regfile 以前的 debug

spec: 问题在第二次 place order 的时候 execute 前一次 order 上. 

1. 顺序反了。应该先 execute 再 Place
2. transID 有问题。没有++

第一个好解决。第二个问题在于：我们的 ID generate 是 Based on history size 的，但是 history 并不是 Place 后放入而是执行之后放入。这样做是为了 history 是按照时间排序的。因而有问题。

现在尝试：加入 tracking 变量。ok



目前 spec 的 readOp 过了。可喜可贺

现在开始搞 spec 的 query

query l: spec ok

query r: 发现问题，我的extractPair 把 Int 变成时间有问题。最后 vector 少了一个 entry. resize vector 就完事了

ok

query h: 发现用户的 transaction Count 和 outgoCount 是个很离谱的数字。我探一下是为啥。应该是 lib2 的问题。transationCount 和 Outgo都是在 execute 一条结束的时候更新的。是否初始值没有设置？

第二个错误：把 transaction 在 history 里的位置导入 account 的 transaction 10 条记录的时候忘记 size-1了.

qeury s: spec ok



####  post spec

1. error checking: 就两个。place timestamp 比上个小；place exe 比 timestamp 早。ok

2. test cases:

   idea:

   每个 print 的情况都要 test.

   除了 query 外每种都测试了。

   

   

   

   

### 提交记录

#### record 1

给出了 test2 的结果。test2 第十行错了， balance 多了 10. 应该是 separate 的时候分手续费 += 搞反了。

test 2 resolved.

#### record 2

test 3. 只有一个 insufficient fund 有问题。

test 3 resolved.

#### record 3

已经红温。三次就提了一个 test

但是 student tests 终于过了. 有了一次额外提交机会

test 5 resolved.

1. 这个多余的 at 是很多 test 的问题。solved.

2. 另外还有一个问题：很多个文件第一行的 As o.... 我们输出是 Logo... 

   应该是 Login 的问题。小事。发现这个指令是 "As of timestamp, user... has a balance"... 

   而我们输出的是 Logout 的verbose. 破案了是忘记写 verbose 了.

   solved

3. error checking exit(1) 有一个没 check 到.

   两个cerr都写了。这个问题应该是 currentime 没更新好？不可能

   应该是 file open 的 error check 以及读取的 error check

4. 唯一一个 sig fault.

   ```sh
   Test case H3v: Failed
       Runtime (sec): 0.004/0.006 
       Memory (kb): 3192/4857 
   The program was stopped with signal SIGSEGV ---
   Feedback from valgrind (if you don't see line numbers, be sure your Makefile 'all' target creates ./bank_valgrind):
    Invalid read of size 8
       at 0x40D37B: Bank::readQuery() (lib3-query.cpp:192)
       by 0x40AC93: main (bank.cpp:10)
     Address 0x5b46f00 is 32 bytes inside an unallocated block of size 4,092,160 in arena "client"
   ```



#### record 4

11/9. 可喜可贺终于写完了。差优化没做，以及一个 error checking.

空间优化仅剩一点。

时间优化大概就是那几个 search 的缘故。

把 Linear search 改成 Binary search（lower_bound）就行。

1. error checking: 发现是因为 update current time 写在了检查 current time 之前所以怎么都是对的。已解决。



### Optimization

#### Binary Search Lower Bound

既然 History 里面的时间肯定是按顺序排序的，我们可以用 binary searach 来查找

lower bound 找到第一个 >= n 的位置。upper bound 是第一个 >n 的位置.

于是 binary search 替掉了 linear search. 

```c++
bool compareExecDate(const Transaction& transaction, unsigned long long t1) {
    return transaction.execDate < t1;
}

auto lowerBound = std::lower_bound(transactionHistory.begin(), transactionHistory.end(), t1, compareExecDate);
```

现在这个 query 已经优化得不能再优化了，看看 readOp 有什么可优化的



#### `std::ios_base::sync_with_stdio(false);`

又忘了加上了。。。

Time optimized over

（虽然满了但其实还有可优化的：

#### `getline` 改成直接 `cin`

感觉被 p1 不要直接 cin 误导了，，那个是因为输入格式没法直接粗暴 loop，如果直接 cin 还要做别的处理。实际上一般肯定是直接 cin 快

now I have a long line of commands to read in. Each command has some int, string and char variables, parted by space
I have two ways to do it. 

The first is to getline(cin, line) to get a string called line.
And I put a stringstream called ss. I do `ss.str(line)` and ss >> ... my variables
The other way is to directly cin

显然最后 >> 移动的东西是一样多的. 而 getline 的方法比 cin 多了一个读行到\n 以及一个 ss.str 的时间. 以及多了一个 getline 的内存和 ss 的内存（可忽略



#### 把 loop 内 declare 的变量尽量都放 loop 外

有一个 Transaction 变量是在 getline 过程中每次 Loop 都 declare 一次（在 while 外过 scope 被 deallocate）

于是假设 loop 了 10000 次，于是就比起在 loop 外 declare 要多了 9999 次的 allocate 和 deallocate 的时间.

每次 declare 这个 variable 它都被 allocate 到 stack 上，但是之后也会 deallocate. 所deallocate 会直接抵消掉 allocate 的时候 stack pointer 的增长。因而对 memory 影响不大。

时间上，对于复杂的 class, struct，我们每次生成都要调用构造函数，destroy 都要调用 dtor. 所会造成额外的开销，并且随循环次数大量积累. 对于简单的 types 比如 build-in 的 int, char 等等， 影响不大







## Project-4 Pokeman

这个 Project 最人性化的地方就是三个 parts 全是分开的毫无关系

最不人性化的地方就是其他所有地方。。



### A: MST

我们输入一堆坐标，在以这些坐标为 Nodes 的全连通图上找 MST

水和陆分开。水和陆不能通行，必须通过边界点

也就是说，我们必须要区分水和陆的点，分别在水和陆上找到 MST

然后再把它们离边界（也就是 x,y 负半轴）上的任意点，最近的两个点分别作为水和陆的 root，连接边界上的点；它们在边界上的对应端点可以相同。

边界上的所有点，其连成一条直线放进 MST 里



也就是一共有三个部分，

水MST

陆MST

边界：暴力连接

等等也不是这样。。。应当不能这么做，这样未必是 MST.

只要把水陆两端的点之间的距离设置成无限大就可以了

与其说是完全图，不如说：

水上所有点构成一个完全子图，陆上所有点构成一个完全子图，并且这两部分中每个点都连接 coastal 上每个点

于是这其实就是一个正常的 non-heap prim 算法，应用在这个正常的图上，除了我们不需要表示这个图，因为给定两个节点可以自然地计算出它们的边长。

由于这是个 connected graph，非常 dense，我们应当使用 non-heap 的 Prim

1. 读取

   ok. 顺利读取。这个应该还可以在 BC 复用，很爽

2. prim 不用 heap

   第一遍写完有点问题。发现是 update parent 的问题。要确认 weight 比原来小了才更新 parent

   ok。顺利过了除了 4,6 之外的 test



#### Debug

A4，根据提示，border 的决定有问题。

A6，本来不应该 cerr 的地方 cerr 了，输出了 Cannot construct MST. 这个东西出来表示我应该是检测到了有 land, sea 但是却没有 border. 

好了 A6 的问题发现了。是我 has_land || has_sea 了，应该是两个都有，没有 border 才有问题。

A4 的问题。也发现了。是我对陆地的判定有问题，把一些陆地划分到 border 了。

x > 0, y = 0; y>0, x=0 也是陆地

border： x<0, y=0 ;  x=0, y<0

陆地：x>0 或 y>0 就算在陆地上

海洋：x<0 并且 y<0 才算在海洋上

这次应该过，先不急着交，写完一次近似算法 TSP 和一些 test files 再交吧



#### test cases A

1. 没有 border 的
2. 只有一个中心点
3. 全在海上
4. 全在陆地
5. 只有 border



A 圆满过了



### B: Approximation Algorithm of TSP

这个非常模糊。。甚至没给出一个标准，让我们随便找一个 approximation algorithm 来完成

理论上不困难。

好的一点在于：B 没有水陆限制。所以直接找一个欧几里得空间上的图上的 TSP 近似算法就好了

直接 GPT prompt!

### Prompt

现在我有一个 2-d Euclidean space, 在这个 space 上画 n 个点，形成一个 n-complete graph. 
我的需求：找出一个 O(n^2) time 的近似 TSP 算法。
我现在已经完成了 node, edge struct 以及 Eclidean space 中的 distance 计算机器, 以及完成了 class FASTTSPg 中, 读取 graph nodes 数据的工作！ 你需要在补完 void runFASTTSP() 函数. 当前, 我们已经读取了 int `num_pokemon` 个 nodes，放进了一个 `std::vector<node> nodes (num_pokemon)`.

```c++
struct node {
    double x;
    double y;
};

struct edge {
    int left;
    int right;
    double weight;
    edge(int l, int r, const double &w) : left(l), right(r), weight(w) {}
    edge() : left(-1), right(-1), weight(INF) {}
};

struct computedistanceNormal { //functor
    double operator()(const node &a, const node &b) {
        return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
    }
    computedistanceNormal() {}
};

class FASTTSPgo {
public:
FASTTSPgo() {}

// Already Finished!
void read_nodes(std::vector<node> &nodes, int num_pokemon);
// TO BE FINISHED!
void runFASTTSP(){
    int num_pokemon = 0;
    std::cin >> num_pokemon;
    std::vector<node> nodes (num_pokemon); 
    computedistanceNormal compute_distance;
    read_nodes(nodes, num_pokemon);
    // TODO
    return;
}
};
```

请你最后输出这样的格式:
total weight
tour

example: 
31.64
0 4 2 3 1



gpt 给我的答案是：每次都选取最近的点，，感觉其实挺不靠谱，但是交了一次

发现 set_precision 给我害惨，，，幽默了

第二次 set_precision(2) 之后提交。

这蹩脚的算法居然一次过了。。。。

错误的完全没有过。它只是绿了，但是没过。近似程度超了太多了。



#### Do some research

于是我找到了：

1. https://www.geeksforgeeks.org/approximate-solution-for-travelling-salesman-problem-using-mst/

   这是一个 2-approximation，目前而言是最可行的。只需要 MST 配合上 preorder traverse

2. Christofides–Serdyukov algorithm： 1.5 approximation，但是 O(n^3)。不行

3. IA notes里：nearest-neighbor + 2opt. nearest neighbor 就是我的第一想法，2opt 局部再优化。不过 2opt 的复杂度是 n^3

4. IA notes里：三个 insertion, 都是正好 n^2 复杂度

   

（ps：by research，其实没有利用好 Euclidean graph 的性质。BY WikiPedia: the minimum spanning tree of the graph associated with an instance of the Euclidean TSP is a [Euclidean minimum spanning tree](https://en.wikipedia.org/wiki/Euclidean_minimum_spanning_tree), and s**o can be computed in expected *O*(*n* log *n*) time for *n* points** (considerably less than the number of edges). This enables the simple 2-approximation algorithm for TSP with triangle inequality above to operate more quickly. 所以其实我们的 MST 算法超额了，本质上可以在 nlogn 时间找到 MST，但是这一条应该和本 project 没关系，它不做这种要求，MST 限制在 n^2 就好）



#### Trying

1. MST + preorder traversal

   为什么比最粗暴的方法 cost 还高，，我傻了，甚至 80% penalty

   幽默完了

2. 还得是 ed. 直接公布答案了，答案就是 IA notes 里面的 arbitrary insertion

3. implement 完了，居然每个 test 都超了 2%. 

   知道原因了。因为没有考虑从 path.back 到 path[0] 的这段路径也可以插入！

   Finished





#### test cases B

Prompt: 写一些10行以内，能够有效地检验一个 Euclidean TSP algorithm 的正确性的 test files

每一个都是：

N

x_1 y_1

...

x_N y_N





### C: TSP

C 更加阳间。就是一个完整的 TSP，只不过是在欧式图上

用 BnB 就可以。

遇事不决先询问 gpt



#### Prompt

现在，我想写一个 Euclidean 图上的 TSP 求解，使用 branch and bound 策略。

假设我已经读取了数据，都存储在了 vector<node> nodes 上了，每个 node 包含 double x,y;

并且，我现在也 implement 了一个比较不错的近似算法，在 O(n^2) 时间内返回一个近似的 vector<int> path 和一个近似的 total_weight

请你解释一下我需要做什么？以下是打底的代码

template <typename T>
void genPerms(vector<T> &path, size_t permLength) {
  if (permLength == path.size()) {
  // Do something with the path
    return;
  }  // if ..complete path

  if (!promising(path, permLength)) {
    return;
  }  // if ..not promising

  for (size_t i = permLength; i < path.size(); ++i) {
    swap(path[permLength], path[i]);
    genPerms(path, permLength + 1);
    swap(path[permLength], path[i]);
  }  // for ..unpermuted elements
}  // genPerms()



GPT 想到的方法是用 MST 来 bound 剩余 nodes 的路径和的 lower bound，因为它一定比剩余 nodes 的最优路径要小。如果 MST 的值+现在的 weight sum 都比目前的 optimal 要大，那么直接剪枝

但是注意到 Ed 上的帖子：



My part C is over on time, ranging from 1-4x in some test cases. I just optimized my code to used only squared distances, I get my initial bound using fasttsp and then prune by using a bound check with an mst of subset (my perf report says that the mst cost for subset function is taking over half of my time but this makes sense). Any tips for optimizing this further? Could the issue be my fasttsp heuristic? I am currently using arbitrary insertion

Test cases of part C exceed the time limit by a factor ranging from 1.++ to 6/TLE. I'm using part B result as a lower bound, constructing mst using linear search and always return promising when the size of mst is smaller than 5.

属于和我用了一样的策略并且连近似算法也一样。可想我 implement 完了之后很可能也得到这种结果

#### 思路

现在找到了一个满分的 ED post. 总结了以下的优化点：

1. 使用 approximation algorithm 的 weight 作为初始 upper bound，使用 approximation algorithm 的 tour 作为初始路线（Used the tour produced by the arbitrary insertion heuristic as the start of the path before gen_perms() is called.
2. 不要使用 sqrt 而是使用 iterative method 来计算 MST，或者 Precomputed distances between nodes in a matrix to avoid repeated expensive square root calculations.
3. 在剩余 nodes 达到 5 个之前，总是通过计算剩余 nodes 的 MST，计算 MST 的总权重+ 当前部分解的权重+ 当前部分解的首尾距离外部最近的两个边，作为 Lower_bound of 这个 branch，也就是它可能达到的最短路径，如果长于目前的最优解，直接 non-promising，剪枝
4. Keep a running total of the permuted weight to avoid redundant re-summing of the current tour.



#### debug

1. read_nodes: ok. 

2. approximationTSP: ok.

这个 project 好在对 memory 要求不高. 可以放一个 nxn 矩阵表示图，于是不用重复算边长了. 并且这是个全连通的图，可以不当作欧几里得图来看。

3. 下一个要做的就是：给定 visited vector，求出 unvisited 的 nodes 的 MST.

由于不能更改 visited 的性质，在函数里还要重新建一个 in_MST vector. 不过由于不用回溯找出路径，不需要设置 parent vector.

由于这是一个完全图，所以很方便，找到第一个不是

prompt：

现在我的class OPTTSPgo里面有 int num_pokemon，std::vector<node> nodes;，std::vector<std::vector<double>> graph; 这个 graph 是一个 complete graph

希望你写一个函数：

double calculateMST(const std::vector<bool>& visited) {

}

这个函数 take in 一个 visited vector 作为参数，表示哪些 nodes 0~num_pokemon-1 的 index 中，哪些 index 的 pokeman 已经被 visit 过了. 而你的目的是找出：所有没有被 visited 过的 nodes 构成的 complete graph 的 MST 的大小（不需要知道路径，只需要知道 MST 的总 weights 就可以），请你使用 Prim 算法，加以修改，完成这个函数，



MST 值一轮一轮确实减下来了。姑且算它对的

但是整体的 generatePermutation 居然卡死了

发现是循环上界的问题。

e,f 过了。









### Tests cases 

又是 ed 救命，，正好给我补上了 test case 1,2,3 这样就能拉满了

test case 1,2,3 都是 MST

Ed:For bug 1 and 2, i generated values between 0 and 100 and considered shores in both x = 0 and y = 0. I would recommend generating at least 6 coordinates

For bug 3, I used 0,0 as an edge case. I essentially did variations of two numbers to create different coordinates, for example:
(num1, num2), (num1, -num2),(-num1, -num2) etc.. 



