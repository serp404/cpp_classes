#include <iostream>
#include <array>
#include <stdexcept>
using namespace std;

const array<int, 12> leap{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const array<int, 12> not_leap{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

class Date {
private:
    int days_since_beginning;

    array<int, 3> convert_to_date() const {
        int i = 1970;
        int temp = 365;
        int current_days = this->days_since_beginning;
        int day, month, year;
        while (current_days > temp) {
            current_days -= temp;
            i++;
            if (is_leap(i))
                temp = 366;
            else
                temp = 365;
        }
        year = i;
        i = 1;
        if (is_leap(year)) {
            while (current_days > leap[i - 1]) {
                current_days -= leap[i - 1];
                i++;
            }
        } else {
            while (current_days > not_leap[i - 1]) {
                current_days -= not_leap[i - 1];
                i++;
            }
        }
        month = i;
        day = current_days;
        return {day, month, year};
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
            days_since_beginning = 0;
            for (int i = 1970; i != y; ++i) {
                if (is_leap(i))
                    days_since_beginning += 366;
                else
                    days_since_beginning += 365;
            }

            for (int i = 1; i != m; ++i) {
                if (is_leap(y))
                    days_since_beginning += leap[i - 1];
                else
                    days_since_beginning += not_leap[i - 1];
            }
            days_since_beginning += d;
        }
    }

    int GetDay() const {
        return convert_to_date()[0];
    }

    int GetMonth() const {
        return convert_to_date()[1];
    }

    int GetYear() const {
        return convert_to_date()[2];
    }

    Date& operator ++() {
        days_since_beginning++;
        return *this;
    }

    Date& operator --() {
        days_since_beginning--;
        return *this;
    }

    Date operator + (int n) {
        Date ans = *this;
        ans.days_since_beginning += n;
        return ans;
    }

    Date operator - (int n) {
        Date ans = *this;
        ans.days_since_beginning -= n;
        return ans;
    }

    int operator - (const Date& other) {
        return days_since_beginning - other.days_since_beginning;
    }
};
