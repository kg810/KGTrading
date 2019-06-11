#pragma once

namespace kg
{
namespace ob
{

enum class OrderStatus
{
    open,
    execute,
    filled,
    partialfilled,
    cancel,
    none
};

class Order
{
public:
    Order() = default;
    Order(int _id, char _side, char _type, double _price, int _qty, std::string _sym)
        : id(_id), side(_side), type(_type), price(_price), quantity(_qty), symbol(_sym)
    {}

    int getId() const { return id; }

    void setStatus(OrderStatus sta) { status = sta; }

private:
    long id;
    char side;    // 'B' for bid, 'A' for ask
    char type;    // 'L' for limit, 'M' for market
    OrderStatus status{ OrderStatus::open };
    double price;
    long quantity;
    std::string symbol;
};


}
}
