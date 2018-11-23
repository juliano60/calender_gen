#ifndef TEXT_CALENDAR_GENERATOR_HPP
#define TEXT_CALENDAR_GENERATOR_HPP

#include "CalendarGenerator.hpp"
#include <iostream>

namespace chrono {
    class Date;

    class TextCalendarGenerator: public CalendarGenerator {
    public:
        explicit TextCalendarGenerator(std::ostream&);

        void generateFor(int year) override;
    
    private:
        void outputYear(int);
        void outputMonth(int m);
        void outputWeekdaysHeader();
        void outputYearCalendar(Date);
        void outputMonthCalendar(Date&);
        void outputCalendar(Date&);
        
    private:
        std::ostream& out_;
    };

}

#endif
