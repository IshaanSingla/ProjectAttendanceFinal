#include <iostream>
#include <string>
#include "frontend.hpp"
#include "students.hpp"
#include "teachers.hpp"
#include <conio.h>

void choose_designation(int, char, char);
bool log_in_student(int, char, char, Students &);
bool log_in_teacher(int, char, char, Teachers &);
void subject_list(int, char, char, std::vector<std::string> &, Students &);
void menu(int, char, char);
void menu_teacher(int, char, char);
void show_subjects(int,char,char);
Students s1;
Teachers t1;
int main()
{
    system("cls");
    choose_designation(51, '-', '+');

    return 0;
}

void choose_designation(int TableWidth, char borderChar, char intersectionChar)
{
    int choice;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Choose Designation", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "1", "Teacher", false);
    printRow(TableWidth, "2", "Student", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    system("cls");
    switch (choice)
    {
    case 1:
    {
        bool is_logged_in;
        is_logged_in = log_in_teacher(51, '-', '+', t1);
        if (is_logged_in)
        {
            menu_teacher(61, '-', '+');
        }
    }
    break;
    case 2:
    {
        bool is_logged_in;
        is_logged_in = log_in_student(51, '-', '+', s1);
        if (is_logged_in == true)
        {
            std::vector<std::string> subjects = s1.getSubjects();
            subject_list(125, '-', '+', subjects, s1);
            menu(61, '-', '+');
        }
    }
    break;

    default:
        system("cls");
        std::cout << "INVALID RESPONSE!" << std::endl
                  << "Please try again." << '\n';
        std::cin.clear();
        std::cin.ignore();
        choose_designation(51, '-', '+');
        break;
    }
}

bool log_in_student(int TableWidth, char borderChar, char intersectionChar, Students &obj)
{
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Welcome to Student Login Page", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::string username, password;
    printRow(TableWidth, "Enter Username:", false);
    std::cout << printCentre(TableWidth / 2, "            ");
    std::cin >> username;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Enter Password:", false);
    std::cout << printCentre(TableWidth / 2, "            ");
    std::cin >> password;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);

    if (obj.loguser(username, password) == true)
    {
        std::cout << "\033[0;32m" << std::endl;
        printRow(TableWidth, "Login Successful", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        system("cls");
        return true;
    }
    else
    {
        std::cin.clear();
        std::cin.ignore();
        system("cls");
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "Login Unsuccessful", false);
        printRow(TableWidth, "Please try again", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        bool is_logged_in;

        is_logged_in = log_in_student(51, '-', '+', s1);
        if (is_logged_in == true)
        {
            std::vector<std::string> subjects = s1.getSubjects();
            subject_list(125, '-', '+', subjects, s1);
            menu(61, '-', '+');
        }
        return false;
    }
}

void subject_list(int TableWidth, char borderChar, char intersectionChar, std::vector<std::string> &subjects, Students &obj)
{
    double percentage;
    std::string remarks;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow("SERIAL NO.", "SUBJECT", "ATTENDANCE", "ATTENDANCE%", "COMMENTS", true, false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);

    for (int i = 0; i < subjects.size(); i++)
    {
        percentage = obj.getpercent(i + 1);
        bool flag1;
        if (percentage < 50)
        {
            remarks = "DETAINED";
            flag1 = false;
        }
        else
        {
            remarks = "CLEAR";
            flag1 = true;
        }
        printRow(std::to_string(i + 1), subjects[i], std::to_string(s1.getAttendedClasses(i + 1)) + "/" + std::to_string(s1.getTotalClasses(i + 1)), std::to_string(percentage), remarks, false, flag1);
    }
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
}

void menu(int TableWidth, char borderChar, char intersectionChar)
{
    int choice;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "MENU", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "1.", "Change Password", false);
    printRow(TableWidth, "2.", "Check Attendance Record", false);
    printRow(TableWidth, "3.", "Exit", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::cout << "Enter the choice: ";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
    {
        std::string new_pass;
        std::cout << "\nEnter new password: ";
        std::cin >> new_pass;
        if (s1.changepass(new_pass))
        {
            system("cls");
            std::cout << "\033[0;32m" << std::endl;
            printRow(TableWidth, "Password changed successfully!", false);
            std::vector<std::string> subjects = s1.getSubjects();
            subject_list(125, '-', '+', subjects, s1);
            menu(61, '-', '+');
        }

        else
        {
            std::cout << "Something went wrong!" << std::endl
                      << std::endl;
            menu(61, '-', '+');
        }
    }
    break;

    case 2:
    {
        std::vector<std::string> subjects = s1.getSubjects();
        int choice = 0;
        do
        {
            std::cout << "Choose the subject: ";
            std::cin >> choice;
            if (!((choice <= subjects.size()) || (choice < 0)))
                std::cout << "Invalid choice" << std::endl;
        } while (!((choice <= subjects.size()) || (choice < 0)));
        system("cls");
        system("cls");
        std::vector<combine<Date, std::string>> attendance = s1.getAttendance(choice);
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        for (int i = 0; i < attendance.size(); i++)
        {
            std::string p_a = (attendance[i].second == "p") ? "Present" : "Absent";
            int day = attendance[i].first.getDay();
            int month = attendance[i].first.getMonth();
            int year = attendance[i].first.getYear();
            std::string stringDay = std::to_string(day);
            std::string stringMonth = std::to_string(month);
            std::string stringYear = std::to_string(year);
            std::string date = stringDay + "-" + stringMonth + "-" + stringYear;
            printRow(TableWidth, date, p_a, false);
        }
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        getch();
        system("cls");
        system("cls");
        subject_list(125, '-', '+', subjects, s1);
        menu(61, '-', '+');
    }
    break;

    case 3:
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "--------------------------Exit--------------------------", false);
        std::cout << "\033[0m" << std::endl;
        exit(EXIT_SUCCESS);

    default:
        std::cin.clear();
        std::cin.ignore();
        system("cls");
        std::cout << "INVALID RESPONSE!" << std::endl
                  << "Please try again." << std::endl;
        std::vector<std::string> subjects = s1.getSubjects();
        subject_list(125, '-', '+', subjects, s1);
        menu(61, '-', '+');
    }
}

void menu_teacher(int TableWidth, char borderChar, char intersectionChar)
{
    int choice;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "MENU", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "1.", "Mark Attendance", false);
    printRow(TableWidth, "2.", "Check Attendance Record", false);
    printRow(TableWidth, "3.", "Change Password", false);
    printRow(TableWidth, "4.", "Exit", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::cout << "Enter the choice: ";
    std::cin >> choice;
    switch (choice)
    {
    case 2:
    {
        show_subjects(TableWidth,borderChar,intersectionChar);
    }
    break;
    case 3:
    {
        std::string new_pass;
        std::cout << "\nEnter new password: ";
        std::cin >> new_pass;
        if (t1.changepass(new_pass))
        {
            system("cls");
            std::cout << "\033[0;32m" << std::endl;
            printRow(TableWidth, "Password changed successfully!", false);
            menu_teacher(61, '-', '+');
        }

        else
        {
            std::cout << "Something went wrong!" << std::endl
                      << std::endl;
            menu_teacher(61, '-', '+');
        }
    }
    break;
    case 4:
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "--------------------------Exit--------------------------", false);
        std::cout << "\033[0m" << std::endl;
        exit(EXIT_SUCCESS);
        break;
    default:
        std::cin.clear();
        std::cin.ignore();
        system("cls");
        std::cout << "INVALID RESPONSE!" << std::endl
                  << "Please try again." << std::endl;
        menu_teacher(61, '-', '+');
    }
    }


bool log_in_teacher(int TableWidth, char borderChar, char intersectionChar, Teachers &obj)
{
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Welcome to Student Login Page", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::string username, password;
    printRow(TableWidth, "Enter Username:", false);
    std::cout << printCentre(TableWidth / 2, "            ");
    std::cin >> username;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Enter Password:", false);
    std::cout << printCentre(TableWidth / 2, "            ");
    std::cin >> password;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);

    if (obj.loguser(username, password) == true)
    {
        std::cout << "\033[0;32m" << std::endl;
        printRow(TableWidth, "Login Successful", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        system("cls");
        return true;
    }
    else
    {
        std::cin.clear();
        std::cin.ignore();
        system("cls");
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "Login Unsuccessful", false);
        printRow(TableWidth, "Please try again", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        bool is_logged_in;

        is_logged_in = log_in_teacher(51, '-', '+', t1);
        if (is_logged_in == true)
        {

            menu_teacher(61, '-', '+');
        }
        return false;
    }
}

void show_subjects(int TableWidth, char borderChar, char intersectionChar)
{
    system("cls");
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    int tablewidth = TableWidth/2 + 1;
    printRow(tablewidth,"SERIAL NO.", "SUBJECTS",true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::vector<std::string> subjects = t1.getSubjects();
    for(int i = 0; i<subjects.size();i++)
    {
        printRow(TableWidth,std::to_string(i+1), subjects[i],false);
    }
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
}