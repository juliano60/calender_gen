#include "HtmlCalendarGenerator.hpp"
#include "Date.hpp"
#include <cassert>
#include <array>
#include <iomanip>

namespace {
    constexpr size_t rowSizeNoWeekNo = 7;
    constexpr size_t rowSizeWithWeekNo = 8;
}

namespace chrono {

    HtmlCalendarGenerator::HtmlCalendarGenerator(std::ostream& out):
        out_{out},
        displayWeekNo_{true},
        rowSize_{displayWeekNo_ ? rowSizeWithWeekNo: rowSizeNoWeekNo}
    {}

    void HtmlCalendarGenerator::generateFor(int year) {
        outputYear(year);
        Date dd{year};

        outputOpeningTag("html");
        outputInlineCss();
        outputOpeningTag("body");
        outputYearCalendar(dd);
        outputOpeningTag("body");
        outputClosingTag("html");
    }

    void HtmlCalendarGenerator::outputInlineCss() {
        outputOpeningTag("head");
        outputOpeningTag("style");
        out_ << "table, th, tr, td {\n"
            << "  border: 1px solid black;\n"
            << "}\n"
            << ".month {\n"
            << "  background-color: #ddffcc;\n"
            << "}\n"
            << ".weekNo {\n"
            << "  background-color: #ccddff\n"
            << "}\n"
            << ".saturday {\n"
            << "  background-color: #ffdd99\n"
            << "}\n"
            << ".sunday {\n"
            << "  background-color: #ff704d\n"
            << "}\n"
            << ".regularDay {\n"
            << "  background-color: #ffff99\n"
            << "}\n";
        outputClosingTag("style");
        outputClosingTag("head");
    }

    void HtmlCalendarGenerator::outputNewline() {
        out_ << "<br/>";
    }

    void HtmlCalendarGenerator::outputHtmlElement(const std::string& element,
        const std::string& content,
        const std::string& attrs)
    {
        out_ << "<" << element;

        if (!attrs.empty()) {
            out_ << " " << attrs;
        }

        out_ << ">"
            << content
            << "</" << element << ">\n";
    }

    void HtmlCalendarGenerator::outputOpeningTag(const std::string& element,
        const std::string& attrs) {

        if (!attrs.empty()) {
            out_ << "<" << element << " " << attrs << ">\n";
        }
        else {
            out_ << "<" << element << ">\n";
        }
    }

    void HtmlCalendarGenerator::outputClosingTag(const std::string& element) {
        out_ << "</" << element << ">\n";
    }

    std::string HtmlCalendarGenerator::getCssClass(int col) const {
        if (displayWeekNo_) {
            if (col == 0) return "weekNo";
            else if (col == 6) return "saturday";
            else if (col == 7) return "sunday";
            else return "regularDay";
        }
        else {
            if (col == 0) return "weekNo";
            else if (col == 5) return "saturday";
            else if (col == 6) return "sunday";
            else return "regularDay";
        }
    } 

    void HtmlCalendarGenerator::outputTableRow(const std::vector<int>& row) {
        outputOpeningTag("tr");

        for (std::size_t i = 0; i != row.size(); ++i) {
            if (row[i] == 0) outputHtmlElement("td", " ", "class=\"" + getCssClass(i) + "\"");
            else outputHtmlElement("td", std::to_string(row[i]), "class=\"" + getCssClass(i) + "\"");
        }

        outputClosingTag("tr");
    } 

    void HtmlCalendarGenerator::outputYear(int year) {
        outputHtmlElement("h2", std::to_string(year));
    }

    void HtmlCalendarGenerator::outputYearCalendar(Date dd) {
        for (Month i = Month::jan; i != Month::end; ++i) {
            outputMonthCalendar(dd);
        }
    }

    void HtmlCalendarGenerator::outputMonthCalendar(Date& dd) {
        outputOpeningTag("table");

        outputOpeningTag("tr");
        outputMonth(static_cast<int>(dd.getMonth()));
        outputClosingTag("tr");

        outputOpeningTag("tr");
        outputWeekdaysHeader();
        outputClosingTag("tr");

        outputCalendar(dd);
        outputClosingTag("table");
        outputNewline();
        outputNewline();
    }

    void HtmlCalendarGenerator::outputMonth(int m) {
        static std::array<std::string, 12> monthTbl = {
                    "January", "February", "March", "April",
                    "May", "June", "July", "August",
                    "September", "October", "November", "December"};

        assert(m >= 0 && m < 12);

        outputHtmlElement("th", monthTbl[m], "class=\"month\" colspan=\"" + 
                                    std::to_string(rowSize_) + "\"");
    }

    void HtmlCalendarGenerator::outputWeekdaysHeader() {
        static std::array<std::string, 7> weekTbl = {
                    "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"
        };

        if (displayWeekNo_) {
            outputHtmlElement("td", "Wk", "class=\"" + getCssClass(0) + "\"");
        }

        for (const auto&x: weekTbl) {
            std::string klass = (x == "Sa") ? "saturday":
                        (x == "Su") ? "sunday":
                        "weekNo";

            outputHtmlElement("td", x, "class=\"" + klass + "\"");
        }
    }

    void HtmlCalendarGenerator::outputCalendar(Date& dd) {
        int day = 1;
        DayOfWeek dow = dd.getDayOfWeek();

        std::vector<int> rowNumbers;

        // output week number
        if (displayWeekNo_ && dow != DayOfWeek::mon) {
            rowNumbers.push_back(dd.getWeekNo());
        }

        // output space before first day
        for (DayOfWeek i = DayOfWeek::mon; i != dow; ++i) {
            rowNumbers.push_back(0);
        }

        Month mm = dd.getMonth();

        while (mm == dd.getMonth()) {
            if (dd.getDayOfWeek() == DayOfWeek::mon) {
                if (displayWeekNo_) {
                    rowNumbers.push_back(dd.getWeekNo());
                }
            }

            rowNumbers.push_back(day); 

            if (dd.getDayOfWeek() == DayOfWeek::sun) {
                outputTableRow(rowNumbers);
                rowNumbers.clear();
            }

            dd.addDay();
            ++day;
        } 

        if (!rowNumbers.empty()) {
            // pad row
            while (rowNumbers.size() != rowSize_) {
                rowNumbers.push_back(0);
            }

            outputTableRow(rowNumbers);
        }
    }

}
