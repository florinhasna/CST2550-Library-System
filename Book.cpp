#include "Book.h"

time_t t = std::time(0);
tm* now = std::localtime(&t);

std::string Date::getCurrentDay(){
    this->year = now->tm_year + 1900;
    this->month = now->tm_mon + 1;
    this->day = now->tm_mday;

    std::string result;

    result.append(std::to_string(this->day));
    result.append("/");
    result.append(std::to_string(this->month));
    result.append("/");
    result.append(std::to_string(this->year));

    return result;
}

std::string Date::getDueDate(){
    this->year = now->tm_year + 1900;
    this->month = now->tm_mon + 1;
    this->day = now->tm_mday + 3;

    std::string result;

    result.append(std::to_string(this->day));
    result.append("/");
    result.append(std::to_string(this->month));
    result.append("/");
    result.append(std::to_string(this->year));

    return result;
}

// constructor
Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
}

// destructor
Book::~Book() 
{ 
}

// returns book's unique ID
std::string Book::getBookID()
{
    return std::to_string(bookID);
}

// return the name of the book
std::string Book::getBookName()
{
    return bookName;
}

// return first name of the author
std::string Book::getAuthorFirstName()
{
    return authorFirstName;
}

// return last name of the author
std::string Book::getAuthorLastName()
{
    return authorLastName;
}

Date Book::getDueDate()
{
    return dueDate;
}

void Book::setDueDate(Date dueDate)
{
    this->dueDate = dueDate;
}

// book is not borrowed by anyone
void Book::returnBook()
{
    this->borrower = nullptr;
}

// set borrower and dueDate
void Book::borrowBook(Member& borrower, Date dueDate)
{
    this->borrower = &borrower;
    this->dueDate = dueDate;
}

std::vector<Book> books;