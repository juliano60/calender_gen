#include "catch.hpp"
#include "Date.hpp"

using namespace chrono;

TEST_CASE ("testLeapYears") {
    REQUIRE_FALSE(isLeapYear(1700));
    REQUIRE_FALSE(isLeapYear(1800));
    REQUIRE_FALSE(isLeapYear(1900));
    REQUIRE(isLeapYear(1996));
    REQUIRE(isLeapYear(2000));
}

TEST_CASE ("basicDateTest") {
    Date dd{1582};
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::Mon);

    dd = Date{1583};
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::Sat);

    dd = Date{1700};
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::Fri);

    // 1st January 2018 is a Monday 
    dd = Date{2018};
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::Mon);
}
/*
TEST_CASE ("canAddDays") {
    Date dd{2018};

    dd.addDay();
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::Tue);

    dd.addDay();
    // 1st January 2018 is a Monday 
    Date dd3{1700};
    REQUIRE(dd3.getDayOfWeek() == DayOfWeek::Mon);

    Date dd4{1751};
    REQUIRE(dd4.getDayOfWeek() == DayOfWeek::Tue);

    Date dd5{2018};
    REQUIRE(dd5.getDayOfWeek() == DayOfWeek::Mon);
}
TEST_CASE ("canAddDays") {
    Date dd{2018};

    dd.addDay();
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::Tue);

    dd.addDay();
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::Wed);

    dd.addDay();
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::Thu);
}
*/
