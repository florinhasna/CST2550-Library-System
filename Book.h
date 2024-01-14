#ifndef _BOOK_H_
#define _BOOK_H_
#include "HelperFunctions.h"

// Book class to store the data of a book
class Book
{
    // properties of the class
    private:
        int bookID;
        std::string bookName;
        std::string authorFirstName;
        std::string authorLastName;
        std::string bookType;
        Date dueDate;
        Member* borrower;
    public: // methods
        Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName); // constructor
        ~Book(); // destructor
        // getter methods
        std::string getBookID();
        std::string getBookName();
        std::string getAuthorFirstName();
        std::string getAuthorLastName();
        Date getDueDate();
        // setter method
        void setDueDate(Date dueDate);
        void returnBook(); // borrowed book returnal
        void borrowBook(Member& borrower, Date dueDate); // issue to a member
};

#endif