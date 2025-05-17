#include "order.h"

void OrderBook
::add_order(const Order& order) {
    if (order.side == OrderType::BUY) {
        buy_orders[order.price].push_back(order);
    } else {
        sell_orders[order.price].push_back(order);
    }
    match();
}

void OrderBook
::match(void){
    while (!buy_orders.empty() && !sell_orders.empty()) {
        // Get highest buy price & lowest sell price
        auto best_buy = buy_orders.begin();
        auto best_sell = sell_orders.begin();
        // match requirement
        if (best_buy->first < best_sell->first) break;
        // Get order
        Order& buy_order = best_buy->second.front();
        Order& sell_order = best_sell->second.front();

        uint32_t trade_qty = std::min(buy_order.quantity, sell_order.quantity);
        std::cout << "Trade match successful => price: " << sell_order.price << ", Quantity: " << trade_qty << endl;

        buy_order.quantity -= trade_qty;
        sell_order.quantity -= trade_qty;

        if (buy_order.quantity == 0) best_buy->second.pop_front();
        if (sell_order.quantity == 0) best_sell->second.pop_front();

        if (best_buy->second.empty()) buy_orders.erase(best_buy);
        if (best_sell->second.empty()) sell_orders.erase(best_sell);
    }
}