#ifndef DATE_HEADER
#define DATE_HEADER
struct Date
{
    unsigned day; 
    unsigned month;
    unsigned year;
};
template <typename T,typename U>
struct combine
{
    T first;
    U second;
};

class user
{
protected:
    std::string username;
    std::string password;
};
#endif
