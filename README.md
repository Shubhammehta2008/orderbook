 Simple Order Matching Engine (C++)

Ek basic **limit order matching engine** — jaise stock exchanges (NSE, NASDAQ)
ke andar Buy aur Sell orders ko match karte hain, waise hi.

Ye project **Price-Time Priority** rule follow karta hai:
- Sabse acchi price wala order pehle match hota hai
  (highest buy price, lowest sell price)
- Same price par jo order pehle aaya (time priority / FIFO), wo pehle match hota hai

## Kaise chalayein

```bash
make run
```

Ye project compile karke `./orderbook` chala dega. Output mein dikhega ki
kaise orders add ho rahe hain aur kaunse trades match ho rahe hain.

## Project Structure

```
src/
  Order.h        -> Order ka data structure (id, side, price, quantity)
  OrderBook.h    -> Matching engine ka class definition
  OrderBook.cpp  -> Matching ka actual logic
  main.cpp       -> Demo run karne ke liye
Makefile         -> Build karne ke liye
```

## Ye Kaam Kaise Karta Hai

- Buy orders `std::map` mein store hote hain, **highest price pehle**
- Sell orders `std::map` mein store hote hain, **lowest price pehle**
- Jab bhi naya order aata hai, `matchOrders()` check karta hai ki koi
  buy-sell pair match ho sakta hai ya nahi
- Agar match hota hai, dono orders ki quantity kam ho jaati hai; jo order
  poora fill ho jaaye, use book se hata diya jaata hai

## Roadmap (Aage Kya Add Karna Hai)

Ye project jaan-boojh kar simple rakha gaya hai taaki isse dheere-dheere
badhaya ja sake. Neeche kuch ideas hain jo isse aur behtar banayenge, aur
inhe seekhne se HFT/trading systems wale roles ke liye achha base banega:

- [ ] **Order cancel/modify** support add karna
- [ ] **Multi-threading**: ek thread orders generate kare, doosra unhe process
      kare (`std::thread`, `mutex`, `condition_variable` seekhne ka mauka)
- [ ] **Benchmarking**: har trade match hone mein kitna time laga, `std::chrono`
      se measure karna (latency measure karna HFT ka core idea hai)
- [ ] **Networking**: TCP socket bana kar orders ko bahar se (jaise ek
      Python script se) bhejna
- [ ] **Unit tests** add karna (Google Test se)
- [ ] **Market data feed simulator**: random orders generate karne wala
      alag module

## Kyun Banaya

Ye project data structures (`map`, `list`), OOP, aur real-world trading
systems ke core concept (order matching) ko cover karta hai — jo fintech
aur trading-adjacent roles ke liye relevant hai.
