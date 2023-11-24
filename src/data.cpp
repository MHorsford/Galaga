#include "data.h"
#include <ctime>
#include <sstream>

Data::Data() {
    time_t t = time(0);
    struct tm* now = localtime(&t);

    day = now->tm_mday;
    month = now->tm_mon + 1;
    year = now->tm_year + 1900;
}

Data::Data(int day, int month, int year) : day(day), month(month), year(year) {}

int Data::getDay() const {
    return day;
}

int Data::getMonth() const {
    return month;
}

int Data::getYear() const {
    return year;
}

std::string Data::toString() const {
    std::stringstream ss;
    ss << day << "/" << month << "/" << year;
    return ss.str();
}
