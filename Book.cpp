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
    this->day = now->tm_mday;

    std::string result;

    int days_in_month;

    // months with 30 days
    if (this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11){
        days_in_month = 30;  
    } else if(this->month == 2) { // february
        // checking if is a leap year or not
        if(this->year % 4 == 0){
            days_in_month = 29;
        } else {
            days_in_month = 28;
        }
    } else { // other months with 31
        days_in_month = 31;
    }

    // if changes month
    if (this->day + 3 > days_in_month){
        this->day = this->day + 3 - days_in_month;
        this->month = this->month + 1;

        // if changes year
        if (this->month + 1 > 12){
            this->year = this->year + 1;
            this->month = 1;
        }
    } else {
        this->day = this->day + 3; 
    }

    result.append(std::to_string(this->day));
    result.append("/");
    result.append(std::to_string(this->month));
    result.append("/");
    result.append(std::to_string(this->year));

    return result;
}

int Date::getDay(){
    return this->day;
}

// constructor
Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
    this->borrower = nullptr;
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
    if(this->borrower != nullptr){
        std::cout << "Book was already issued to someone else...\n\n";
        throw std::invalid_argument("Already borrowed");
    } else {
        this->borrower = &borrower;
        this->dueDate = dueDate;
    }
}

std::vector<Book> books;