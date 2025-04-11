#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 

#include "task_manager.hpp"

bool TaskManager::AddTask(Task& new_task) {
    bool found = true;
    for (auto& task : manager_) {
        if (task.Description() == new_task.Description() &&
            task.Location()    == new_task.Location()    &&
            task.DueDate()     == new_task.DueDate()     &&
            task.Category()    == new_task.Category()) {
            return false;
        }
    }
    manager_.push_back(new_task);
    return found;
}

bool TaskManager::DeleteTask(std::string description) {
    bool found = false;
    for (auto it = manager_.begin(); it != manager_.end(); ++it) {
        if (it->Description() == description) {
            manager_.erase(it);
            return true;
        }
    }
    return found;
}

bool TaskManager::EditTask(std::string description) {
    for (auto& task : manager_) {
        if (task.Description() == description) {
            int choice;
            std::string changed = "";
            
            do {
                std::cout << "\nEditing task: " << task.Description() << std::endl;
                std::cout << "Select a field to edit:\n";
                std::cout << "1. Description\n";
                std::cout << "2. Location\n";
                std::cout << "3. Due Date\n";
                std::cout << "4. Category\n";
                std::cout << "5. Done editing\n";
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                std::cin.ignore();

                switch (choice) {
                    case 1:
                        std::cout << "Enter new description: ";
                        std::getline(std::cin, changed);
                        task.SetDescription(changed);
                        break;
                    case 2:
                        std::cout << "Enter new location: ";
                        std::getline(std::cin, changed);
                        task.SetLocation(changed);
                        break;
                    case 3:
                        std::cout << "Enter new due date: ";
                        std::getline(std::cin, changed);
                        task.SetDueDate(changed);
                        break;
                    case 4:
                        std::cout << "Enter new category: ";
                        std::getline(std::cin, changed);
                        task.SetCategory(changed);
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }
            } while (choice != 5);
            return true;
        }
    }
    return false;
}

void TaskManager::DisplayTask() const {
    std::cout << std::left;
    std::cout << std::setw(5) << "ID"
              << std::setw(25) << "Description"
              << std::setw(20) << "Location"
              << std::setw(20) << "Due date"
              << std::setw(15) << "Category" << std::endl;
    std::cout << std::string(78, '-') << std::endl;
    for (int i = 0; i < manager_.size(); ++i) {
        std::cout << std::setw(5) << i
                  << std::setw(25) << manager_[i].Description()
                  << std::setw(20) << manager_[i].Location()
                  << std::setw(20) << manager_[i].DueDate()
                  << std::setw(15) << manager_[i].Category()
                  << std::endl;
    }
}