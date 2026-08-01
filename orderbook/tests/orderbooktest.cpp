#include <gtest/gtest.h>
#include <string>

#include "../src/OrderBook.h"
#include "../src/Order.h"

// Test 1: Order successfully add hona chahiye
TEST(OrderBookTest, AddOrderDoesNotCrash)
{
    OrderBook book;

    EXPECT_NO_THROW({
        book.addOrder(Order(Side::BUY, 100.0, 10));
    });
}

// Test 2: Buy aur Sell match hone chahiye
TEST(OrderBookTest, MatchingOrders)
{
    OrderBook book;

    // Buy: 10 units @ 100
    book.addOrder(Order(Side::BUY, 100.0, 10));

    // Sell: 5 units @ 100
    // 5 units trade honge
    book.addOrder(Order(Side::SELL, 100.0, 5));

    testing::internal::CaptureStdout();

    book.printBook();

    std::string output = testing::internal::GetCapturedStdout();

    // Buy order mein 5 units remaining hone chahiye
    EXPECT_NE(output.find("#1  5 @ 100"), std::string::npos);

    // Sell order completely filled ho gaya,
    // isliye book mein nahi hona chahiye
    EXPECT_EQ(output.find("#2  5 @ 100"), std::string::npos);
}

// Test 3: Prices cross nahi karte to match nahi hona chahiye
TEST(OrderBookTest, NoMatchWhenPricesDoNotCross)
{
    OrderBook book;

    // Buyer maximum 100 dena chahta hai
    book.addOrder(Order(Side::BUY, 100.0, 10));

    // Seller minimum 105 maang raha hai
    // Isliye match nahi hoga
    book.addOrder(Order(Side::SELL, 105.0, 5));

    testing::internal::CaptureStdout();

    book.printBook();

    std::string output = testing::internal::GetCapturedStdout();

    // Dono orders book mein hone chahiye
    EXPECT_NE(output.find("#1  10 @ 100"), std::string::npos);
    EXPECT_NE(output.find("#2  5 @ 105"), std::string::npos);
}