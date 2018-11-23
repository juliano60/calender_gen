#include "Date.hpp"
#include <array>
#include <cassert>

namespace {
    constexpr int startYear = 1582;
}

namespace chrono {

    DayOfWeek& operator++(DayOfWeek& dow) {
        assert(dow != DayOfWeek::end);

        dow = static_cast<DayOfWeek>(static_cast<int>(dow)+1);
        return dow;
    }

    Month& operator++(Month& mon) {
        assert(mon != Month::end);

        mon = static_cast<Month>(static_cast<int>(mon)+1);
        return mon;
    }

    InvalidDate::InvalidDate(const std::string& msg):
        std::runtime_error{msg}
    {}

    Date::Date(int year): 
        days_{0} 
    {
        if (year < startYear) {
            throw InvalidDate{"Date() - Date not supported"};
        }

        for (int yy = startYear; yy != year; ++yy) {
            days_ += daysInYear(yy);
        } 
    } 

    void Date::addDay() {
        ++days_;
    }

    DayOfWeek Date::getDayOfWeek() const {
        int delta = static_cast<int>(days_ % 7);

        return static_cast<DayOfWeek>(delta);
    }

    // A leap is a year exactly divisible by four except for years that are
    // divisble by 100. If they are then they must also be divisible by
    // 400.
    // See definition: https://en.wikipedia.org/wiki/Gregorian_calendar
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) ||
            (year % 4 == 0 && year % 400 == 0);
    }

    int daysInYear(int year) {
        if (year == 1582) {
            // handle year 1582 separately
            return 355;
        }
        return isLeapYear(year) ? 366: 365;
    }

    std::pair<long,int> Date::daysInCurrentYearAndYear() const {
        long daysTemp = days_;

        int yy = startYear;
        while (true) {
            int days = daysInYear(yy);

            if (daysTemp < days) break;

            daysTemp -= days;
            ++yy;
        }
        return std::make_pair(daysTemp, yy);
    }

    // note there are many definitions of the week number
    // we are using the one where 1st January is always
    // in week 1.
    int Date::getWeekNo() const {
        long daysTemp = daysInCurrentYearAndYear().first;
        int dow = static_cast<int>(days_ % 7);

        int weekNo = 1;
        while (true) {
            if (daysTemp - 1 < 0) break;

            --daysTemp;
            --dow;

            if (dow < 0) {
                dow = 6;//Sunday
                ++weekNo;
            }
        }

        return weekNo;
    }

    // simple algorithm to determine the month.
    // substract as many years possible then as many months
    // as possible, then we should get the resulting month.
    Month Date::getMonth() const {
        auto daysAndYear = daysInCurrentYearAndYear();
        long daysTemp = daysAndYear.first;
        int yy = daysAndYear.second;

        static std::array<int, 12> monthDays = {
            31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
        };

        if (isLeapYear(yy)) monthDays[1] = 29;
        int mm = 0;
        while (true) {
            int daysInMonth = monthDays[mm];

            if (daysTemp < daysInMonth) break;

            daysTemp -= daysInMonth;
            ++mm;
        }

        assert(mm >= 0 && mm < 12);
        return static_cast<Month>(mm);
    }

}
