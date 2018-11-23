#ifndef DATE_HPP
#define DATE_HPP

#include <stdexcept>
#include <string>
#include <utility>

// a basic Date utility class
// The representation uses the number of days
// since 1st January 1582, which happens to be
// a Monday.

namespace chrono {

    enum class DayOfWeek {
        mon=0,tue,wed,thu,fri,sat,sun,end
    };

    DayOfWeek& operator++(DayOfWeek&);

    enum class Month {
        jan=0,feb,mar,apr,may,jun,
        jul,aug,sep,oct,nov,dec,end
    };

    Month& operator++(Month&);

    class InvalidDate: public std::runtime_error {
    public:
        explicit InvalidDate(const std::string& msg);
    }; 

    class Date {
    public:
        // construct a Date corresponding
        // to the 1st January of a given year
        explicit Date(int year);

        DayOfWeek getDayOfWeek() const;
        Month getMonth() const;
        int getWeekNo() const;

        // increase the number of days by one
        void addDay();

    private:
        std::pair<long,int> daysInCurrentYearAndYear() const;

    private:
        long days_;    
    }; 

    bool isLeapYear(int year);
    int daysInYear(int year);
}

#endif
