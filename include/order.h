#pragma once

namespace kg
{


struct Order
{
    long id;
    char side;
    double price;
    long quantity;

    std::string symbol;

    Order() = default;
    Order(int _id, char _side, double _price, int _qty, std::string _sym)
        : id(_id), side(_side), price(_price), quantity(_qty), symbol(_sym)
    {}

    int getId() const { return id; }
};


}
