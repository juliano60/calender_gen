#ifndef HTML_CALENDAR_GENERATOR_HPP
#define HTML_CALENDAR_GENERATOR_HPP

#include "CalendarGenerator.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace chrono {
    class Date;

    class HtmlCalendarGenerator: public CalendarGenerator {
    public:
        explicit HtmlCalendarGenerator(std::ostream&);

        void generateFor(int year) override;
    
    private:
        void outputYear(int);
        void outputMonth(int m);
        void outputWeekdaysHeader();
        void outputYearCalendar(Date);
        void outputMonthCalendar(Date&);
        void outputCalendar(Date&);

        void outputHtmlElement(const std::string& element, const std::string& content,
                const std::string& attrs="");
        void outputOpeningTag(const std::string& element, const std::string& attrs="");
        void outputClosingTag(const std::string& element);
        void outputTableRow(const std::vector<int>& row);
        void outputInlineCss();
        void outputNewline();
        std::string getCssClass(int col) const;
        
    private:
        std::ostream& out_;
        bool displayWeekNo_;
        std::size_t rowSize_;
    };

}

#endif
