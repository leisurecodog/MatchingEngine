#include "Order.h"

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Order(id=" << order.id
       << ", side=" << (order.side == OrderType::BUY ? "BUY" : "SELL")
       << ", price=" << order.price
       << ", quantity=" << order.quantity
       << ")";
    return os;
}