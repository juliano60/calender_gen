#ifndef CALENDAR_GENERATOR
#define CALENDAR_GENERATOR

// calendar generator interface
// Note we only support the Gregorian Calendar.
// The earliest supported date is October 1582.
// See https://en.wikipedia.org/wiki/Gregorian_calendar for
// more info.

namespace chrono {

    class CalendarGenerator {
    public:
        virtual ~CalendarGenerator() =default;

        // generate a calendar for a given year
        // throws an InvalidDate exception if the year
        // is before 1582.
        virtual void generateFor(int year) =0;
    }; 

}

#endif
