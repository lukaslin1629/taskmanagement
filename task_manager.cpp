#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>


using namespace std;

int main(){

    // task name, pair(type, detail)
    unordered_map<string, vector<pair<string, string>>> tasks;

    cout << "Menu Option: \n" << "Create\n" << "Edit\n" << "Delete\n" << "View\n\n";
    cout << "Task List: " << endl;

    fstream file("taskDataFile.txt", ios::in|ios::out|ios::app);          // It will open the existing file or create one if doesn't exist

    if(!file.is_open()){
        cout << "Faile to open the file\n";
        return -1;
    }

    // To print out the list of tasks
    string line;
    while(getline(file, line)){
        
        // Print out all the task name
        cout << line << endl;

        // Use the line (task name) to open another text file to load the task detail
        string taskName = line + ".txt";
        fstream taskFile(taskName, ios::in|ios::out|ios::app);
    

        string detail;
        while(getline(taskFile, detail)){
            // Separate the task information and type using colon
            size_t colon = detail.find(':');

            if(colon != string::npos){
                string beforeColon = detail.substr(0, colon);
                string afterColon = (colon + 1 < detail.size())?detail.substr(colon + 1) : "";

                // Push all the information into the vector, line = task name
                tasks[line].push_back(make_pair(beforeColon, afterColon));
            }
        }

        taskFile.close();

    }

    file.close();                   // Close the file that contains all the tasks name


    /* 
    **Print function for testing**
    for(const auto& pair: tasks){
        cout << "task name: " << pair.first << endl;
        for(const auto& p: pair.second){
            // due date, task description, location, categories
            cout << "type: " << p.first << ", detal: " << p.second << endl;
        }
    }
    */

    string response; 
    cout << "\n================================\n";
    cout << "What would you like to do today?\n";
    cin >> response;

    if(response == "create"){
        // Call create function

    }   
    else if(response == "edit"){
        // Call edit function

    } 
    else if(response == "delete"){
        // Call delete function

    }
    else if(response == "view"){
        // Call view function or print the map's first again

    }

        
    return 0;
}
