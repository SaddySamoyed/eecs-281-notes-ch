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





buyer: .price >= top.



所以整体逻辑：

1. 查看 PQ top

2. match 则交易，不 match 则入队\

   while (match)

1. while current.quantity !0 

   { 比较 quantity, 如果 current 的 quantity > top.quantity, 那么 top 被 pop，current 的 quantity -= top.quantity; 

   如果 current 的 qua =top. quantity，则 pop top

   如果 current 的 quantity < top.quantity，则 top

   }

   

   where 

   current 继续检查下一个 top. while 一直查直到 < top.quantity

   否则查看是否小于，小于则 top.quantity -= current.quantity，



现在问题：

1. buyer 是按照愿意出的最低价排队的，但是PQ 的 API 只有获取 priority 最高的





我们先做一个 4 个 mode 都不开的，纯 match 到 TL 输入结束的版本。

同时也没有 error checking. 

