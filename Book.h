#ifndef _BOOK_H_
#define _BOOK_H_
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <regex>

class Member;

struct Date{
    int year;
    int month;
    int day;

    std::string getCurrentDay();
    std::string getDueDate();
    int getDay();
};

class Book
{
    private:
        int bookID;
        std::string bookName;
        std::string authorFirstName;
        std::string authorLastName;
        std::string bookType;
        Date dueDate;
        Member* borrower;
    public:
        Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName);
        ~Book();
        std::string getBookID();
        std::string getBookName();
        std::string getAuthorFirstName();
        std::string getAuthorLastName();
        Date getDueDate();
        void setDueDate(Date dueDate);
        void returnBook();
        void borrowBook(Member& borrower, Date dueDate);
};

extern std::vector<Book> books;

#endif