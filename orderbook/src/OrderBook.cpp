#include "OrderBook.h"
#include <iostream>

void OrderBook::addOrder(Order order) {
    order.id = nextOrderId++;

    std::cout << "[NEW ORDER] #" << order.id << " "
              << sideToString(order.side) << " "
              << order.quantity << " @ " << order.price << "\n";

    if (order.side == Side::BUY) {
        buyOrders[order.price].push_back(order);
    } else {
        sellOrders[order.price].push_back(order);
    }

    // har naya order aane ke baad, dekho koi match banta hai kya
    matchOrders();
}

void OrderBook::matchOrders() {
    // jab tak best buy price >= best sell price hai, tab tak match hota rahega
    while (!buyOrders.empty() && !sellOrders.empty()) {
        auto bestBuyIt = buyOrders.begin();   // highest buy price
        auto bestSellIt = sellOrders.begin(); // lowest sell price

        double buyPrice = bestBuyIt->first;
        double sellPrice = bestSellIt->first;

        // agar buyer, seller se kam price de raha hai, to match nahi hoga
        if (buyPrice < sellPrice) {
            break;
        }

        // is price level ka sabse pehla order (time priority - FIFO)
        Order &buyOrder = bestBuyIt->second.front();
        Order &sellOrder = bestSellIt->second.front();

        int tradedQty = std::min(buyOrder.quantity, sellOrder.quantity);

        std::cout << "  [TRADE] " << tradedQty << " units @ " << sellPrice
                  << "  (Buy #" << buyOrder.id << " <-> Sell #"
                  << sellOrder.id << ")\n";

        buyOrder.quantity -= tradedQty;
        sellOrder.quantity -= tradedQty;

        // agar order poora fill ho gaya, to list se hata do
        if (buyOrder.quantity == 0) {
            bestBuyIt->second.pop_front();
            if (bestBuyIt->second.empty()) {
                buyOrders.erase(bestBuyIt);
            }
        }

        if (sellOrder.quantity == 0) {
            bestSellIt->second.pop_front();
            if (bestSellIt->second.empty()) {
                sellOrders.erase(bestSellIt);
            }
        }
    }
}

void OrderBook::printBook() const {
    std::cout << "\n----- ORDER BOOK -----\n";
    std::cout << "SELL SIDE (lowest price on top):\n";
    for (auto it = sellOrders.rbegin(); it != sellOrders.rend(); ++it) {
        for (const auto &o : it->second) {
            std::cout << "  #" << o.id << "  " << o.quantity
                      << " @ " << o.price << "\n";
        }
    }

    std::cout << "-----------------------\n";

    std::cout << "BUY SIDE (highest price on top):\n";
    for (const auto &level : buyOrders) {
        for (const auto &o : level.second) {
            std::cout << "  #" << o.id << "  " << o.quantity
                      << " @ " << o.price << "\n";
        }
    }
    std::cout << "-----------------------\n\n";
}
