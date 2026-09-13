# Order Matching Engine
 
A high-performance limit order matching engine implemented in modern C++, designed to replicate core functionality found in stock exchanges (NSE, NASDAQ, etc.). This project demonstrates fundamental concepts in financial systems architecture and real-time order processing.
 
## Overview
 
This matching engine processes buy and sell orders for securities using the **Price-Time Priority** matching algorithm:
 
- **Price Priority**: Best prices are matched first
  - Highest buy prices paired with lowest sell prices
- **Time Priority**: Orders at the same price level are matched in FIFO (First-In-First-Out) order
  - Earlier orders execute before later ones at identical price levels
## Quick Start
 
### Build and Run
 
```bash
make run
```
 
This compiles the project and executes `./orderbook`. The output displays:
- Order insertions into the order book
- Real-time trade executions and matched pairs
## Project Structure
 
```
orderbook/
├── src/
│   ├── Order.h          # Order data structure (ID, side, price, quantity)
│   ├── OrderBook.h      # Order matching engine class definition
│   ├── OrderBook.cpp    # Core matching algorithm implementation
│   └── main.cpp         # Demo and test harness
├── Makefile             # Build configuration
└── README.md            # This file
```
 
## How It Works
 
### Core Components
 
**Order Data Structure**
- Unique order ID
- Side (BUY or SELL)
- Limit price
- Order quantity
**Order Book Management**
- Buy orders stored in `std::map` with **descending price order** (highest first)
- Sell orders stored in `std::map` with **ascending price order** (lowest first)
- Enables O(log n) order insertion and retrieval
**Matching Algorithm**
1. When a new order arrives, `matchOrders()` checks for executable counterparty orders
2. Orders are matched at the price level of the resting order (maker price)
3. When quantities match:
   - Both orders' quantities are decremented
   - Fully filled orders are removed from the book
   - Trade execution is recorded
4. Partially filled orders remain in the book
### Execution Logic
 
```
NEW BUY ORDER (price P, qty Q)
├─ Check best SELL orders (lowest price first)
├─ If SELL price ≤ P: MATCH at SELL price
├─ Decrement both order quantities
└─ Repeat until no more matches or BUY quantity = 0
 
NEW SELL ORDER (price P, qty Q)
├─ Check best BUY orders (highest price first)
├─ If BUY price ≥ P: MATCH at BUY price
├─ Decrement both order quantities
└─ Repeat until no more matches or SELL quantity = 0
```
 
## Key Features
 
✅ **Price-Time Priority Matching** — Compliant with standard exchange rules  
✅ **Efficient Data Structures** — O(log n) operations using std::map  
✅ **Order Book Visualization** — Clear output of book state and trades  
✅ **Modular Design** — Clean separation of concerns for easy extension  
✅ **Memory Efficient** — Automatic cleanup of fully filled orders  
 
## Example Usage
 
```cpp
OrderBook book;
 
// Add orders
book.addOrder(Order(1, OrderSide::BUY, 100.50, 100));    // Buy 100 @ 100.50
book.addOrder(Order(2, OrderSide::SELL, 100.75, 50));    // Sell 50 @ 100.75
book.addOrder(Order(3, OrderSide::SELL, 100.50, 50));    // Sell 50 @ 100.50
 
// Output:
// Trade: BUY Order 1 matched with SELL Order 3 @ 100.50 for 50 units
// Remaining: 50 units of Order 1 in book
```
 
## Development Roadmap
 
This project intentionally maintains simplicity to serve as a foundation for progressive enhancements. The following extensions are recommended to build a production-grade system and develop skills relevant to quantitative trading and HFT roles:
 
### Phase 1: Core Enhancements
- [ ] **Order Cancellation & Modification**
  - Implement cancel/modify requests
  - Update order quantities or remove orders entirely
  - Track order state transitions
- [ ] **Order Expiration**
  - Time-based order validity (Good-Till-Cancel vs. Good-For-Day)
  - Automatic order cleanup on expiration
### Phase 2: Performance & Concurrency
- [ ] **Multi-threaded Architecture**
  - Order input thread (producer)
  - Matching engine thread (consumer)
  - Use `std::thread`, `std::mutex`, `std::condition_variable`
  - Learn thread safety and synchronization primitives
  - Build understanding for concurrent trading systems
- [ ] **Latency Benchmarking**
  - Measure order-to-execution latency using `std::chrono`
  - Track matching engine throughput (orders/second)
  - Profile critical code paths
  - **Essential for HFT system optimization**
### Phase 3: Networking & Integration
- [ ] **TCP Socket Interface**
  - Accept orders from external clients (e.g., Python scripts)
  - Send trade confirmations and market data updates
  - Implement binary protocol for low-latency communication
  - Learn socket programming and network protocols
- [ ] **Market Data Feed**
  - Implement real-time order book snapshot export
  - Generate market data messages (trades, best bid/ask)
  - Support multiple subscribers (pub-sub pattern)
### Phase 4: Testing & Quality
- [ ] **Unit Tests**
  - Google Test (GTest) framework integration
  - Test matching logic with various order scenarios
  - Stress testing with high order volumes
  - Edge case validation (partial fills, price improvement, etc.)
- [ ] **Simulation Engine**
  - Realistic order flow generator
  - Market microstructure simulation
  - Performance regression testing
### Phase 5: Advanced Features
- [ ] **Multiple Asset Classes**
  - Support for different instruments
  - Cross-product order flow
- [ ] **Advanced Order Types**
  - Iceberg orders (hidden quantity)
  - Pegged orders (dynamic price adjustment)
  - Market orders with smart execution
- [ ] **Risk Management**
  - Position limits
  - Exposure monitoring
  - Circuit breakers
## Technical Learning Outcomes
 
This project covers fundamental concepts essential for roles in:
- **Quantitative Trading** — Order matching, market microstructure
- **Financial Technology (FinTech)** — Exchange infrastructure, trading systems
- **High-Frequency Trading (HFT)** — Low-latency optimization, system design
- **Systems Engineering** — Data structures, concurrency, performance optimization
### C++ Concepts Demonstrated
 
- **Standard Library**: `std::map`, `std::vector`, `std::deque`
- **OOP**: Class design, encapsulation, separation of concerns
- **Memory Management**: Smart pointers, RAII principles
- **Modern C++**: C++17 features, structured bindings
- **Algorithms**: Binary search (via std::map), FIFO matching
## Building and Testing
 
### Requirements
- C++17 or later compiler (g++, clang++)
- Make build system
### Compilation
 
```bash
# Clean and rebuild
make clean && make
 
# Run with default test cases
make run
 
# Run with verbose output
./orderbook
```
 
## System Requirements
 
- **Compiler**: GCC 7+, Clang 5+, or MSVC 2017+
- **Memory**: Minimal (< 50MB for typical workloads)
- **CPU**: Single-core sufficient for demonstration; multi-core for concurrency phase
## Performance Characteristics
 
| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Add Order | O(log n) | O(1) per order |
| Match Orders | O(k log n) | O(k) for k matches |
| Cancel Order | O(log n) | O(1) |
| Book Snapshot | O(n) | O(n) |
 
*n = total orders in book, k = number of matched orders*
 
## Code Quality Standards
 
- **Naming**: Clear, self-documenting variable and function names
- **Comments**: Technical explanations for complex matching logic
- **Structure**: Modular design enabling easy testing and extension
- **Style**: Consistent indentation and formatting (4-space standard)
## Future Integration Points
 
Once extended, this engine can integrate with:
- **Risk Management System** — Position monitoring, limit enforcement
- **Market Data Publisher** — Real-time feed distribution
- **Analytics Engine** — Trade analysis, market statistics
- **Backtesting Framework** — Historical simulation
## References & Resources
 
### Learn More About
- Exchange Order Books: Nasdaq Technical Documentation
- Matching Algorithms: CME Group matching rules
- Low-Latency Systems: "Systems Performance" by Brendan Gregg
- C++ Concurrency: "C++ Concurrency in Action" by Anthony Williams
## License
 
This project is provided as-is for educational and portfolio purposes.
 
## Author
 
**Shubham Mehta**  
- GitHub: [@Shubhammehta2008](https://github.com/Shubhammehta2008)
- LinkedIn: [Shubham Mehta](https://linkedin.com/in/shubham-mehta-ab134a335)
