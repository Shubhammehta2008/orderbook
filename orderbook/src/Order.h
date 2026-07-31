#pragma once
#include <string>

// Order kis type ka hai - Buy ya Sell
enum class Side {
    BUY,
    SELL
};

// Ek Order ke andar ye sab info hoti hai
struct Order {
    int id;          // har order ki unique id
    Side side;       // BUY ya SELL
    double price;     // kis price pe order hai
    int quantity;     // kitna quantity chahiye/beचना hai

    Order(Side s, double p, int q)
        : id(0), side(s), price(p), quantity(q) {}
};

// Side ko print karne ke liye helper function
inline std::string sideToString(Side s) {
    return s == Side::BUY ? "BUY" : "SELL";
}
