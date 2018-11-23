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
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::mon);

    dd = Date{1583};
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::sat);

    dd = Date{1700};
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::fri);

    // 1st January 2018 is a monday 
    dd = Date{2018};
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::mon);
}

TEST_CASE ("canAddDays") {
    Date dd{2018};

    dd.addDay();
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::tue);

    dd.addDay();
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::wed);

    dd.addDay();
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::thu);
}

TEST_CASE ("weekNumberTests1") {
    // 1st January 2017 is a Sunday
    Date dd{2017};
    REQUIRE(dd.getWeekNo() == 1);

    for (int i = 0; i != 31; ++i)
        dd.addDay();

    REQUIRE(dd.getMonth() == Month::feb);
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::wed);
    REQUIRE(dd.getWeekNo() == 6);

    dd.addDay();//Thur
    REQUIRE(dd.getWeekNo() == 6);
    dd.addDay();//Frid
    REQUIRE(dd.getWeekNo() == 6);
    dd.addDay();//Sat
    REQUIRE(dd.getWeekNo() == 6);
    dd.addDay();//Sun
    REQUIRE(dd.getWeekNo() == 6);
    dd.addDay();//Mon
    REQUIRE(dd.getWeekNo() == 7);
}

TEST_CASE ("testWeekNumbers2") {
    // 1st January 2018 is a Monday 
    Date dd{2018};
    REQUIRE(dd.getWeekNo() == 1);

    for (int i = 0; i != 31; ++i)
        dd.addDay();

    REQUIRE(dd.getMonth() == Month::feb);
    REQUIRE(dd.getDayOfWeek() == DayOfWeek::thu);
    REQUIRE(dd.getWeekNo() == 5);
}
