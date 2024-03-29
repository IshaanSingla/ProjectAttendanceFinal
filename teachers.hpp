#include <iostream>
#include <vector>
#include <fstream>
#include "common.hpp"

class Teachers
{
private:
    std::string username;
    std::string password;
    bool loggedIn;
    std::vector<combine<std::string, std::string>> Subject_Codes;
    std::vector<combine<std::string,std::vector<combine<std::string,std::vector<combine<Date,std::string>>>>>> attendance;
    bool check_username(const std::string &);
    bool check_password(const std::string &);
    void loadSubjects();
    void loadAttendance();
public:
    Teachers() : username(""), password(""), loggedIn(false) {}
    ~Teachers();
    void logout();
    bool loguser(const std::string &, const std::string &);
    std::vector<std::string> getSubjects() const;
    bool changepass(const std::string &);
    std::vector<std::string> getSubjects();
    std::vector<std::string> getStudents(const int&);
    std::vector<double> getpercent(const int&);
    std::vector<combine<Date,std::string>> getStudentAttendance(const int&,const int&);
};  

Teachers::~Teachers()
{
    logout();
}

void Teachers::logout()
{
    username.clear();
    password.clear();
    loggedIn = false;
    Subject_Codes.clear();
}
bool Teachers::check_username(const std::string &username)
{
    std::ifstream instream;
    try
    {
        instream.open("teacherlist.lis");
        if (!instream)
            throw std::runtime_error("Error opening file: teacherlist.lis");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    std::string line;
    while (std::getline(instream, line))
    {
        if (line == username)
        {
            std::getline(instream, line);
            this->password = line;
            instream.close();
            return true;
        }
        std::getline(instream, line);
    }
    instream.close();
    return false;
}

bool Teachers::check_password(const std::string &password)
{
    if (this->password == password)
    {
        this->password.clear();
        return true;
    }
    this->password.clear();
    return false;
}

bool Teachers::loguser(const std::string &username, const std::string &password)
{
    if (check_username(username) && check_password(password))
    {
        this->username = username;
        loggedIn = true;

        loadSubjects();
        return true;
    }
    return false;
}

void Teachers::loadSubjects()
{
    if (!loggedIn)
        return;
    std::ifstream instream;
    try
    {
        instream.open(username + ".sub");
        if (!instream)
            throw std::runtime_error("Error opening file: " + username + ".sub");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::string line;
    combine<std::string, std::string> subject_and_code;
    while (std::getline(instream, line))
    {
        subject_and_code.first = line;
        std::getline(instream, line);
        subject_and_code.second = line;
        Subject_Codes.push_back(subject_and_code);
    }
    instream.close();
    loadAttendance();
}

std::vector<std::string> Teachers::getSubjects() const
{
    std::vector<std::string> subjects;
    for (int i = 0; i < Subject_Codes.size(); i++)
    {
        subjects.push_back(Subject_Codes[i].first);
    }
    return subjects;
}

bool Teachers::changepass(const std::string &newpass)
{
    if (!loggedIn)
        return false;
    std::ifstream instream;
    std::ofstream outstream;
    try
    {
        instream.open("teacherlist.lis");
        outstream.open("temp.tmp");
        if (!instream || !outstream)
            throw std::runtime_error("Error opening files: teacherlist.lis or temp.tmp");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    std::string line;
    while (std::getline(instream, line))
    {
        outstream << line << std::endl;
        if (line == username)
        {
            outstream << newpass << std::endl;
            std::getline(instream, line);
            continue;
        }
        std::getline(instream, line);
        outstream << line << std::endl;
    }
    instream.close();
    outstream.close();
    instream.open("temp.tmp");
    outstream.open("teacherlist.lis");
    while (std::getline(instream, line))
    {
        outstream << line << std::endl;
    }
    this->password = newpass;
    return true;
}

void Teachers::loadAttendance()
{
    for(int i = 0; i < Subject_Codes.size();i++)
    {
        std::string code = Subject_Codes[i].second;
        std::ifstream instream;
        instream.open(code+".slis");
        std::string student;
        std::vector<combine<std::string,std::vector<combine<Date,std::string>>>> stud_attendance_record;
        while(std::getline(instream,student))
        {
            combine<std::string,std::vector<combine<Date,std::string>>> student_attendance;
            std::string sub_code = code.substr(0,6);
            std::ifstream student_stream(student+sub_code+".att");
            std::string attendance;
            std::vector<combine<Date,std::string>> temp2;
            while(std::getline(student_stream,attendance))
            {
                Date date(attendance.substr(0,8));
                std::string present_absent = attendance.substr(9,1);
                combine<Date,std::string> temp1;
                temp1.first = date;
                temp1.second = present_absent;
                temp2.push_back(temp1);
            }
            student_attendance.first = student;
            student_attendance.second = temp2;
            stud_attendance_record.push_back(student_attendance);
        }
        combine<std::string,std::vector<combine<std::string,std::vector<combine<Date,std::string>>>>> attendance_record;
        attendance_record.first = Subject_Codes[i].second;
        attendance_record.second = stud_attendance_record;
        attendance.push_back(attendance_record);
    }
}

std::vector<std::string> Teachers::getSubjects()
{
    std::vector<std::string> subjectList;
    for(int i = 0;i<Subject_Codes.size();i++)
    {
        subjectList.push_back(Subject_Codes[i].first);
    }
    return subjectList;
}

std::vector<std::string> Teachers::getStudents(const int& subject_choice)
{
    std::vector<std::string> studentlist;
    for(int i = 0; i<attendance[subject_choice-1].second.size();i++)
    {
        studentlist.push_back(attendance[subject_choice-1].second[i].first);
    }
    return studentlist;
}


std::vector<double> Teachers::getpercent(const int& subject_choice)
{
    std::vector<double> percentlist;
    for(int i = 0; i<attendance[subject_choice-1].second.size();i++)
    {
        double total = attendance[subject_choice-1].second[i].second.size();
        double present = 0;
        for(int j = 0; j<total;j++)
        {
            if(attendance[subject_choice-1].second[i].second[j].second == "p")
            {
                present++;
            }
        }

        double percent = present/total * 100;
        percentlist.push_back(percent);
    }

    return percentlist;
}

std::vector<combine<Date,std::string>> Teachers::getStudentAttendance(const int& subject_choice,const int& student_choice)
{
    std::vector<combine<Date,std::string>> AttendanceList;
    combine<Date,std::string> temp;
    for(int i = 0; i < attendance[subject_choice-1].second[student_choice-1].second.size();i++)
    {
        temp.first = attendance[subject_choice-1].second[student_choice-1].second[i].first;
        temp.second = attendance[subject_choice-1].second[student_choice-1].second[i].second;
        AttendanceList.push_back(temp);
    }
    return AttendanceList;
}