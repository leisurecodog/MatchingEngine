#include <iostream>
#include <map>
#include <deque>
#include <string>
#include <queue>
#include <cstdint>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <random>


using namespace std;
#define SHOW_LEVEL 1
#define MSG(LEVEL, x)  do{ if(LEVEL > SHOW_LEVEL)return; now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); std::cout << "[TIME] " << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "\t" << __FILE__ << " : " << __func__ << ":" << __LINE__ << "\t" << x << std::endl; }while(0)