#include "Book.h"

vector<Book> books;

// constructor
Book::Book(int bookID, string bookName, string authorFirstName, string authorLastName)
{
    // loading relevant data
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

// return Date struct member "dueDate"
Date Book::getDueDate()
{
    return dueDate;
}

// set Date structe member "dueDate", which is current day + 3
void Book::setDueDate(Date dueDate)
{
    this->dueDate = dueDate;
}

// set the book as not borrowed by anyone upon returning
void Book::returnBook()
{
    this->borrower = nullptr;
}

// set borrower and dueDate
void Book::borrowBook(Member& borrower, Date dueDate)
{
    if(this->borrower != nullptr){ // if already borrowed by someone else, throw exception
        throw invalid_argument("Already borrowed");
    } else { // otherwise issue to the member that requested it
        this->borrower = &borrower;
        this->dueDate = dueDate;
    }
}