#include <iostream>
#include <iomanip>
#include <vector>
#include "common.hpp"



//Declarations
std::string printCentre(int, const std::string&);
int printHorizontalLine(int, char, char);
void printRow(int&, std::string, bool);
void printRow(int&, std::string, std::string, bool);
void printRow(const int&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, bool);
void printRow(std::string, std::string, std::string, std::string, std::string, bool, bool);



//Definitions
std::string printCentre(int width, const std::string& str)
{
    int leading_spaces = (width - str.length())/2;
    if (leading_spaces > 0)
        return (std::string(leading_spaces, ' ') + str);
    else
        return "";
}

int printHorizontalLine(int width, char borderChar, char intersectionChar)
{
    std::cout << intersectionChar;
    for (int i = 0; i < width - 2; i++)
        std::cout << borderChar;
    std::cout << intersectionChar << std::endl;
    return width;
}

void printRow(int& width, std::string str, bool flag = false)
{
    if (flag==true)
        std::cout << "|" << "\033[1;33m" << std::setw(width-2) << std::left << printCentre(width-2, str) << "\033[0m" << "|" << std::endl;
    else
        std::cout << "|" << std::setw(width-2) << std::left << printCentre(width-2, str) << "|" << std::endl;
}

void printRow(int& width, std::string col1, std::string col2, bool flag = false)
{
    if (flag==true)
        std::cout << "|" << "\033[1;33m" << std::setw(width-2) << std::left << printCentre(width-2, col1) << "\033[0m"
                  << "|" << "\033[1;33m" << std::setw(width-2) << std::left << printCentre(width-2, col2) << "\033[0m" << "|"
                  <<std::endl;
    else
        std::cout << "|" << std::setw((width-2)/2) << std::left << printCentre((width-2)/2, col1)
                  << "|" << std::setw((width-2)/2) << std::left << printCentre((width-2)/2, col2) << "|"
                  <<std::endl;
}

void printRow(const int& width, const std::string& col1, const std::string& col2, const std::string& col3, const std::string& col4, const std::string& col5, bool flag = false, int flag1=0)
{
    if (flag==true)
    {
        std::cout << "|" << "\033[1;33m" << std::setw((width-6)/5) << std::left << printCentre((width-6)/5, col1) << "\033[0m" << "|"
                  << "\033[1;33m" << std::setw((width-6)/5) << printCentre((width-6)/5, col2) << "\033[0m" << "|"
                  << "\033[1;33m" << std::setw((width-6)/5) << printCentre((width-6)/5, col3) << "\033[0m" << "|"
                  << "\033[1;33m" << std::setw((width-6)/5) << printCentre((width-6)/5, col4) << "\033[0m" << "|"
                  << "\033[1;33m" << std::setw((width-6)/5) << printCentre((width-6)/5, col5) << "\033[0m" << "|"
                  << std::endl;
    }
    else if (flag==true)
    {
        std::cout << "|" << std::setw((width-6)/5) << std::left << printCentre((width-6)/5, col1) << "|"
                  << std::setw((width-6)/5) << printCentre((width-6)/5, col2) << "|"
                  << std::setw((width-6)/5) << printCentre((width-6)/5, col3) << "|"
                  << std::setw((width-6)/5) << printCentre((width-6)/5, col4) << "|"
                  << std::setw((width-6)/5) << printCentre((width-6)/5, col5) << "|"
                  << std::endl;
    }
}

void printRow(std::string col1, std::string col2, std::string col3, std::string col4, std::string col5, bool flag = false, bool flag1 = false)
{   
    if (flag==true && flag1==false) 
    {
        std::cout << "|" << "\033[1;33m" << std::setw(16) << std::left << printCentre(16, col1) << "\033[0m" << "|"
                  << "\033[1;33m" << std::setw(52) << printCentre(52, col2) << "\033[0m" << "|"
                  << "\033[1;33m" << std::setw(16) << printCentre(16, col3) << "\033[0m" << "|"
                  << "\033[1;33m" << std::setw(19) << printCentre(19, col4) << "\033[0m" << "|"
                  << "\033[1;33m" << std::setw(16) << printCentre(16, col5) << "\033[0m" << "|"
                  << std::endl;
    }
    else if (flag==false && flag1==false)
    {
        std::cout << "|" << "\033[0;31m" << std::setw(16) << std::left << printCentre(16, col1) << "\033[0m" << "|"
                  << "\033[0;31m" << std::setw(52) << printCentre(52, col2) << "\033[0m" << "|"
                  << "\033[0;31m" << std::setw(16) << printCentre(16, col3) << "\033[0m" << "|"
                  << "\033[0;31m" << std::setw(19) << printCentre(19, col4) << "\033[0m" << "|"
                  << "\033[0;31m" << std::setw(16) << printCentre(16, col5) << "\033[0m" << "|"
                  << std::endl;
    }
    else if (flag==false && flag1==true)
    {
        std::cout << "|" << "\033[0;32m" << std::setw(16) << std::left << printCentre(16, col1) << "\033[0m" << "|"
                  << "\033[0;32m" << std::setw(52) << printCentre(52, col2) << "\033[0m" << "|"
                  << "\033[0;32m" << std::setw(16) << printCentre(16, col3) << "\033[0m" << "|"
                  << "\033[0;32m" << std::setw(19) << printCentre(19, col4) << "\033[0m" << "|"
                  << "\033[0;32m" << std::setw(16) << printCentre(16, col5) << "\033[0m" << "|"
                  << std::endl;
    }
}