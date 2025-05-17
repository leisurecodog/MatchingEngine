#include "Common.h"
#include "Order.h"

#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

class MatchingEngine{
public:

    MatchingEngine() : done(false) {}
    ~MatchingEngine() {
        stop();
    }
    void start(){
        worker = std::thread(&MatchingEngine::processOrders, this);
    }
    void stop() {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            done = true;
            MSG(1, "===== Engine Stop =====");
        }
        cv.notify_all();
        if (worker.joinable()) {
            worker.join();
        }
    }
    void addOrder(const Order&);
private:
    // ==================== function ====================
    void matchOrders(void);
    void processOrders(void);

    // ==================== variable ====================
    // REQUIRED, for Macro time display
    std::time_t now_c;
    // Price -> Orders (FIFO)
    std::map<double, std::deque<Order>, std::greater<double>> buy_orders; // greater<> is C++14 up
    std::map<double, std::deque<Order>> sell_orders;
    // for user submit order
    std::queue<Order> orderQueue; 
    // for multi-threading
    std::thread worker;
    std::mutex  queueMutex;
    std::condition_variable cv;
    std::atomic<bool> done;
    
    
};

#endif