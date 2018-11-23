#ifndef HTML_CALENDAR_GENERATOR_HPP
#define HTML_CALENDAR_GENERATOR_HPP

#include "CalendarGenerator.hpp"
#include <iostream>

namespace chrono {

    class HtmlCalendarGenerator: public CalendarGenerator {
    public:
        explicit HtmlCalendarGenerator(std::ostream&);

        void generateFor(int year) override;
    
    private:
        std::ostream& out_;
    };

}

#endif
