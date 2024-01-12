#include "Person.h"

vector<Member> members;
vector<Librarian> librarians;
Date date_object;

Person::~Person() // destructor
{ 
}

// returns name
string Person::getName() 
{
    return name;
}

// sets new name
void Person::setName(string name) 
{
    this->name = name;
}

// returns address
string Person::getAddress() 
{
    return address;
}

// sets new address
void Person::setAddress(string address) 
{
    this->address = address;
}

// returns email
string Person::getEmail() 
{
    return email;
}

// sets new email
void Person::setEmail(string email) 
{
    this->email = email;
}

// MEMBER DERIVED CLASS METHODS 

// constructor       
Member::Member (int memberID, string name, string address, string email)
{
    this->memberID = memberID;
    this->setName(name);
    this->setAddress(address);
    this->setEmail(email);
}

// returns the ID as a string
string Member::getMemberId() 
{
      return to_string(memberID);
}

// returns a vector of borrowed books
vector<Book*> Member::getBooksBorrowed() 
{
    return booksLoaned;
}

// add a new book borrow
void Member::setBooksBorrowed(Book* book)
{
    if (!book) { // null pointer given
        cout << "System error whilt trying to handle the request.\n"; 
        return;
    }

    auto it = find(this->booksLoaned.begin(), this->booksLoaned.end(), book);

    if (it != this->booksLoaned.end()) {
        it = this->booksLoaned.erase(it); // Erase the borrowed book and update the iterator
        cout << book->getBookName() << " has been returned successfully.\n";
    } else {
        this->booksLoaned.push_back(book);
    }
}

// LIBRARIAN DERIVED CLASS METHODS

// constructor
Librarian::Librarian(int staffID, string name, string address, string email, int salary)
{
    this->staffID = staffID;
    this->setName(name);
    this->setAddress(address);
    this->setEmail(email);
    this->salary = salary;
}

void Librarian::addMember()
{   
    regex int_input("^[0-9]+$");
    regex name_pattern("^[A-Za-z]{3,}\\s[A-Za-z]{3,}$");
    regex address_pattern("^[1-9]+\\s[a-zA-Z]{3,}\\s[a-zA-Z]{3,}\\,\\s[A-Z0-9]{2,}\\s[A-Z0-9]{3,3}$");
    regex email_pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    
    string mID; // memberID
    string name, address, email;
    int int_mID;

    cin.ignore();
    // read in librarian details
    do{
        cout << "Enter a four numbers long unique staff ID: ";
        getline(cin, mID);
        int_mID = read_and_convert_integers(mID);
    } while (!(int_mID > 999 && int_mID < 10000) || check_member_id(int_mID));

    do {
        cout << "Enter full name: ";
        getline(cin, name);
    } while(!regex_match(name, name_pattern));
    
    do{
        cout << "Enter first line of address and postcode in capitals separated by a coma...\n";
        cout << "e.g.: 35 Hendon Way, NW9 7FJ -> Waiting input: ";
        getline(cin, address);
    } while (!regex_match(address, address_pattern));
    
    do {
        cout << "Enter a valid E-Mail: ";
        getline(cin, email);
    } while (!regex_match(email, email_pattern));

    members.push_back(Member(int_mID, name, address, email));

    cout << "\nThe member " << name << " has been successfuly created.\n\n";
    cout <<  "Data received:\n";
    cout << "NAME: " << name << endl;
    cout << "ADDRESS: " << address << endl;
    cout << "EMAIL: " << email << endl;
    cout << "MEMBER ID: " << int_mID << endl; 
}

void Librarian::issueBook(int memberID, int bookID)
{
    Member* borrower;
    Book* book;
    int member_position;
    member_position = get_member_position(memberID);

    if(member_position >= 0){
        borrower = &members[member_position];

        member_position = get_book_position(bookID);
        if(member_position >=0){
            book = &books[member_position];
        } else {
            cout << "BookID is invalid, try again...\n";
            return;
        }

        try{
            book->borrowBook(*borrower, date_object);
        } catch (const exception& e) {
            cout << "\nThe book was already borrowed...\n";
            return;
        }

        borrower->setBooksBorrowed(book);
        cout << "\nThe book " << book->getBookName();
        cout << " was issued to " << borrower->getName() << "\n";
    } else {
        cout << "MemberID is invalid, try again...\n";
        return;
    }
}

void Librarian::returnBook(int memberID, int bookID)
{
    int member_position;
    int book_position;

    member_position = get_member_position(memberID);
    book_position = get_book_position(bookID);

    if(book_position < 0) {
        cout << "BookID is invalid, try again...\n";
        return;
    }

    if (member_position >= 0){
        vector<Book*> borrowed = members[member_position].getBooksBorrowed();

        cout << "\n";
        this->calcFine(memberID);
        for (int i = 0; i < (int) borrowed.size(); i++){
            if (borrowed[i]->getBookID() == to_string(bookID)){
                members[member_position].setBooksBorrowed(borrowed[i]);
                borrowed[i]->returnBook();
                return;
            }
        }

        cout << "The book was not borrowed by this member to be returned...\n";
    } else {
        cout << "MemberID is invalid, try again...\n";
        return;
    }
}

void Librarian::displayBorrowedBooks(int memberID)
{
    int member_position;
    member_position = get_member_position(memberID);

    if (member_position >= 0){
        vector<Book*> borrowed = members[member_position].getBooksBorrowed();

        if (borrowed.empty()){
            cout << "\n" << members[member_position].getName() << " does not have any books borrowed.\n";
            return;
        }

        cout << "\nThe books borrowed by " << members[member_position].getName() << " are : \n";

        for(int book_position = 0; book_position < (int) borrowed.size(); book_position++){
            cout << book_position + 1 << ". " << borrowed[book_position]->getBookName() << " written by " << borrowed[book_position]->getAuthorFirstName() << " ";
            cout << borrowed[book_position]->getAuthorLastName() <<"\n";
            cout << "   - To be returned no later than: " << borrowed[book_position]->getDueDate().getDueDate() << "\n";
        }
    } else {
        cout << "MemberID is invalid, try again...\n";
        return;
    }

    cout << endl;
}

void Librarian::calcFine(int memberID)
{
    int member_position;
    member_position = get_member_position(memberID);

    if (member_position >= 0) {
        Date today_date;
        today_date.getCurrentDay(); // initialize with current date
        vector<Book*> borrowed = members[member_position].getBooksBorrowed();

        if(borrowed.empty()){
            cout << "\n" << members[member_position].getName() << " does not have any borrowed books currently...\n";
            return;
        }

        for(int j = 0; j < (int) borrowed.size(); j++){
            vector<int> date;
            string date_int;
            istringstream book_due_date(borrowed[j]->getDueDate().getDueDate());
            
            // separate the date into number strings, add the conversion to int to date vector
            while (getline(book_due_date, date_int, '/')){
                date.push_back(stoi(date_int));
            }

            int due_day = date[0];
            int due_month = date[1];
            // int due_year = date[2];

            if(due_month < today_date.month){

                int days_in_month;
                int overdue = today_date.day;

                for(int k = today_date.month - 1; k >= due_month; k--){
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

                cout << borrowed[j]->getBookName() << " is " << overdue - due_day << " days overdue." << endl;
                cout << "   - A fine of " << overdue - due_day << "£ has to be paid." << endl;  
            } else {
                if (today_date.day > due_day){
                    int overdue = today_date.day - due_day;
                    cout << borrowed[j]->getBookName() << " is " << overdue << " days overdue." << endl;
                    cout << "   - A fine of " << overdue << "£ has to be paid." << endl;
                } else {
                    cout << "The member is not due any fine for the book: " << borrowed[j]->getBookName() << "\n";                 
                }
            }
        }
    } else {
        cout << "MemberID is invalid, try again...\n";
        return;
    }

    cout << endl;
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


// part of helper functions
int get_member_position(int mID)
{
    int error_flag = -1;

    for (int i=0; i < (int) members.size(); i++){
        if(members[i].getMemberId() == to_string(mID)){
            return i;
        }
    }

    return error_flag;
}

int get_book_position(int bID)
{
    int error_flag = -1;

    for (int i=0; i < (int) books.size(); i++){
        if(books[i].getBookID() == to_string(bID)){
            return i;
        }
    }

    return error_flag;
}

bool check_member_id(int mID)
{
    if (members.empty())
        return false;
    
    for(int i = 0; i < (int) members.size(); i++){
        if(members[i].getMemberId() == to_string(mID)){
            cout << "Member ID was already used, please enter a different one...\n\n";
            return true;
        }
    }

    return false;
}