#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void reoccuringEasyTask();
void createTask(std::string taskName, std::string instructions, std::string taskDates, std::string student);
void createStudentFolders();
void oneTimeTask();
void editTask();
void listTasks(std::string currentDir);

int main(){
    again:
    int CT = 0; //ChooseTool
    std::cout << "Which tool would you like to use?\n";
    std::cout << "1. Schedual a reoccuring task\n 2. Make a new one time task \n 3. Edit an existing task\n";
    std::cout << "4. Add a new student\n 5. Tree the tree\n 6. EXIT \n";
    std::cout << "Press a number key to select one of the above.\n";
    std::cin >> CT;
    system("cls");
    bool trueOrFalse = ((CT != 1) || (CT != 2) || (CT != 3) || (CT != 4) || (CT !=5) || (CT != 6)) ;
    if (trueOrFalse == false){
        std::cout << CT << " is not a valid choice\n";
    }else if (CT == 1)
    {
        reoccuringEasyTask();
    }else if (CT == 2)
    {
        oneTimeTask();
    }else if (CT == 3)
    {
        editTask();
    }else if (CT == 4)
    {
        createStudentFolders();
    }else if (CT == 5)
    {
        std::system("tree ../tasks/");
        system("pause");
        system("cls");
    }else if (CT == 6)
    {
        exit(0);
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
    currentFile << instructions << "\n" << taskDates << std::endl;
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

void oneTimeTask(){
    std::string taskType, taskName, instructions, taskDates, student;
    std::vector<std::string> subjects{"science", "history", "math", "spanish", "english"};
    std::cout << "What do you want to name this task?\n";
    std::getline(std::cin.ignore(), taskName);
    std::cout << "Which student is this task for?\n";
    std::getline(std::cin.ignore(), student);
    std::cout << "What subject do you want to make a task for?\n";
    std::cout << "The avaliable subjects are:\n";
    for (long long unsigned int i = 0; i < subjects.size(); i++){
        std::cout << subjects[i] << "\n";
    }
    std::cout << "\n";
    std::getline(std::cin.ignore(), taskType);
    std::cout << "What are the instructions for this task?\n";
    std::getline(std::cin.ignore(), instructions);
    std::cout << "When is this due?\n";
    std::getline(std::cin.ignore(), taskDates);
    taskType = "." + taskType;
    taskName = taskName + taskType;
    createTask(taskName, instructions, taskDates, student);
}

void editTask(){
    std::string student, taskName, fileContents, fileToOpen, YON;
    std::cout << "Which student do you want to edit a task for?";
    std::cin >> student;
    student = "../tasks/" + student;
    listTasks(student);
    std::cout << "What is the name of the task you'd like to edit?\n";
    std::getline(std::cin.ignore(), taskName);
    std::ifstream file; file.open(taskName);
    char myChar;
    while (file) {
        file.get(myChar);
        fileContents += myChar;
    }
    std::cout << fileContents;
    std::cout << "Open task file? (y/n)\n";
    std::cin >> YON;
    if (YON == "y"){
        fileToOpen = "notepad \"" + taskName + "\"";
        system(fileToOpen.c_str());
        system("pause");
    }
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
}