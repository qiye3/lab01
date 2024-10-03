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

// 计算距离截止日期还有多少天
int calculate_left_days(string deadline) {
    int year, month, day;
    char dash;
    stringstream ss(deadline);
    ss>>year>>dash>>month>>dash>>day;

    time_t now = time(0);
    tm* currentTime = localtime(&now);

    int currentYear = 1900 + currentTime->tm_year;
    int currentMonth = 1 + currentTime->tm_mon;
    int currentDay = currentTime->tm_mday;

    tm deadlineDate = {0};
    deadlineDate.tm_year = year - 1900;
    deadlineDate.tm_mon = month - 1;
    deadlineDate.tm_mday = day;

    time_t deadlineTime = mktime(&deadlineDate);
    time_t currentTimeSeconds = mktime(currentTime);

    double differenceInSeconds = difftime(deadlineTime, currentTimeSeconds);
    int differenceInDays = differenceInSeconds / (60 * 60 * 24);

    return differenceInDays;
}