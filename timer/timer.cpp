#include "timer.hpp"


long long timer::get_time() {
    auto current_time = std::chrono::system_clock::now();
    auto currentTimeAsTimeT = std::chrono::time_point_cast<std::chrono::microseconds>(current_time);
    auto time = currentTimeAsTimeT.time_since_epoch().count();
    return time;
}