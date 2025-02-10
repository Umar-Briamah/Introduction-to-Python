#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Event class to represent individual events
class Event {
public:
    std::string name;
    std::string startTime;
    std::string endTime;

    Event(const std::string& name, const std::string& startTime, const std::string& endTime)
        : name(name), startTime(startTime), endTime(endTime) {}
};

// Calendar class to hold a collection of events and generate the .ics content
class Calendar {
private:
    std::vector<Event> events;
    
public:
    void addEvent(const std::string& name, const std::string& startTime, const std::string& endTime) {
        events.emplace_back(name, startTime, endTime);
    }

    // Generate the .ics format string
    std::string generateICS() {
        std::stringstream icsContent;
        icsContent << "BEGIN:VCALENDAR\n";
        icsContent << "VERSION:2.0\n";
        icsContent << "CALSCALE:GREGORIAN\n";

        for (const auto& event : events) {
            icsContent << "BEGIN:VEVENT\n";
            icsContent << "SUMMARY:" << event.name << "\n";
            icsContent << "DTSTART:" << event.startTime << "\n";
            icsContent << "DTEND:" << event.endTime << "\n";
            icsContent << "END:VEVENT\n";
        }

        icsContent << "END:VCALENDAR\n";
        return icsContent.str();
    }

    // Save the .ics content to a file
    void saveToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << generateICS();
            outFile.close();
            std::cout << "Calendar saved to " << filename << std::endl;
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }

    // Read the .ics file content (basic read without parsing the events)
    void readFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        std::string line;
        if (inFile.is_open()) {
            while (std::getline(inFile, line)) {
                std::cout << line << std::endl;
            }
            inFile.close();
        } else {
            std::cerr << "Unable to open file for reading." << std::endl;
        }
    }
};

int main() {
    // Create a calendar object
    Calendar cal;

    // Add events to the calendar
    cal.addEvent("Meeting with John", "20250210T100000", "20250210T120000");
    cal.addEvent("Doctor Appointment", "20250212T150000", "20250212T160000");

    // Save the calendar to an ICS file
    cal.saveToFile("my_calendar.ics");

    // Read and display the contents of the ICS file
    std::cout << "\nReading the calendar from the .ics file:\n";
    cal.readFromFile("my_calendar.ics");

    return 0;
}
