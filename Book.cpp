#include "Book.h"

vector<Book> books;

// constructor
Book::Book(int bookID, string bookName, string authorFirstName, string authorLastName)
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
string Book::getBookID()
{
    return to_string(bookID);
}

// return the name of the book
string Book::getBookName()
{
    return bookName;
}

// return first name of the author
string Book::getAuthorFirstName()
{
    return authorFirstName;
}

// return last name of the author
string Book::getAuthorLastName()
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
        throw invalid_argument("Already borrowed");
    } else {
        this->borrower = &borrower;
        this->dueDate = dueDate;
    }
}