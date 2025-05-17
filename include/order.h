#include <iostream>
#include <map>
#include <deque>
#include <string>
#include <cstdint>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

#ifndef ORDER_H
#define ORDER_H

enum class OrderType { BUY, SELL };

struct Order {
    uint32_t id;
    OrderType side;
    double price;
    uint32_t quantity;
};

class OrderBook {
public:
    void add_order(const Order&);
private:
    // ==================== function ====================
    void match(void);

    // ==================== variable ====================
    // Price -> Orders (FIFO)
    std::map<double, std::deque<Order>, std::greater<double>> buy_orders; // greater<> is C++14 up
    std::map<double, std::deque<Order>> sell_orders;
    
};

#endif