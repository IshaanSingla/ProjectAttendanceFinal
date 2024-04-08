#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include "common.hpp"
class Teacher{
    private:
    std::string username;
    std::string password;
    std::vector<std::string> Subject_Codes[2];
    bool check_username(std::string);
    bool check_password(std::string);
public:
    bool loguser(std::string,std::string);
    std::vector<std::string> getSubjects(std::string);
    bool changepass(std::string,std::string);
    std::vector<combine<Date,std::string>> getAttendance(int number);
    double getpercent(int number);
    std::map<std::string, double> std_attd_list(int subject);

};


bool Teacher::check_username(std::string username)
{
    std::ifstream instream("teacherlist.lis");
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

bool Teacher::check_password(std::string password)
{
    if(this->password == password)
    {
        return true;
    }
    this->password = "";
    return false;
}

bool Teacher::loguser(std::string username, std::string password)
{
    if(check_username(username) && check_password(password))
    {
        this->username = username;
        return true;
    }
    return false;
}



std::vector<std::string> Teacher::getSubjects(std::string password)
{
    if((this->password == "")||(this->password != password)) return Subject_Codes[0];
    std::ifstream instream(username + ".sub");
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

bool Teacher::changepass(std::string oldpass,std::string newpass)
{
    if((this->password == "")||(this->password != oldpass)) return false;
    std::ifstream instream("teacherlist.lis");
    std::string line;
    std::ofstream outstream("temp.tmp");
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
    outstream.open("teacherlist.lis");
    while(std::getline(instream,line))
    {
        outstream << line << std::endl;
    }
    this->password = newpass;                                                                        
    return true;
}



