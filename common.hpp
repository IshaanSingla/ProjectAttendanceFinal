#ifndef DATE_HEADER
#define DATE_HEADER

#include <iostream>

class Date {
private:
    int day;

    int month;
    int year;

    bool isLeapYear(int y) const {
        return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
    }

    int daysInMonth() const {
        if (month == 4 || month == 6 || month == 9 || month == 11)
            return 30;
        else if (month == 2)
            return isLeapYear(year) ? 29 : 28;
        else
            return 31;
    }

public:
    Date() : day(0), month(0), year(0) {}

    Date(const std::string &date) {
        if (date.length() != 8) {
            day = 0;
            month = 0;
            year = 0;
            return;
        }

        day = ((date[0] - 48) * 10) + (date[1] - 48);
        month = ((date[3] - 48) * 10) + (date[4] - 48);
        year = ((date[6] - 48) * 10) + (date[7] - 48);

        if (!isValid()) {
            day = 0;
            month = 0;
            year = 0;
        }
    }

    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }

    bool isValid() const {
        if (month < 1 || month > 12 || day < 1)
            return false;

        int daysInMonth = this->daysInMonth();
        return day <= daysInMonth;
    }

    bool operator==(Date obj)
    {
        return (this->day == obj.day)&&(this->month == obj.month)&&(this->year == obj.year);
    }
};
template <typename T, typename U>
struct combine
{
    T first;
    U second;
};
class User
{
protected:
    std::string username;
    std::string password;
    bool loggedIn;
public:
    User(): username(""),password(""),loggedIn(false) {}
    
};

#endif
