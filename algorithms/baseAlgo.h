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
    virtual init() = 0;

    virtual run() = 0;

private:

    virtual newOrder() = 0;

    virtual cancelOrder() = 0;

    std::vector<std::string> symbols;
    std::vector<uint16_t> kgIds;
    std::map<uint16_t, ob::Order> orders;
};

}
}
