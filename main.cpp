// limit_order_only
// TODO for future: market price, ROD, IOC, FOK
#include "MatchingEngine.h"
#include "OrderGenerator.h"
int main() {
    MatchingEngine engine;
    OrderGenerator generator;
    std::vector<Order> orders;

    engine.start();

    generator.GenOrder(100, orders);

    for (const auto& order : orders) {
        engine.addOrder(order);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
