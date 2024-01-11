#include "Person.h"

std::vector<Member> members;
std::vector<Librarian> librarians;
Date date_object;
Date today_date;

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

// returns a vector of borrowed books
std::vector<Book*> Member::getBooksBorrowed() 
{
    return booksLoaned;
}

// add a new book borrow
void Member::setBooksBorrowed(Book* book)
{
    auto it = std::find(this->booksLoaned.begin(), this->booksLoaned.end(), book);
    if(it != this->booksLoaned.end()){
        this->booksLoaned.erase(it);
        std::cout << book->getBookName() << " has been returned successfuly." << "\n";
    } else {
        this->booksLoaned.push_back(book);
    }

    std::cout << (int)this->booksLoaned.size();
}

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
    std::cin.ignore();
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter address: ";
    std::getline(std::cin, address);
    std::cout << "Enter E-Mail: ";
    std::getline(std::cin, email);

    members.push_back(Member(mID, name, address, email));
}

void Librarian::issueBook(int memberID, int bookID)
{
    bool flag = false;
    Member* borrower;
    Book* book;
    for(int i = 0; i < (int) members.size(); i++){
        if(members[i].getMemberId() == std::to_string(memberID)){
            flag = true;
            borrower = &members[i];
            break;
        }
    }

    if(!flag){
        std::cout << "MemberID is invalid, try again..." << "\n\n";
    } else {
        flag=false;
        for(int i = 0; i < (int) books.size(); i++){
            if(books[i].getBookID() == std::to_string(bookID)){
                flag = true;
                book = &books[i];
            }

            if(flag){
                try{
                    book->borrowBook(*borrower, date_object);
                    borrower->setBooksBorrowed(book);
                    std::cout << "\n" << "The book " << book->getBookName() << " was issued to " << borrower->getName() << "\n\n";
                } catch (const std::exception& e) {
                    std::cerr << "The specified book was borrowed by someone else. " << std::endl;
                }
                break;
            }
        }
        
        if(!flag) {
            std::cout << "BookID is invalid, try again..." << "\n\n";
        }
    }
}

void Librarian::returnBook(int memberID, int bookID)
{
    for(int i = 0; i < (int) members.size(); i++){
        if(members[i].getMemberId() == std::to_string(memberID)){
            std::vector<Book*> borrowed = members[i].getBooksBorrowed();

            for(int i = 0; i < (int) borrowed.size(); i++){
                if(borrowed[i]->getBookID() == std::to_string(bookID)){
                    members[i].setBooksBorrowed(borrowed[i]);
                    borrowed[i]->returnBook();
                }
            }
            break;
        }
    }

    this->calcFine(memberID);
}

void Librarian::displayBorrowedBooks(int memberID)
{
    for(int i = 0; i < (int) members.size(); i++){
        if(members[i].getMemberId() == std::to_string(memberID)){
            std::vector<Book*> borrowed = members[i].getBooksBorrowed();

            if((int) borrowed.size() == 0){
                std::cout << "\n" << members[i].getName() << " does not have any books borrowed." << "\n";
                break;
            }

            std::cout << "\n" << "The books borrowed by " << members[i].getName() << " are : " << "\n";

            for(int i = 0; i < (int) borrowed.size(); i++){
                std::cout << i+1 << ". " << borrowed[i]->getBookName() << " written by " << borrowed[i]->getAuthorFirstName() << " ";
                std::cout << borrowed[i]->getAuthorLastName() <<"\n";
                std::cout << "   - To be returned no later than: " << borrowed[i]->getDueDate().getDueDate() << "\n";
            }
            break;
        }
    }

    std::cout << std::endl;
}

void Librarian::calcFine(int memberID)
{
    for(int i = 0; i < (int) members.size(); i++){
        if(members[i].getMemberId() == std::to_string(memberID)){
            std::vector<Book*> borrowed = members[i].getBooksBorrowed();

            for(int i = 0; i < (int) borrowed.size(); i++){
                int borrowal_day = borrowed[i]->getDueDate().day;

                if (borrowal_day > today_date.day){
                    std::cout << borrowed[i]->getBookName() << " is " << borrowal_day - today_date.day << " days overdue." << std::endl;
                    std::cout << "   - A fine of " << borrowal_day - today_date.day << "£ has to be paid." << std::endl;
                }
            }
        }
    }

    std::cout << std::endl;
}

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