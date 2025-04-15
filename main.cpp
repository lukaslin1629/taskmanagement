#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "task_manager.hpp"

int main() {
    int status;
    do {
        status = system("python3 authenticate.py");

        int exit_code = WEXITSTATUS(status);

        if (exit_code == 0) {
            std::cout << "Access granted. Welcome!\n";
            break;
        } else if (exit_code == 1) {
            std::cout << "Authentication failed. Please try again.\n\n";
        } else if (exit_code == 2) {
            std::cout << "User registered.\n\n";
        } else {
            std::cout << "Unknown error.\n";
            return 1;
        }

    } while (true);
    std::fstream myFile;

    // Read file
    myFile.open("myTodoList.txt", std::ios::in);
    std::string line, event, location, duedate, category;
    TaskManager myTask;

    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            if (line.find("Event:")    != std::string::npos)         event       = line.substr(line.find(":") + 1);
            else if (line.find("Location:") != std::string::npos)    location    = line.substr(line.find(":") + 1);
            else if (line.find("Due date:") != std::string::npos)    duedate     = line.substr(line.find(":") + 1);
            else if (line.find("Category:") != std::string::npos) {
                category = line.substr(line.find(":") + 1);
                Task curr_task(event, location, duedate, category);
                myTask.AddTask(curr_task);
            }
        }
        myFile.close();
    }
    std::cout << "What would you like to do today?\n";
    bool user_cont = true;
    std::string response;

    while (user_cont) {
        std::cout << std::endl;
        myTask.DisplayTask();

        // menu
        std::cout << "\nMenu:\n";
        std::cout << "1. Add new task\n";
        std::cout << "2. Delete task\n";
        std::cout << "3. Edit task\n";
        std::cout << "4. View tasks\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> response;
        std::cout << std::endl;

        // add task
        if (response == "1") {
            std::cin.ignore();
            std::cout << "Event:";
            std::getline(std::cin, event);
        
            std::cout << "Location:";
            std::getline(std::cin, location);

            std::cout << "Due date:";
            std::getline(std::cin, duedate);
        
            std::cout << "Categories:";
            std::getline(std::cin, category);
        
            Task new_task = Task(event, location, duedate, category);
            bool add = myTask.AddTask(new_task);
            if (add) std::cout << "Successfully added new task!\n";
        }

        // delete task
        else if (response == "2") {
            std::cin.ignore();
            std::cout << "Event:";
            std::getline(std::cin, event);
            if (myTask.DeleteTask(event)) {
                std::cout << "Successfully deleted task!\n";
            } else {
                std::cout << "Task not found.\n";
            }
        }

        // edit task
        else if (response == "3") {
            std::cin.ignore();
            std::cout << "Event:";
            std::getline(std::cin, event);
            std::cout << "Due date:";
            std::getline(std::cin, duedate);
            if (myTask.EditTask(event, duedate)) {
                std::cout << "Successfully edited task!\n";
            } else {
                std::cout << "Task not found.\n";
            }
        }

        // view tasks
        else if (response == "4") {
            myTask.DisplayTask();
        }
        else if (response == "5") {
            std::cout << "All tasks are saved successfully!\nExit!\n";
            user_cont = false;
            break;
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }

        std::cout << "\nContinue? (Y/N): ";
        std::cin >> response;
        if (response == "N" || response == "n") {
            std::cout << "All tasks are saved successfully!\nExit!\n";
            user_cont = false;
        }
    }

    // export file
    myFile.open("myTodoList.txt", std::ios::out);
    if (myFile.is_open()) {
        for (size_t i = 0; i < myTask.manager_.size(); ++i) {
            myFile << std::to_string(i) << std::endl;
            myFile << "Event:"            << myTask.manager_[i].Event()       << std::endl;
            myFile << "Location:"         << myTask.manager_[i].Location()    << std::endl;
            myFile << "Due date:"         << myTask.manager_[i].DueDate()     << std::endl;
            myFile << "Category:"         << myTask.manager_[i].Category()    << std::endl;
        }
        myFile.close();
    }

    return 0;
}