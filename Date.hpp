#ifndef DATE_HPP
#define DATE_HPP

#include <stdexcept>
#include <string>

// a basic Date utility class
// The representation uses the number of days
// since 1st October 1582, which happens to be
// a Monday.

namespace chrono {

    enum class DayOfWeek {
        Mon=0,Tue,Wed,Thu,Fri,Sat,Sun
    };

    class InvalidDate: public std::runtime_error {
    public:
        explicit InvalidDate(const std::string& msg);
    }; 

    class Date {
    public:
        // construct a Date corresponding
        // to the 1st January of a given year
        explicit Date(int year);

        DayOfWeek getDayOfWeek() const noexcept;

        // increase the number of days by one
        void addDay() noexcept;

    private:
        long days_;    
    }; 

    bool isLeapYear(int year);
}

#endif
