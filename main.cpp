#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <stdexcept>
#include "BugReport.h"
#include "linkedQueue.h"
#include "priorityQueue.h"

/* Program name: priorityQueue.cpp
* Author: Carr O'Connor
* Date last updated: 5/1/2017
* Purpose: Implement a priority queue using a linked list.
*/

void printMenu();
void resetStream();
int inputInt(std::string prompt, int min, int max);
std::string getDate();

int main(){
    int id = 1;
    std::regex datePattern("^\\d{4}\\-(0?[1-9]|1[012])\\-(0?[1-9]|[12][0-9]|3[01])$");
    priorityQueueType<BugReport> priorityQueue;
    linkedQueueType<BugReport> completedQueue;
    priorityQueue.initializeQueue();
    completedQueue.initializeQueue();

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
                date = getDate();
                if(std::regex_match(date, match, datePattern)){
                    std::cin.ignore(); // To ignore the remaining newline character from previous input
                    std::cout << "Enter the name of the reporter: ";
                    std::getline(std::cin, reporter);
                    std::cout << "Describe the bug: ";
                    std::getline(std::cin, description);
                    priority = inputInt("What is the priority 1 - 10 (1 is low, 10 is high): ", 1, 10);
                    BugReport report(id++, description, reporter, "new", priority, date);
                    priorityQueue.enqueue(report);
                } else {
                    std::cout << "The date entered is not valid. Please check that the date entered is in the correct format." << std::endl;
                }
                break;
            case 2:
                if(!priorityQueue.isEmptyQueue()){
                    BugReport report = priorityQueue.front();
                    std::cout << "BugReport ID: " << std::to_string(report.getId()) << std::endl;
                    std::cout << "Description: " << report.getDescription() << std::endl;
                    std::cout << "Reporter: " << report.getReporter() << std::endl;
                    std::cout << "Status: " << report.getStatus() << std::endl;
                    std::cout << "Priority: " << std::to_string(report.getPriority()) << std::endl;
                    std::cout << "Date: " << report.getDate() << std::endl;
                    completedQueue.enqueue(report);
                    priorityQueue.dequeue();
                } else {
                    std::cout << "There are no bug reports to distribute." << std::endl;
                }
                break;
            case 3:
                std::cout << "Quitting: \n" << std::endl;
                std::cout << "List of Finished Bug Reports: \n" << std::endl;
                while(!completedQueue.isEmptyQueue()){
                    BugReport report = completedQueue.front();
                    std::cout << "BugReport ID: " << std::to_string(report.getId()) << std::endl;
                    std::cout << "Description: " << report.getDescription() << std::endl;
                    std::cout << "Reporter: " << report.getReporter() << std::endl;
                    std::cout << "Status: " << report.getStatus() << std::endl;
                    std::cout << "Priority: " << std::to_string(report.getPriority()) << std::endl;
                    std::cout << "Date: " << report.getDate() << std::endl << std::endl;
                    completedQueue.dequeue();
                }
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

string getDate(){
    std::string date;
    std::regex datePattern("^\\d{4}\\-(0?[1-9]|1[012])\\-(0?[1-9]|[12][0-9]|3[01])$");
    std::smatch match;
    std::cout << "Enter the date of the report (yyyy-mm-dd): ";
    std::cin >> date;
    while(!std::regex_match(date, match, datePattern)){
        std::cout << "The date entered is not valid. Please check that the date entered is in the correct format." << std::endl;
        std::cout << "Enter the date of the report (yyyy-mm-dd): ";
        resetStream();
        std::cin >> date;
    }
    return date;
}

void resetStream(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}