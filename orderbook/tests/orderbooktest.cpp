#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

#include "../src/OrderBook.h"
#include "../src/Order.h"

TEST(OrderBookTest, AddOrderDoesNotCrash)
{
    OrderBook book;

    EXPECT_NO_THROW({
        book.addOrder(Order(Side::BUY, 100.0, 10));
    });
}

TEST(OrderBookTest, MatchingOrders)
{
    OrderBook book;

    // Buy: 10 units @ 100
    book.addOrder(Order(Side::BUY, 100.0, 10));

    // Sell: 5 units @ 100
    // 5 units should be traded
    book.addOrder(Order(Side::SELL, 100.0, 5));

    testing::internal::CaptureStdout();

    book.printBook();

    std::string output = testing::internal::GetCapturedStdout();

    // Buy order should have 5 units remaining
    EXPECT_NE(output.find("5 @ 100"), std::string::npos);

    // Fully matched sell order should not remain
    EXPECT_EQ(output.find("SELL"), std::string::npos);
}

TEST(OrderBookTest, NoMatchWhenPricesDoNotCross)
{
    OrderBook book;

    // Buy willing to pay 100
    book.addOrder(Order(Side::BUY, 100.0, 10));

    // Seller wants 105 -> no match
    book.addOrder(Order(Side::SELL, 105.0, 5));

    testing::internal::CaptureStdout();

    book.printBook();

    std::string output = testing::internal::GetCapturedStdout();

    // Both orders should remain
    EXPECT_NE(output.find("5 @ 105"), std::string::npos);
    EXPECT_NE(output.find("10 @ 100"), std::string::npos);
}