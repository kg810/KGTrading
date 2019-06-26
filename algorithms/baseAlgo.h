/*
 * base algorigthm class
 */

#include<string>
#include<vector>
#include<map>

#include"../kglib/orderbook/order.h"

namespace kg
{
namespace algo
{

class baseAlgo
{
public:
    virtual ~baseAlgo();

    /*
     * init baseAlgo
     */
    virtual void init() = 0;

    virtual void run() = 0;

private:

    virtual ssize_t newOrder() = 0;

    virtual ssize_t cancelOrder() = 0;

    std::vector<std::string> symbols;
    std::vector<uint16_t> kgIds;
    std::map<uint16_t, ob::Order> orders;
};

}
}
