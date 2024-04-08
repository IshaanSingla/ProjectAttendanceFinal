#include <iostream>
#include <vector>
#include <fstream>
#include "common.hpp"

class Students:public User
{
private:
    
    std::vector<combine<std::string, std::string>> Subject_Codes;
    std::vector<combine<combine<std::string, double>, std::vector<combine<Date, std::string>>>> subject_attendance;
    bool check_username(const std::string &);
    bool check_password(const std::string &);
    void loadSubjects();
    void loadAttendance();

public:
    ~Students();
    void logout();
    bool loguser(const std::string &, const std::string &);
    bool changepass(const std::string &);
    std::vector<std::string> getSubjects() const;
    std::vector<combine<Date, std::string>> getAttendance(const int &) const;
    double getpercent(const int &) const;
    int getTotalClasses(const int&) const;
    int getAttendedClasses(const int&) const;
};

Students::~Students()
{
    logout();
}

void Students::logout()
{
    username.clear();
    password.clear();
    loggedIn = false;
    Subject_Codes.clear();
}
bool Students::check_username(const std::string &username)
{
    std::ifstream instream;
    try
    {
        instream.open("studentlist.lis");
        if (!instream)
            throw std::runtime_error("Error opening file: studentlist.lis");
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

bool Students::check_password(const std::string &password)
{
    if (this->password == password)
    {
        this->password.clear();
        return true;
    }
    this->password.clear();
    return false;
}

bool Students::loguser(const std::string &username, const std::string &password)
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

void Students::loadSubjects()
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

std::vector<std::string> Students::getSubjects() const
{
    std::vector<std::string> subjects;
    for (int i = 0; i < Subject_Codes.size(); i++)
    {
        subjects.push_back(Subject_Codes[i].first);
    }
    return subjects;
}

bool Students::changepass(const std::string &newpass)
{
    if (!loggedIn)
        return false;
    std::ifstream instream;
    std::ofstream outstream;
    try
    {
        instream.open("studentlist.lis");
        outstream.open("temp.tmp");
        if (!instream || !outstream)
            throw std::runtime_error("Error opening files: studentlist.lis or temp.tmp");
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
    outstream.open("studentlist.lis");
    while (std::getline(instream, line))
    {
        outstream << line << std::endl;
    }
    this->password = newpass;
    return true;
}

std::vector<combine<Date, std::string>> Students::getAttendance(const int &number) const
{
    return subject_attendance[number - 1].second;
}

double Students::getpercent(const int &number) const
{
    return subject_attendance[number - 1].first.second;
}

void Students::loadAttendance()
{
    for (int i = 0; i < Subject_Codes.size(); i++)
    {
        std::string code = Subject_Codes[i].second;
        std::ifstream instream;
        try
        {
            instream.open(username + code + ".att");
            if (!instream)
                throw std::runtime_error("Error opening file: " + username + code + ".att");
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        std::string line;
        std::vector<combine<Date, std::string>> attendance_record;
        combine<Date, std::string> attendance;
        std::string p_a;
        int total = 0;
        int count = 0;
        while (std::getline(instream, line))
        {
            Date date(line.substr(0, 8));
            p_a = line[9];
            attendance.first = date;
            attendance.second = p_a;
            attendance_record.push_back(attendance);
            total++;
            p_a == "p" ? count++ : count;
        }

        double percent = ((double)count / (double)total) * 100;

        combine<std::string, double> code_percent;
        code_percent.first = code;
        code_percent.second = percent;
        combine<combine<std::string, double>, std::vector<combine<Date, std::string>>> subjectRecord;
        subjectRecord.first = code_percent;
        subjectRecord.second = attendance_record;
        subject_attendance.push_back(subjectRecord);
        instream.close();
    }
}

int Students::getTotalClasses(const int& subject) const{
    return subject_attendance[subject-1].second.size();
}

int Students::getAttendedClasses(const int& subject) const{
    int attended = 0;
    for(int i = 0; i < subject_attendance[subject-1].second.size(); i++)
    {
        if(subject_attendance[subject-1].second[i].second == "p")
        {
            attended++;
        }
    }
    return attended;
}
