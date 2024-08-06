#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>
#include <ostream>

std::string fileContents;

std::string loopFile(std::string fileName);
void listTasks(std::string currentDir);
bool sortByExtensionCustom(std::string s1, std::string s2);
void sortFromExtension(std::vector<std::string>& files);

int main(){
    std::string student, dailyTasks, taskNameReqest, currentDir = "../tasks/";
    std::cout << "Loading MySchoolTracker v1.1.0\n";
    std::cout << "Loading files...\n\n";
    std::cout << "What student's tasks would you like to look at? (No capitalization)\n";
    std::cin >> student;
    student += "/";
    currentDir += student;
    tasks:
    listTasks(currentDir);
    std::cout << dailyTasks << std::endl;
    std::cout << "What task would you like to look at?\n";
    std::cin >> taskNameReqest;
    system("cls");
    taskNameReqest = currentDir + taskNameReqest;
    loopFile(taskNameReqest);
    std::cout << "The instructions for this task are:\n " << fileContents << "\n";
    system("pause"); //Pauses so that the console doesn't close automatically.
    goto tasks;
}

std::string loopFile(std::string fileName){
    fileContents = "";
    std::ifstream file; file.open(fileName);
    char myChar;
    while (file) {
        file.get(myChar);
        fileContents += myChar;
    }
    file.close();
    return fileContents;
}

void listTasks(std::string currentDir){
    std::stringstream temp;
    std::vector<std::string> files{};
    std::vector<std::string> taskSubjects{".science", ".history", ".math", ".spanish", ".english"};
    const std::filesystem::path tasks{currentDir};

    std::cout << "Current Tasks:\n";
    // directory_iterator can be iterated using a range-for loop
    for (auto const& dir_entry : std::filesystem::directory_iterator{tasks}){
        temp << dir_entry.path().filename() << "\n";
    }
    files.push_back(temp.str());
    sortFromExtension(files);
}

bool sortByExtensionCustom(std::string s1, std::string s2){
    size_t i = s1.find('.');
    size_t j = s2.find('.');
    std::string d = s1.substr(i+1);
    std::string e = s2.substr(j+1);
    if (d == e) {
        return s1 <s2;
    }
    return d < e;
}

void sortFromExtension(std::vector<std::string>& files){
    std::sort(files.begin(), files.end(), sortByExtensionCustom);
    for (auto s : files){
        std::cout << s << "\n";
    }
}