#include "Common.h"

#ifndef ORDER_H
#define ORDER_H

enum class OrderType { BUY, SELL };

struct Order {
    uint32_t id;
    OrderType side;
    double price;
    uint32_t quantity;

};
std::ostream& operator<<(std::ostream& os, const Order& order);

#endif