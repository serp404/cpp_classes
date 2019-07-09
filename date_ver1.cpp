#include <iostream>
#include <array>
#include <stdexcept>
using namespace std;

const array<int, 12> leap{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const array<int, 12> not_leap{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date {
private:
    int day, month, year;

    bool is_leap() const {
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    }

public:
    Date(int d, int m, int y) {
        if (d < 1 || d > 31 || m < 1 || m > 12) {
            throw invalid_argument("day, month, year");
        } else if (((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) && d > leap[m - 1]) {
            throw invalid_argument("day, month, year");
        } else if (!((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) && d > not_leap[m - 1]) {
            throw invalid_argument("day, month, year");
        } else {
            day = d;
            month = m;
            year = y;
        }
    }

    int GetDay() const {
        return day;
    }

    int GetMonth() const {
        return month;
    }

    int GetYear() const {
        return year;
    }

    Date& operator ++() {
        if (day < 28) {
            day++;
            return *this;
        } else {
            day++;
            if (is_leap() && day > leap[month - 1]) {
                day = 1;
                month++;
            } else if (!is_leap() && day > not_leap[month - 1]) {
                day = 1;
                month++;
            }
            if (month > 12) {
                month = 1;
                year++;
            }
            return *this;
        }
    }

    Date& operator --() {
        if (day > 1) {
            day--;
            return *this;
        } else {
            if (month == 1) {
                day = 31;
                month = 12;
                year--;
                return *this;
            } else {
                month--;
                if (is_leap()) {
                    day = leap[month - 1];
                } else {
                    day = not_leap[month - 1];
                }
                return *this;
            }
        }
    }

    Date operator + (int n) {
        Date ans = *this;
        if (n >= 0) {
            for (size_t i = 0; i != n; ++i) {
                ++ans;
            }
        } else {
            for (size_t i = 0; i != n; --i) {
                --ans;
            }
        }
        return ans;
    }

    Date operator - (int n) {
        Date ans = *this;
        if (n >= 0) {
            for (size_t i = 0; i != n; ++i) {
                --ans;
            }
        } else {
            for (size_t i = 0; i != n; --i) {
                ++ans;
            }
        }
        return ans;
    }

    int operator - (const Date& other) {
        int d1 = 0, d2 = 0;

        for (int i = 1970; i != year; ++i) {
            if (Date(1, 1, i).is_leap())
                d1 += 366;
            else
                d1 += 365;
        }

        for (int i = 1; i != month; ++i) {
            if (is_leap())
                d1 += leap[i - 1];
            else
                d1 += not_leap[i - 1];
        }
        d1 += day;

        for (int i = 1970; i != other.year; ++i) {
            if (Date(1, 1, i).is_leap())
                d2 += 366;
            else
                d2 += 365;
        }

        for (int i = 1; i != other.month; ++i) {
            if (other.is_leap())
                d2 += leap[i - 1];
            else
                d2 += not_leap[i - 1];
        }
        d2 += other.day;
        return d1 - d2;
    }
};
