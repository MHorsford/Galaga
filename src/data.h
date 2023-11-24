#ifndef DATA_H
#define DATA_H

#include <string>

class Data {
public:
    Data();
    Data(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    std::string toString() const;

private:
    int day;
    int month;
    int year;
};

#endif
