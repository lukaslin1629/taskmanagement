#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP
#include <iostream>
#include <string>
#include <vector>

#include "task.hpp"

class TaskManager {
    public:
        TaskManager() {}
        std::vector<Task> manager_;
        bool AddTask(Task& new_task);
        bool DeleteTask(std::string event, std::string duedate);
        bool EditTask(std::string event, std::string duedate);
        void DisplayTask() const;
};

#endif