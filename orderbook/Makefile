CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

SRC = src/main.cpp src/OrderBook.cpp
TARGET = orderbook

TEST_SRC = tests/OrderBookTest.cpp src/OrderBook.cpp
TEST_TARGET = orderbook_test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: all
	./$(TARGET)

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -lgtest -lgtest_main -pthread -o $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)