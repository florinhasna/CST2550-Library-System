#include "Book.h"

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

// // book is not borrowed by anyone
// void Book::returnBook()
// {
// }

// // set borrower and dueDate
// void Book::borrowBook(Member& borrower, Date dueDate)
// {
// }