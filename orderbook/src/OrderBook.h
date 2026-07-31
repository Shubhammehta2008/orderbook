#pragma once
#include <map>
#include <list>
#include <functional>
#include "Order.h"

// Ye class actual matching engine hai.
// Buy orders ko highest price pehle store karte hain (kyunki jo zyada
// price de raha hai use pehle match karna chahiye).
// Sell orders ko lowest price pehle store karte hain (jo sabse kam
// price maang raha hai use pehle match karna chahiye).
class OrderBook {
public:
    // Naya order add karo. Ye function matching bhi trigger karega.
    void addOrder(Order order);

    // Poori order book print karo (jo abhi tak match nahi hui)
    void printBook() const;

private:
    // Matching logic - jab bhi order add ho, ye check karega
    // ki koi buy-sell pair match ho sakta hai ya nahi
    void matchOrders();

    // price -> us price pe waiting orders ki list (time priority ke liye list)
    std::map<double, std::list<Order>, std::greater<double>> buyOrders;
    std::map<double, std::list<Order>> sellOrders;

    int nextOrderId = 1;
};
