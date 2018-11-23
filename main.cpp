#include "CalendarGenerator.hpp"
#include "TextCalendarGenerator.hpp"
#include "HtmlCalendarGenerator.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <memory>

// Notes:
// = we have added an extra command-line argument (html|text) solely for testing purposes
// and it is purely optional. In fact we do not validate this argument in the code. 
// 

enum class GeneratorType {
    html, text
};

void displayHelp();
std::unique_ptr<chrono::CalendarGenerator> makeGenerator(GeneratorType t, std::ostream&);
void generateCalendar(int year, std::ostream& out, GeneratorType t); 

int main(int argc, char* argv[]) {
    try {
        if (argc == 3 || argc == 4) {
            GeneratorType t = argc == 3 ? GeneratorType::html : GeneratorType::text;
            int year = std::stoi(argv[1]);
            std::ofstream ofs{argv[2]};

            if (!ofs) {
                std::cerr << "Error opening file : " << argv[2] << "\n";
                return 1;
            }

            generateCalendar(year, ofs, t);
        }
        else {
            throw std::invalid_argument{"Invalid argument supplied"};
        }
    }
    catch (std::invalid_argument& e) {
        // the year supplied was invalid
        displayHelp();
        return 2;
    }
    catch (std::exception& e) {             
        std::cerr << e.what() << "\n";
        return 3;
    }
    catch (...) {
        std::cerr << "An error occurred\n";
        return 4;
    }

    return 0;
}

void displayHelp() {
    std::cerr << "Usage: calendar_gen <year> <filename> [html|text]\n"
            << "Generate a Gregorian calendar for year-1, year and year+1 and output to a file.\n\n"
            << "  year,\t\t\tthe year to generate the calendar for. A calendar\n"
            << "\t\t\twill also be generated for year-1 and year+1. The minimum value\n"
            << "\t\t\tsupported is 1583.\n"
            << "  filename,\t\tthe output filename.\n"
            << "  [html|text],\t\tif supplied controls whether the output format is html or text.\n"
            << "\t\t\tThe default is html.\n";
}

std::unique_ptr<chrono::CalendarGenerator> makeGenerator(GeneratorType t, 
    std::ostream& ofs)
{
    switch (t) {
    case GeneratorType::html:
        return std::unique_ptr<chrono::CalendarGenerator>(
                        new chrono::HtmlCalendarGenerator(ofs));
    case GeneratorType::text:
        return std::unique_ptr<chrono::CalendarGenerator>(
                        new chrono::TextCalendarGenerator(ofs));
    default:
        throw std::invalid_argument{"Unsupported generator type"};
    }
}

void generateCalendar(int year, std::ostream& out, GeneratorType t) {
    auto calendar = makeGenerator(t, out);

    for (int yy = year-1; yy != year+2; ++yy) {
        calendar->generateFor(yy);
    }
}
