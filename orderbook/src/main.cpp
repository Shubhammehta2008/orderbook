#include "OrderBook.h"
#include <iostream>

int main() {
    OrderBook book;
    std::cout << "=== Simple Order Matching Engine ===\n\n";
    // Kuch demo orders daal rahe hain taaki dikh sake matching kaise kaam karti hai
    book.addOrder(Order(Side::SELL, 101.0, 10));
    book.addOrder(Order(Side::SELL, 100.5, 5));
    book.addOrder(Order(Side::BUY, 99.0, 8));
    book.printBook();
    // Ye order match ho jayega kyunki price sell se zyada hai
    book.addOrder(Order(Side::BUY, 101.0, 12));

    book.printBook();

    return 0;
}
