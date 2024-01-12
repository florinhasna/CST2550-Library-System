#include "Person.h"

std::vector<Member> members;
std::vector<Librarian> librarians;
Date date_object;

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
    if (!book) {
        std::cout << "System error whilt trying to handle the request.\n"; // null pointer given
        return;
    }

    auto it = std::find(this->booksLoaned.begin(), this->booksLoaned.end(), book);

    if (it != this->booksLoaned.end()) {
        it = this->booksLoaned.erase(it); // Erase the borrowed book and update the iterator
        std::cout << book->getBookName() << " has been returned successfully.\n";
    } else {
        this->booksLoaned.push_back(book);
    }
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
    std::regex name_pattern("^[A-Za-z]{3,}\\s[A-Za-z]{3,}$");
    std::regex address_pattern("^[1-9]+\\s[a-zA-Z]{3,}\\s[a-zA-Z]{3,}\\,\\s[A-Z0-9]{2,}\\s[A-Z0-9]{3,3}$");
    std::regex email_pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    // read in librarian details
    do{
        std::cout << "Enter a four numbers long unique staff ID: ";
        std::cin >> mID;
    } while (!(mID > 999 && mID < 10000));

    std::cin.ignore();

    do {
        std::cout << "Enter full name: ";
        std::getline(std::cin, name);
    } while(!std::regex_match(name, name_pattern));
    
    do{
        std::cout << "Enter first line of address and postcode in capitals separated by a coma...\n";
        std::cout << "e.g.: 35 Hendon Way, NW9 7FJ -> Waiting input: ";
        std::getline(std::cin, address);
    } while (!std::regex_match(address, address_pattern));
    
    do {
        std::cout << "Enter a valid E-Mail: ";
        std::getline(std::cin, email);
    } while (!std::regex_match(email, email_pattern));

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
                } catch (const std::exception& e) {
                    break;
                }
                
                borrower->setBooksBorrowed(book);
                std::cout << "\n" << "The book " << book->getBookName() << " was issued to " << borrower->getName() << "\n\n";
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

            for(int j = 0; j < (int) borrowed.size(); j++){
                if(borrowed[j]->getBookID() == std::to_string(bookID)){
                    members[i].setBooksBorrowed(borrowed[j]);
                    borrowed[j]->returnBook();
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
    Date today_date;
    today_date.getCurrentDay();
    for(int i = 0; i < (int) members.size(); i++){
        if(members[i].getMemberId() == std::to_string(memberID)){
            std::vector<Book*> borrowed = members[i].getBooksBorrowed();

            for(int j = 0; j < (int) borrowed.size(); j++){
                int borrowal_day = borrowed[j]->getDueDate().day;
                int borrowal_month = borrowed[j]->getDueDate().month;

                std::cout << "Borrowal day " << borrowal_day << " " << borrowal_month << std::endl;
                std::cout << "Curr day " << today_date.day << " " << today_date.month << std::endl;

                if(borrowal_month < today_date.month){
                    int days_in_month;
                    int overdue = today_date.day - 3;

                    for(int k = today_date.month - 1; k >= borrowal_month; k--){
                        // months with 30 days
                        if (k == 4 || k == 6 || k == 9 || k == 11){
                            days_in_month = 30;  
                        } else if(k == 2) { // february
                            // checking if is a leap year or not
                            if(today_date.year % 4 == 0){
                                days_in_month = 29;
                            } else {
                                days_in_month = 28;
                            }
                        } else { // other months with 31
                            days_in_month = 31;
                        }

                        overdue = overdue + days_in_month;
                    }

                    std::cout << borrowed[j]->getBookName() << " is " << overdue - borrowal_day << " days overdue." << std::endl;
                    std::cout << "   - A fine of " << overdue - borrowal_day << "£ has to be paid." << std::endl;  
                } else {
                    if (today_date.day - borrowal_day > 3){
                        std::cout << borrowed[j]->getBookName() << " is " << today_date.day - borrowal_day - 3 << " days overdue." << std::endl;
                        std::cout << "   - A fine of " << today_date.day - borrowal_day - 3 << "£ has to be paid." << std::endl;
                    } else {
                        std::cout << "The member is not due any fine for the book " << borrowed[j]->getBookName() << "\n"; 
                    }
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