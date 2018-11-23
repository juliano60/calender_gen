#include "TextCalendarGenerator.hpp"
#include "Date.hpp"
#include <cassert>
#include <array>
#include <iomanip>

namespace chrono {

    TextCalendarGenerator::TextCalendarGenerator(std::ostream& out):
        out_{out}
    {}

    void TextCalendarGenerator::generateFor(int year) {
        outputYear(year);
        Date dd{year};

        outputYearCalendar(dd);
    }

    void TextCalendarGenerator::outputYear(int year) {
        out_ << year << "\n\n";
    }

    void TextCalendarGenerator::outputYearCalendar(Date dd) {
        for (Month i = Month::jan; i != Month::end; ++i) {
            outputMonthCalendar(dd);
        }
    }

    void TextCalendarGenerator::outputMonthCalendar(Date& dd) {
        outputMonth(static_cast<int>(dd.getMonth()));
        outputWeekdaysHeader();
        outputCalendar(dd);
    }

    void TextCalendarGenerator::outputMonth(int m) {
        static std::array<std::string, 12> monthTbl = {
                    "January", "February", "March", "April",
                    "May", "June", "July", "August",
                    "September", "October", "November", "December"};

        assert(m >= 0 && m < 12);

        out_ << monthTbl[m] << "\n"; 
    }

    void TextCalendarGenerator::outputWeekdaysHeader() {
        static std::array<std::string, 7> weekTbl = {
                    "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"
        };
        constexpr bool displayWeekNo = true;

        if (displayWeekNo) {
            out_ << "Wk ";
        }

        for (const auto& wk: weekTbl) {
            out_ << wk << " ";
        }

        out_ << "\n"; 
    }

    void TextCalendarGenerator::outputCalendar(Date& dd) {
        int day = 1;
        DayOfWeek dow = dd.getDayOfWeek();
        constexpr bool displayWeekNo = true;

        // output week number
        if (displayWeekNo && dow != DayOfWeek::mon) {
            out_ << std::setw(2) << dd.getWeekNo() << " ";
        }

        // output space before first day
        for (DayOfWeek i = DayOfWeek::mon; i != dow; ++i) {
            out_ << "   ";
        }

        Month mm = dd.getMonth();

        while (mm == dd.getMonth()) {
            if (dd.getDayOfWeek() == DayOfWeek::mon) {
                if (displayWeekNo) {
                    out_ << std::setw(2) << dd.getWeekNo() << " ";
                }
            }
                
            out_ << std::setw(2) << day << " ";

            if (dd.getDayOfWeek() == DayOfWeek::sun) {
                out_ << "\n";
            }

            dd.addDay();
            ++day;
        } 
        out_ << "\n\n";
    }

}
