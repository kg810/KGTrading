/*
Basic idea is construct a book for each symbol.
Each time we receive an order, will consolidate corresponding book with the order price/qty.
A sample book looks like below:
----------------------------------------------------
|         Bid            |            Offer        |
----------------------------------------------------
|count  quantity  price  |   price  quantity  count|
----------------------------------------------------
|10     100000    16.1   |   16.2   60000     3    |
|20     110000    16.0   |   16.4   75000     8    |
|                       ...                        |
----------------------------------------------------
*/

#pragma once

#include<cstddef>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<string>
#include<memory>
#include<algorithm>

namespace kg {

class MarketMgr
{
    std::unordered_map<int, Order> orders;
    std::unordered_map<int, std::shared_ptr<Book>> books;
    std::hash<std::string> hash_to_bookid;

public:
    MarketMgr() = default;

    std::shared_ptr<Book> getBook(int bookId)
    {
        auto itr = books.find(bookId);
        if(itr != books.end()) return itr->second;
        return nullptr;
    }

    // add a new order
    bool add(Order& order)
    {
        if(!orderExist(order.id))
        {
            int bookId = hash_to_bookid(order.symbol);

            if(!bookExist(bookId)) // create and init book
            {
                std::shared_ptr<Book> bptr = std::make_shared<Book>(bookId);
                if(bptr->add(order.side, order.price, order.quantity))
                {
                    books.emplace(bookId, bptr);
                    orders.emplace(order.id, order);
                    return true;
                }

                return false;
            }
            else // update existing book
            {
                auto itr = books.find(bookId);
                if(itr->second->add(order.side, order.price, order.quantity))
                {
                    orders.emplace(order.id, order);
                    return true;
                }
                return false;
            }
        }
        else
        {
            std::cerr << "order " << order.id << " already exists" << std::endl;
            return false;
        }
    }

    // remove given order
    bool remove(int orderId)
    {
        if(orderExist(orderId))
        {
            auto itr = orders.find(orderId);
            auto order = itr->second;

            int bookId = hash_to_bookid(order.symbol);
            auto bptr = getBook(bookId);
            if(bptr->remove(order.side, order.price, order.quantity))
            {
                orders.erase(itr);
                return true;
            }

            return false;

        }
        else
        {
            std::cerr << "no order on orderId " << orderId << std::endl;
            return false;
        }
    }

    // replace given order
    bool replace(int orderId, int quantity)
    {
        if(orderExist(orderId))
        {
            auto itr = orders.find(orderId);
            auto order = itr->second;

            int bookId = hash_to_bookid(order.symbol);
            auto bptr = getBook(bookId);

            int levelQty;
            if(order.side == 'B')
                levelQty = bptr->levelQty<true>(order.price);
            else
                levelQty = bptr->levelQty<false>(order.price);

            int newQty = levelQty - order.quantity + quantity;

            if(bptr->replace(order.side, order.price, newQty))
            {
                order.quantity = quantity;
                return true;
            }

            return false;

        }
        else
        {
            std::cerr << "no order on orderId " << orderId << std::endl;
            return false;
        }
    }

    double priceOfSideLevel(char side, int levelIndex, std::string symbol)
    {
        int bookId = hash_to_bookid(symbol);
        if(bookExist(bookId))
        {
            auto bptr = books.find(bookId)->second;
            if(side == 'B')
            {
                if(levelIndex < bptr->bidsSize())
                {
                    return bptr->bids[levelIndex].price;
                }
                else
                {
                    std::cerr << "levelIndex out of range." << std::endl;
                    return 0;
                }

            }
            else
            {
                if(levelIndex < bptr->offersSize())
                {
                    return bptr->offers[levelIndex].price;
                }
                else
                {
                    std::cerr << "levelIndex out of range." << std::endl;
                    return 0;
                }

            }

        }
        else
        {
            std::cerr << "no book on bookId " << bookId << std::endl;
            return 0;
        }
    }

    int qtyOfSideLevel(char side, int levelIndex, std::string symbol)
    {
        int bookId = hash_to_bookid(symbol);
        if(bookExist(bookId))
        {
            auto bptr = books.find(bookId)->second;
            if(side == 'B')
            {
                if(levelIndex < bptr->bidsSize())
                {
                    return bptr->bids[levelIndex].quantity;
                }
                else
                {
                    std::cerr << "levelIndex out of range." << std::endl;
                    return 0;
                }

            }
            else
            {
                if(levelIndex < bptr->offersSize())
                {
                    return bptr->offers[levelIndex].quantity;
                }
                else
                {
                    std::cerr << "levelIndex out of range." << std::endl;
                    return 0;
                }

            }

        }
        else
        {
            std::cerr << "no book on bookId " << bookId << std::endl;
            return 0;
        }

    }

    bool orderExist(int orderId)
    {
        if(orders.find(orderId) != orders.end())
            return true;

        return false;
    }

    bool bookExist(int bookId)
    {
        if(books.find(bookId) != books.end())
            return true;
        return false;
    }

    int orderSize() { return orders.size(); }
    int bookSize() { return books.size(); }

};

}
