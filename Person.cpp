#include <iostream>
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

// MEMBER DERIVED CLASS METHODS 

// constructor       
Member::Member (int memberID, std::string name, std::string address, std::string email)
{
    this->memberID = memberID;
    this->setName(name);
    this->setAddress(address);
    this->setEmail(email);
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

std::vector<Member> members;

// LIBRARIAN DERIVED CLASS METHODS

// constructor
Librarian::Librarian(int staffID, std::string name, std::string address, std::string email, int salary)
{
    this->staffID = staffID;
    this->setName(name);
    this->setAddress(address);
    this->setEmail(email);
    this->salary = salary;
}

void Librarian::addMember()
{   
    int mID; // memberID
    std::string name, address, email;

    // read in new member details
    std::cout << "Enter a unique member ID: ";
    std::cin >> mID;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cin.ignore(); // read a line
    std::cout << "Enter address: ";
    std::getline(std::cin, address);
    std::cin.ignore();
    std::cout << "Enter E-Mail: ";
    std::cin >> email;

    members.push_back(Member(mID, name, address, email));
    std::cout << members[0].getMemberId();
    std::cout << members[0].getName();
    std::cout << members[0].getEmail();
}

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