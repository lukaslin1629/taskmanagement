#ifndef TASK_HPP
#define TASK_HPP
#include <iostream>
#include <string>

class Task {
    public:
        // Constructor
        Task(std::string event, std::string location, std::string duedate, std::string category)
            : event_(event), location_(location), duedate_(duedate), category_(category) {}
            
        // Accessor
        std::string Event() const       { return event_;       }
        std::string Location() const    { return location_;    }
        std::string DueDate() const     { return duedate_;     }
        std::string Category() const    { return category_;    }

        // Mutator
        void SetEvent(const std::string& event)             { event_       = event;       }
        void SetLocation(const std::string& location)       { location_    = location;    }
        void SetDueDate(const std::string& duedate)         { duedate_     = duedate;     }
        void SetCategory(const std::string& category)       { category_    = category;    }

    private:
        std::string event_;
        std::string location_;
        std::string category_;
        std::string duedate_;
};

#endif