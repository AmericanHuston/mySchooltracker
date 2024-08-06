#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void reoccuringEasyTask();
void createTask(std::string taskName, std::string instructions, std::string taskDates, std::string student);
void createStudentFolders();

int main(){
    again:
    int CT = 0; //ChooseTool
    std::cout << "Which tool would you like to use?\n";
    std::cout << "Schedual a reoccuring task\n Make a new one time task \n Edit an existing task\n";
    std::cout << "Add a new student\n";
    std::cout << "Press a number key to select one of the above.\n\n";
    std::cin >> CT;
    system("cls");
    bool trueOrFalse = ((CT != 1) || (CT != 2) || (CT != 3) || (CT != 4)) ;
    if (trueOrFalse == false){
        std::cout << CT << " is not a valid choice\n";
    }else{
        if (CT == 1){
            reoccuringEasyTask();
        }else if (CT == 4)
        {
            createStudentFolders();
        }
        
    }
    goto again;
}

void reoccuringEasyTask(){
    std::string instructions, taskName, repeats, taskType, dates, student;
    int weeklyRepeats = 0;
    std::vector<std::string> subjects{"science", "history", "math", "spanish", "english"};
    std::cout << "Which student is this task for?\n";
    std::cin >> student;
    std::cout << "What subject do you want to make a task for?\n";
    std::cout << "The avaliable subjects are: ";
    for (long long unsigned int i = 0; i < subjects.size(); i++){
        std::cout << subjects[i] << "\n";
    }
    std::cout << "\n";
    std::cin >> taskType;
    system("cls");
    std::vector<std::string>::iterator it;
    it = std::find(subjects.begin(), subjects.end(), taskType);
    if (it != subjects.end()){
        std::cout << "\n";
        std::cout << "Subject valid\n";
        std::cout << "What is the name of this task?\n";
        std::cin >> taskName;
        taskName += ".";
        taskName += taskType;
        std::cout << "What is the instructions for this task?: ";
        std::getline(std::cin.ignore(), instructions); //Uses getline to include the spaces.
        std::cout << "How many times should this task repeat weekly? (1, 2, 3, ect.)";
        std::cin >> weeklyRepeats;
        createTask(taskName, instructions, dates, student);
    }else{
        std::cout << "Subject not valid\n";
    }
}

void createTask(std::string taskName, std::string instructions, std::string taskDates, std::string student){
    std::string TEMPFILENAME = taskName;
    std::string TEMPDIR = "../tasks/" + student + "/incomplete/";
    std::ofstream currentFile(TEMPFILENAME);
    currentFile << instructions << std::endl;
    currentFile.close();
    std::string TASKDIRFILE = TEMPDIR += TEMPFILENAME;
    std::filesystem::copy(TEMPFILENAME, TASKDIRFILE);
    std::filesystem::remove(TEMPFILENAME);
} //Creates a new task with the proper formatting.

void createStudentFolders(){
    std::string student;
    std::filesystem::current_path("../tasks/");
    std::cout << "What is the name of the student you'd like to add?\n";
    std::cin >> student;
    std::filesystem::create_directory(student);
    student = "../tasks/" + student;
    std::filesystem::current_path(student);
    std::filesystem::create_directory("incomplete/");
    std::filesystem::create_directory("complete/");
    std::cout << "Student added!\n";
    system("pause");
    system("cls");
}