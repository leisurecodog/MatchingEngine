#include "Common.h"
#include "MatchingEngine.h"
class OrderGenerator{

private:
    /* data */
public:
    OrderGenerator(/* args */) = default;
    ~OrderGenerator() = default;
    void GenOrder(const uint32_t&& len, vector<Order>& vec){
        std::random_device rd;                         // 隨機種子來源（非確定性）
        std::mt19937 gen(rd());                        // Mersenne Twister 引擎
        std::uniform_int_distribution<> dist_qty(0, 100);
        std::uniform_real_distribution<> dist_price(95.0, 105.0);
        OrderType tp;
        for(uint32_t i=0; i<len; i++){
            auto qty = dist_qty(gen);
            tp = (qty % 2 == 0 ? OrderType::BUY : OrderType::SELL);
            vec.push_back({i, tp, dist_price(gen), (uint32_t)qty});
        }
        // for(auto ele: vec)
        //     cout << ele << endl;
    }
};
