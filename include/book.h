#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

namespace kg
{

struct Book
{
    struct Level
    {
        double price;
        int quantity;
        int count; // count of orders on each level

        Level() = default;
        Level(double _price, int _qty, int _cnt)
            : price(_price), quantity(_qty), count(_cnt)
        {}
    };

    int id;
    std::vector<Level> bids;
    std::vector<Level> offers;

    Book() = delete;
    Book(const Book&) = delete;
    Book& operator=(const Book&) = delete;

    Book(int _id) : id(_id)
    {
        size_t sizeOfSide = sizeof(Book) * 10; // reserve 10 level space
        bids.reserve(sizeOfSide);
        offers.reserve(sizeOfSide);
    }

    bool add(char side, double price, int quantity)
    {
        if(side == 'B')
        {
            return add<true>(bids, price, quantity);
        }
        else
        {
            return add<false>(offers, price, quantity);
        }
    }

    bool remove(char side, double price, int quantity)
    {
        if(side == 'B')
        {
            return remove<true>(bids, price, quantity);
        }
        else
        {
            return remove<false>(offers, price, quantity);
        }
    }

    bool replace(char side, double price, int quantity)
    {
        if(side == 'B')
        {
            return replace<true>(bids, price, quantity);
        }
        else
        {
            return replace<false>(offers, price, quantity);
        }
    }

    template<bool isBid>
    static bool lt(const Level& l, const double p) { return isBid ? (p < l.price) : (p > l.price); }

    template<bool isBid, typename CONT>
    bool add(CONT& cont, double price, int quantity)
    {
        if(price > 0 && quantity > 0)
        {
            auto itr = std::lower_bound(cont.begin(), cont.end(), price, lt<isBid>);
            if(itr != cont.end())
            {
                if(price == itr->price) // modify
                {
                    itr->quantity += quantity;
                    ++(itr->count);
                }
                else // insert and shift
                {
                    cont.insert(itr, {price, quantity, 1});
                }
            }
            else
            {
                cont.push_back({price, quantity, 1});
            }
            return true;
        }
        else
        {
            std::cerr << "unqualified price(" << price << ") or quantity(" << quantity << ")" << std::endl;
            return false;
        }
    }

    template<bool isBid, typename CONT>
    bool remove(CONT& cont, double price, int quantity)
    {
        if(levelQty<isBid>(price)) // level exist
        {
            auto itr = std::lower_bound(cont.begin(), cont.end(), price, lt<isBid>);

            if(itr->count == 1) // remove the level
            {
                cont.erase(itr);
            }
            else // reduce level quantity of order quantity
            {
                itr->quantity -= quantity;
                --(itr->count);
            }
            return true;
        }
        else
        {
            std::cerr << "no level on price " << price << std::endl;
            return false;
        }
    }

    template<bool isBid, typename CONT>
    bool replace(CONT& cont, double price, int quantity)
    {
        if(levelQty<isBid>(price)) // level exist
        {
            auto itr = std::lower_bound(cont.begin(), cont.end(), price, lt<isBid>);

            itr->quantity = quantity;

            return true;
        }
        else
        {
            std::cerr << "no level on price " << price << std::endl;
            return false;
        }
    }

    int bidsSize() const { return bids.size(); }
    int offersSize() const { return offers.size(); }
    int getId() const { return id; }

    template<bool isBid>
    const int levelQty(const double price) const
    {
        auto& cont = isBid ? bids : offers;
        auto itr = std::lower_bound(cont.begin(), cont.end(), price, lt<isBid>);
        if(itr != cont.end() && itr->price == price) return itr->quantity;
        return 0;
    }

};

}


