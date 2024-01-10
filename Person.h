#ifndef _PERSON_H_
#define _PERSON_H_
#include <iostream>
#include <vector>
#include "Book.h"

// Base class
class Person
{
    private:
        std::string name;
        std::string address;
        std::string email;
    public:
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
    private:
        int memberID;
        std::vector<Book*> booksLoaned;
    public:
        Member (int memberID, std::string name, std::string address, std::string email);
        std::string getMemberId();
        std::vector<Book*> getBooksBorrowed();
        void setBooksBorrowed(Book* book);
};

// Derived class inheriting from Person
class Librarian: public Person
{
    private:
        int staffID;
        int salary;
    public:
        Librarian(int staffID, std::string name, std::string address, std::string email, int salary);
        void addMember();
        void issueBook(int memberID, int bookID);
        void returnBook(int memberID, int bookID);
        void displayBorrowedBooks(int memberID);
        void calcFine(int memberID);
        int getStaffID();
        void setStaffID(int staffID);
        int getSalary();
        void setSalary(int salary);
};

#endif