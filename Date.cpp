#include "Date.hpp"

namespace {
    constexpr int startYear = 1582;
}

namespace chrono {

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
            if (yy == startYear) {
                // 10 days were dropped in year 1582
                days_ += 355;
            }
            else if (isLeapYear(yy)) {
                days_ += 366;
            }
            else {
                days_ += 365;
            }
        } 
    } 

    void Date::addDay() noexcept {
        ++days_;
    }

    DayOfWeek Date::getDayOfWeek() const noexcept {
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

}
