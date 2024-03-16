#include <iostream>
#include <vector>
#include <fstream>
#include "common.hpp"

class Students
{
private:
    std::string username;
    std::string password;
    std::vector<std::string> Subject_Codes[2];
    bool check_username(const std::string&);
    bool check_password(const std::string&);

public:
    Students(): username(""),password("") {}
    bool loguser(const std::string&,const std::string&);
    std::vector<std::string> getSubjects(const std::string&);
    bool changepass(const std::string&,const std::string&);
    std::vector<combine<Date,std::string>> getAttendance(const int&);
    double getpercent(const int&);
};

bool Students::check_username(const std::string& username)
{
    std::ifstream instream;
    try
    {
        instream.open("studentlist.lis");
        if (!instream)
            throw std::runtime_error("Error opening file: studentlist.lis");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    std::string line;
    while(std::getline(instream,line))
    {
        if(line == username)
        {
            std::getline(instream,line);
            this->password = line;
            instream.close();
            return true;
        }
        std::getline(instream,line);
    }
    instream.close();
    return false;
}

bool Students::check_password(const std::string& password)
{
    if(this->password == password)
    {
        return true;
    }
    this->password = "";
    return false;
}

bool Students::loguser(const std::string& username, const std::string& password)
{
    if(check_username(username) && check_password(password))
    {
        this->username = username;
        return true;
    }
    return false;
}

std::vector<std::string> Students::getSubjects(const std::string& password)
{
    if((this->password == "")||(this->password != password)) return Subject_Codes[0];
    std::ifstream instream;
    try
    {
        instream.open(username + ".sub");
        if (!instream)
            throw std::runtime_error("Error opening file: " + username + ".sub");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return Subject_Codes[0];
    }

    std::string line;
    while(std::getline(instream,line))
    {
        Subject_Codes[0].push_back(line);
        std::getline(instream,line);
        Subject_Codes[1].push_back(line);
    }
    instream.close();
    return Subject_Codes[0];
}

bool Students::changepass(const std::string& oldpass,const std::string& newpass)
{
    if((this->password == "")||(this->password != oldpass)) return false;
    std::ifstream instream;
    std::ofstream outstream;
    try
    {
        instream.open("studentlist.lis");
        outstream.open("temp.tmp");
        if (!instream || !outstream)
            throw std::runtime_error("Error opening files: studentlist.lis or temp.tmp");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    std::string line;
    while(std::getline(instream,line))
    {
        outstream << line << std::endl;
        if(line == username)
        {
            outstream << newpass << std::endl;
            std::getline(instream,line);
            continue;
        }
        std::getline(instream,line);
        outstream << line << std::endl;
    }
    instream.close();
    outstream.close();
    instream.open("temp.tmp");
    outstream.open("studentlist.lis");
    while(std::getline(instream,line))
    {
        outstream << line << std::endl;
    }
    this->password = newpass;
    return true;
}

std::vector<combine<Date,std::string>> Students::getAttendance(const int& number)
{
    std::string code = Subject_Codes[1][number-1];
    std::ifstream instream;
    try
    {
        instream.open(username + code + ".att");
        if (!instream)
            throw std::runtime_error("Error opening file: " + username + code + ".att");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return std::vector<combine<Date,std::string>>(); // Return an empty vector
    }

    std::string line;
    std::vector<combine<Date,std::string>> attendance_record;
    combine<Date,std::string> attendance;
    Date date;
    std::string p_a;
    while(std::getline(instream,line))
    {
        date.day = ((int)line[0]-48)*10+((int)line[1]-48);
        date.month = ((int)line[3]-48)*10+((int)line[4]-48);
        date.year= ((int)line[6]-48)*10+((int)line[7]-48);
        p_a = line[9];
        attendance.first = date;
        attendance.second = p_a;
        attendance_record.push_back(attendance);
    }
    instream.close();
    return attendance_record;
}

double Students::getpercent(const int& number)
{
    std::vector<combine<Date,std::string>> attendance = getAttendance(number);
    double total = attendance.size();
    double count = 0;
    for(int i = 0;i<attendance.size();i++)
    {
        if(attendance[i].second == "p")
        {
            count++;
        }
    }
    return (count/total)*100;
}
 