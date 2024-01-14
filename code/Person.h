#ifndef _PERSON_H_
#define _PERSON_H_
#include "Book.h" // HelperFunctions.h already included in Book.h

// Base class
class Person
{
    private: // properties
        std::string name;
        std::string address;
        std::string email;
    public: // setter and getter methods + destructor
        virtual ~Person();
        std::string getName();
        void setName(std::string name);
        std::string getAddress();
        void setAddress(std::string address);
        std::string getEmail();
        void setEmail(std::string email);
};

// Derived class inheriting from Person
class Member: public Person
{
    private: // properties
        int memberID;
        std::vector<Book*> booksLoaned;
    public: 
        Member (int memberID, std::string name, std::string address, std::string email); // constructor
        // getter methods
        std::string getMemberId();
        std::vector<Book*> getBooksBorrowed();
        // setter methods, used to set a pointer to a Book object, being the book borrowed
        void setBooksBorrowed(Book* book);
};

// Derived class inheriting from Person
class Librarian: public Person
{
    private: // properties
        int staffID;
        int salary;
    public:
        Librarian(int staffID, std::string name, std::string address, std::string email, int salary); // constructor
        void addMember(); // method to create a new member account
        void issueBook(int memberID, int bookID); // used to issue a book to a member
        void returnBook(int memberID, int bookID); // return that book when is the case
        void displayBorrowedBooks(int memberID); // display all the books that a member borrowed
        void calcFine(int memberID); // calcutes the fines that a member needs to pay for overdue books
        // setter and getter methods
        int getStaffID();
        void setStaffID(int staffID);
        int getSalary();
        void setSalary(int salary);
};

#endif