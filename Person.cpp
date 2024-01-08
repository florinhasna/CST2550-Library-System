#include "Person.h"

Person::~Person() // destructor
{ 
}

// returns name
std::string Person::getName() 
{
    return name;
}

// sets new name
void Person::setName(std::string name) 
{
    this->name = name;
}

// returns address
std::string Person::getAddress() 
{
    return address;
}

// sets new address
void Person::setAddress(std::string address) 
{
    this->address = address;
}

// returns email
std::string Person::getEmail() 
{
    return email;
}

// sets new email
void Person::setEmail(std::string email) 
{
    this->email = email;
}

// LIBRARIAN DERIVED CLASS METHODS

// constructor
Librarian::Librarian(int staffID, std::string name, std::string address, std::string email, int salary)
{
    this->staffID = staffID;
    setName(name);
    setAddress(address);
    setEmail(email);
    this->salary = salary;
}

// void Librarian::addMember()
// {   
// }

// void Librarian::issueBook(int memberID, int bookID)
// {
// }

// void Librarian::returnBook(int memberID, int bookID)
// {
// }

// void Librarian::displayBorrowedBooks(int memberID)
// {
// }

// void Librarian::calcFine(int memberID)
// {
// }

int Librarian::getStaffID()
{
    return staffID;
}

void Librarian::setStaffID(int staffID)
{
    this->staffID = staffID;
}

int Librarian::getSalary()
{
    return salary;
}

void Librarian::setSalary(int salary)
{
    this->salary = salary;
}

// MEMBER DERIVED CLASS METHODS 

// constructor       
Member::Member (int memberID, std::string name, std::string address, std::string email)
{
    this->memberID = memberID;
    setName(name);
    setAddress(address);
    setEmail(email);
}

// returns the ID as a string
std::string Member::getMemberId() 
{
      return std::to_string(memberID);
}

// // returns a vector of borrowed books
// std::vector<Book> Member::getBooksBorrowed() 
// {
// }

// // add a new book borrow
// void Member::setBooksBorrowed(Book book)
// {
// }