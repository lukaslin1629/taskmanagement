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

bool TaskManager::DeleteTask(Task& task) {
    bool found = false;
    for (auto it = manager_.begin(); it != manager_.end(); ++it) {
        if (it->Description() == task.Description() &&
            it->Location()    == task.Location()    &&
            it->DueDate()     == task.DueDate()     &&
            it->Category()    == task.Category()) {
            manager_.erase(it);
            return true;
        }
    }
    return found;
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