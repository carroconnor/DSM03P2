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
* Date last updated: 6/21/20124
* Purpose: Implement a priority queue using a linked list.
*/

void printMenu();
void resetStream();
int inputInt(std::string prompt, int min, int max);
std::string getDate();

int main(){
    int id = 1;
    // Regex to validat date format
    std::regex datePattern("^\\d{4}\\-(0?[1-9]|1[012])\\-(0?[1-9]|[12][0-9]|3[01])$");
    priorityQueueType<BugReport> priorityQueue; //hold the bug reports by priority
    linkedQueueType<BugReport> completedQueue; //hold the bug reports that have been completed
    priorityQueue.initializeQueue();
    completedQueue.initializeQueue();

    while(true){
        printMenu();
        int choice = inputInt("", 1, 3); //Enter choice: 

        std::smatch match;
        std::string date;
        std::string description;
        std::string reporter;
        int priority;

        switch(choice){
            case 1:
                date = getDate();
                //if match regex build bug report
                if(std::regex_match(date, match, datePattern)){
                    std::cin.ignore(); 
                    // std::cout << "Enter the name of the reporter: ";
                    std::getline(std::cin, reporter);
                    //std::cout << "Describe the bug: ";
                    std::getline(std::cin, description);
                    priority = inputInt("", 1, 10); //What is the priority 1 - 10 (1 is low, 10 is high): 
                    BugReport report(id++, description, reporter, "new", priority, date);
                    priorityQueue.enqueue(report);
                } else {
                    //std::cout << "The date entered is not valid. Please check that the date entered is in the correct format." << std::endl;
                }
                break;
            case 2:
                //if there are bug reports in the queue add to completed list and set status to Finished
                if(!priorityQueue.isEmptyQueue()){
                    BugReport report = priorityQueue.front();
                    // std::cout << "BugReport ID: " << std::to_string(report.getId()) << std::endl;
                    // std::cout << "Description: " << report.getDescription() << std::endl;
                    // std::cout << "Reporter: " << report.getReporter() << std::endl;
                    // std::cout << "Status: " << report.getStatus() << std::endl;
                    // std::cout << "Priority: " << std::to_string(report.getPriority()) << std::endl;
                    // std::cout << "Date: " << report.getDate() << std::endl;
                    report.setStatus("Finished");
                    completedQueue.enqueue(report);
                    priorityQueue.dequeue();
                } else {
                    std::cout << "There are no bug reports to distribute." << std::endl;
                }
                break;
            case 3:
                //display list of all completed bug reports
                // std::cout << "Quitting: \n" << std::endl;
                // std::cout << "List of Finished Bug Reports: \n" << std::endl;
                while(!completedQueue.isEmptyQueue()){
                    BugReport report = completedQueue.front();
                    std::cout << "BugReport ID: " << std::to_string(report.getId()) << std::endl;
                    std::cout << "Description: " << report.getDescription() << std::endl;
                    std::cout << "Reporter: " << report.getReporter() << std::endl;
                    std::cout << "Status: " << report.getStatus() << std::endl;
                    std::cout << "Priority: " << std::to_string(report.getPriority()) << std::endl;
                    std::cout << "Date: " << report.getDate() << std::endl;
                    std::cout << std::endl;
                    completedQueue.dequeue();
                }
                std::cout << std::endl;
                std::cout << "List of Unfinished Bug Reports: " << std::endl;
                std::cout << std::endl;
                while(!priorityQueue.isEmptyQueue()){
                    BugReport report = priorityQueue.front();
                    std::cout << "BugReport ID: " << std::to_string(report.getId()) << std::endl;
                    std::cout << "Description: " << report.getDescription() << std::endl;
                    std::cout << "Reporter: " << report.getReporter() << std::endl;
                    std::cout << "Status: " << report.getStatus() << std::endl;
                    std::cout << "Priority: " << std::to_string(report.getPriority()) << std::endl;
                    std::cout << "Date: " << report.getDate() << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    priorityQueue.dequeue();
                }
                return 0;
        }
    }
    return 0;
}

void printMenu(){
    // std::stringstream ss;
    // ss << "1. Enter bug report\n";
    // ss << "2. Distribute bug report\n";
    // ss << "3. Quit\n";
    // std::cout << ss.str();
}

// get integer input from user
int inputInt(std::string prompt, int min, int max){
    int result;

    if(prompt.length() > 0){
        std::cout << prompt << std::endl; 
    }
    std::cin >> result; 

    while(result < min || result > max){
        //std::cout << "That is an invalid choice.";
        resetStream();
        std::cin >> result;
    }
    
    return result;
}

//get date input from user
std::string getDate(){
    std::string date;
    std::regex datePattern("^\\d{4}\\-(0?[1-9]|1[012])\\-(0?[1-9]|[12][0-9]|3[01])$");
    std::smatch match;
    //std::cout << "Enter the date of the report (yyyy-mm-dd): ";
    std::cin >> date;
    while(!std::regex_match(date, match, datePattern)){
        // std::cout << "The date entered is not valid. Please check that the date entered is in the correct format." << std::endl;
        // std::cout << "Enter the date of the report (yyyy-mm-dd): ";
        resetStream();
        std::cin >> date;
    }
    return date;
}

void resetStream(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}