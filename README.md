# KGTrading

KGTrading targets to build a low-latency trading platform, including core components of feedhandler(CTP first), gateway, algorithms support, network lib support, core interprocess support

## what's done..
### orderbook
class Order - define order structure. Although problem only requires single symbol, the solution supports mutiple symbols.
class Book - define book sturcture, includes Level sturcture, and several operations.
class OrderBookMgr - define user interface, support all 5 operations in Part A problem.

## test
test.cpp defines unit testcases to cover most of functionalities provided in orderbook.h. it's based on boost unit test framework.

## basic analysis
In my implementation, order is stored in hash map, so performance is always O(1)
worst-case time performance for some sample operations:
1. Given an Order, add a new order to the book. O(m) - worst-case is insert top of book, need to shift all levels
2. Given an id, remove the order with that ID from the book. O(m) - worst-case is remove top of book, need to shift all levels
3. Given an id and quantity value, modify the order with that ID to have the new quantity. O(log(m)) - lookup by binary search.
4. Given a side and integer level, return the price for that side and level. O(1) - Book structure supports constant time lookup
