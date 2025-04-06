#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "task_manager.hpp"

Task GetUserInput() {
    std::string description, location, duedate, category;
    std::cin.ignore();
    std::cout << "Description:";
    std::getline(std::cin, description);

    std::cout << "Location:";
    std::getline(std::cin, location);

    std::cout << "Due date:";
    std::getline(std::cin, duedate);

    std::cout << "Category:";
    std::getline(std::cin, category);

    return Task(description, location, duedate, category);
}

int main() { 
    std::fstream myFile;

    // Read file
    myFile.open("myTodoList.txt", std::ios::in);
    std::string line, description, location, duedate, category;
    TaskManager myTask;

    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {
            if (line.find("Task Description:") != std::string::npos) description = line.substr(line.find(":") + 1);
            else if (line.find("Location:") != std::string::npos)    location    = line.substr(line.find(":") + 1);
            else if (line.find("Due date:") != std::string::npos)    duedate     = line.substr(line.find(":") + 1);
            else if (line.find("Category:") != std::string::npos) {
                category = line.substr(line.find(":") + 1);
                Task curr_task(description, location, duedate, category);
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
        std::cout << "3. View tasks\n";
        std::cout << "Enter your choice: ";
        std::cin >> response;
        std::cout << std::endl;

        // add task
        if (response == "1") {
            std::cin.ignore();
            std::cout << "Description:";
            std::getline(std::cin, description);
        
            std::cout << "Location:";
            std::getline(std::cin, location);

            std::cout << "Due date:";
            std::getline(std::cin, duedate);
        
            std::cout << "Categories:";
            std::getline(std::cin, category);
        
            Task new_task = Task(description, location, duedate, category);
            bool add = myTask.AddTask(new_task);
            if (add) std::cout << "Successfully added new task!\n";
        }

        // delete task
        else if (response == "2") {
            Task task_to_delete = GetUserInput();
            if (myTask.DeleteTask(task_to_delete))
                std::cout << "Successfully deleted task!\n";
            else
                std::cout << "Task not found.\n";
        }

        // view tasks
        else if (response == "3") {
            myTask.DisplayTask();
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }

        std::cout << "Continue? (Y/N): ";
        std::cin >> response;
        if (response == "N" || response == "n") user_cont = false;
    }

    // export file
    myFile.open("myTodoList.txt", std::ios::out);
    if (myFile.is_open()) {
        for (size_t i = 0; i < myTask.manager_.size(); ++i) {
            myFile << std::to_string(i) << std::endl;
            myFile << "Task Description:" << myTask.manager_[i].Description() << std::endl;
            myFile << "Location:"         << myTask.manager_[i].Location()    << std::endl;
            myFile << "Due date:"         << myTask.manager_[i].DueDate()     << std::endl;
            myFile << "Category:"         << myTask.manager_[i].Category()    << std::endl;
        }
        myFile.close();
    }

    return 0;
}