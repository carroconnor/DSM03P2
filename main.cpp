#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <stdexcept>
#include "BugReport.h"
//#include "priorityQueue.h"

/* Program name: priorityQueue.cpp
* Author: Carr O'Connor
* Date last updated: 5/1/2017
* Purpose: Implement a priority queue using a linked list.
*/

// For the main program, you will create a bug-tracking system for a piece of software. You will utilize the provided BugReport class to get bug reports from the user and give the highest priority reports to a developer. 
// The program will run off of a menu with 3 options 1. Enter bug report 2. Distribute bug report 3. Quit. When the user chooses option 1 the program will gather the information for the bug report, and store it in a BugReport object. 
// Utilize regular expressions to validate the report date. See the sample run below for an example of the input provided by the test.  When the user chooses option 2, grab the first bug report from the queue display it to the user, 
// and add it to a linked list of completed BugReports.For option 3, display all of the completed BugReports from the linked list, then empty all of the bug reports from the queue and display the uncompleted bug reports.

void printMenu();
void resetStream();
int inputInt(std::string prompt, int min, int max);

int main(){
    int id = 0;
    std::regex datePattern("([0-9]{4})-([0-9]{2})-([0-9]{2})");

    while(true){
        printMenu();
        int choice = inputInt("Enter choice: ", 1, 3);

        std::smatch match;
        std::string date;
        std::string description;
        std::string reporter;
        int priority;

        switch(choice){
            case 1:
                std::cout << "Enter the date of the report (yyyy-mm-dd): ";
                std::cin >> date;
                if(std::regex_match(date, match, datePattern)){
                    std::cin.ignore(); // To ignore the remaining newline character from previous input
                    std::cout << "Enter the name of the reporter: ";
                    std::getline(std::cin, reporter);
                    std::cout << "Describe the bug: ";
                    std::getline(std::cin, description);
                    priority = inputInt("What is the priority 1 - 10 (1 is low, 10 is high): ", 1, 10);
                    BugReport report(id++, description, reporter, "new", priority, date);
                } else {
                    std::cout << "Invalid date format. Please enter the date in the format yyyy-mm-dd." << std::endl;
                }
                break;
            case 2:
                // Distribute bug report
                break;
            case 3:
                return 0;
        }
    }
    return 0;
}

void printMenu(){
    std::stringstream ss;
    ss << "1. Enter bug report\n";
    ss << "2. Distribute bug report\n";
    ss << "3. Quit\n";
    std::cout << ss.str();
}

int inputInt(std::string prompt, int min, int max){
    int result;

    if(prompt.length() > 0){
        std::cout << prompt << std::endl; 
    }
    std::cin >> result; 

    while(result < min || result > max){
        std::cout << "That is an invalid choice.";
        resetStream();
        std::cin >> result;
    }
    
    return result;
}

void resetStream(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}