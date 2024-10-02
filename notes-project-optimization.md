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
2. 
