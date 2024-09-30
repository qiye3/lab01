#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;
#include "../task/Task.hpp"


string current_time() {
    auto now = std::chrono::system_clock::now();
    time_t now_c = std::chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
