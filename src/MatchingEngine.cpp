#include "MatchingEngine.h"

void MatchingEngine
::addOrder(const Order& order) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        orderQueue.push(order);
    }
    cv.notify_one();
    MSG(2, "Push order done");
}

void MatchingEngine
::processOrders(void){

    Order order;
    MSG(1, "start");
    while( !done || !orderQueue.empty() ){
        std::unique_lock<std::mutex> lock(queueMutex);
        auto func1 = [this] { return !orderQueue.empty() || done; };
        cv.wait(lock, func1);
        // MSG("start check orderQueue");
        while( !orderQueue.empty() ){
            order = orderQueue.front();
            orderQueue.pop();
            if (order.side == OrderType::BUY) {
                buy_orders[order.price].push_back(order);
            } else {
                sell_orders[order.price].push_back(order);
            }
            this->matchOrders();
        }
    }
}
void MatchingEngine
::matchOrders(void){
    if( buy_orders.empty() || sell_orders.empty() )return;
    // Get highest buy price & lowest sell price
    auto best_buy = buy_orders.begin();
    auto best_sell = sell_orders.begin();
    // match requirement
    if (best_buy->first < best_sell->first) return;
    // Get both order
    Order& buy_order = best_buy->second.front();
    Order& sell_order = best_sell->second.front();

    uint32_t trade_qty = std::min(buy_order.quantity, sell_order.quantity);
    MSG(1, "Trade match successful => price: " << sell_order.price << ", Quantity: " << trade_qty);

    buy_order.quantity -= trade_qty;
    sell_order.quantity -= trade_qty;

    if (buy_order.quantity == 0) best_buy->second.pop_front();
    if (sell_order.quantity == 0) best_sell->second.pop_front();

    if (best_buy->second.empty()) buy_orders.erase(best_buy);
    if (best_sell->second.empty()) sell_orders.erase(best_sell);
}