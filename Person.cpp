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
    // load the relevant date to properties of the object
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

// returns the vector of borrowed books
vector<Book*> Member::getBooksBorrowed() 
{
    return booksLoaned;
}

// add a new book borrow
void Member::setBooksBorrowed(Book* book)
{
    if (!book) { // null pointer given
        cout << "System error whilst trying to handle the request.\n"; 
        return; // end the execution of the method
    }

    // iterator to see if the book is a member of the booksLoaned vector
    auto it = find(this->booksLoaned.begin(), this->booksLoaned.end(), book);

    // if book is already in the vector, then the request is to return the book 
    if (it != this->booksLoaned.end()) {
        it = this->booksLoaned.erase(it); // Erase the borrowed book and update the iterator
        cout << book->getBookName() << " has been returned successfully.\n";
    } else { // otherwise the request is to borrow it
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
    // regex needed to validate each data of a Librarian
    regex int_input("^[0-9]+$");
    regex name_pattern("^[A-Za-z]{3,}\\s[A-Za-z]{3,}$");
    regex address_pattern("^[1-9]+\\s[a-zA-Z]{3,}\\s[a-zA-Z]{3,}\\,\\s[A-Z0-9]{2,}\\s[A-Z0-9]{3,3}$");
    regex email_pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    
    // declare variables to store data inputs
    string mID;
    string name, address, email;
    int int_mID;

    cin.ignore(); // to avoid getline unwanted behaviour

    // read in member details
    do{
        cout << "Enter a four numbers long unique staff ID: ";
        getline(cin, mID);
        int_mID = read_and_convert_integers(mID); // check and return int number, if -1, then is not valid
    } while (!(int_mID > 999 && int_mID < 10000) || check_member_id(int_mID));

    do { // validate name
        cout << "Enter full name: ";
        getline(cin, name);
    } while(!regex_match(name, name_pattern));
    
    do{ // validate address
        cout << "Enter first line of address and postcode in capitals separated by a coma...\n";
        cout << "e.g.: 35 Hendon Way, NW9 7FJ -> Waiting input: ";
        getline(cin, address);
    } while (!regex_match(address, address_pattern));
    
    do { // validate email
        cout << "Enter a valid E-Mail: ";
        getline(cin, email);
    } while (!regex_match(email, email_pattern));

    // as soon as all data is collected, add member object into the member vector
    members.push_back(Member(int_mID, name, address, email));

    // print inserted data of the member
    cout << "\nThe member " << name << " has been successfuly created.\n\n";
    cout <<  "Data received:\n";
    cout << "NAME: " << name << endl;
    cout << "ADDRESS: " << address << endl;
    cout << "EMAIL: " << email << endl;
    cout << "MEMBER ID: " << int_mID << endl; 
}

// method of Librarian class to issua a book to a member
void Librarian::issueBook(int memberID, int bookID)
{
    // declare two pointers to Member and Book objects
    Member* borrower;
    Book* book;
    int member_position; // position of the member in the vector
    // if -1 is returned, then the memberID is invalid
    member_position = get_member_position(memberID); 

    if(member_position >= 0){ // check is not -1 
        // assign borrower pointer the address of the member object
        borrower = &members[member_position]; 

        // update member_position with book position in books vector
        member_position = get_book_position(bookID); 
        if(member_position >=0){ // check the index is not -1
            // assign book pointer the address of the relevant book
            book = &books[member_position]; 
        } else { // the index returned was -1
            cout << "BookID is invalid, try again...\n";
            return;
        }

        try{ // exception thrown in Book class when book is already borrowed
            // if successful, set the borrower to the Book object
            book->borrowBook(*borrower, date_object);
        } catch (const exception& e) {
            cout << "\nThe book was already borrowed...\n";
            return;
        }

        // and add the book to the booksLoaned vector of Member object
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
    // declare and assign indexes for member and book
    int member_position;
    int book_position;

    member_position = get_member_position(memberID);
    book_position = get_book_position(bookID);

    // check the indexes are not -1
    if(book_position < 0) {
        cout << "BookID is invalid, try again...\n";
        return;
    }

    if (member_position >= 0){
        // get the vector of borrowed books
        vector<Book*> borrowed = members[member_position].getBooksBorrowed();

        cout << "\n";
        this->calcFine(memberID); // check if there is any outstanding fine
        for (int i = 0; i < (int) borrowed.size(); i++){ // iterate through borrowed books and find the relevant book
            if (borrowed[i]->getBookID() == to_string(bookID)){ // found
                // in this case, setBooksBorrowed method will return the book (see Member class)
                members[member_position].setBooksBorrowed(borrowed[i]);
                // set the book as not having any borrower
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

// method to display books that were borrowed by a member
void Librarian::displayBorrowedBooks(int memberID)
{
    // get member index in "members" vector
    int member_position;
    member_position = get_member_position(memberID);

    if (member_position >= 0){ // checking if is not -1 (error flag)
        // get to bookLoaned vector of the member
        vector<Book*> borrowed = members[member_position].getBooksBorrowed();

        if (borrowed.empty()){ // if is empty
            cout << "\n" << members[member_position].getName() << " does not have any books borrowed.\n";
            return;
        }

        // if not empty
        cout << "\nThe books borrowed by " << members[member_position].getName() << " are : \n";

        // iterate through borrowed vector and display details about the borrowal
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

// calculates the outstanding fines of a member
void Librarian::calcFine(int memberID)
{
    // get member index in vector
    int member_position;
    member_position = get_member_position(memberID);

    if (member_position >= 0) { // if member index is valid
        Date today_date; // Date type used to get current day
        today_date.getCurrentDay(); // initialize with current date

        // get books borrowed by the member
        vector<Book*> borrowed = members[member_position].getBooksBorrowed();

        if(borrowed.empty()){ // check if there are any borrowed books
            cout << "\n" << members[member_position].getName() << " does not have any borrowed books currently...\n";
            return;
        }

        // iterate every book
        for(int j = 0; j < (int) borrowed.size(); j++){
            // save the date into a vector
            vector<int> date;
            string date_int;
            // string holding the dueDate for the book
            istringstream book_due_date(borrowed[j]->getDueDate().getDueDate());
            
            // separate the date into number strings, add the conversion to int to date vector
            while (getline(book_due_date, date_int, '/')){ 
                date.push_back(stoi(date_int));
            }

            // getting day and month is due
            int due_day = date[0];
            int due_month = date[1];

            // if month the book was due to be return is a previous one
            if(due_month < today_date.month){

                // get days and overdue number of days
                int days_in_month;
                int overdue = today_date.day;

                // iterate through months until they are equal
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

                    // add days to overdue, when finished, overdue holds the number of days over dueDate
                    overdue = overdue + days_in_month;
                }

                // print how much needs to be paid
                cout << borrowed[j]->getBookName() << " is " << overdue - due_day << " days overdue." << endl;
                cout << "   - A fine of " << overdue - due_day << "£ has to be paid." << endl;  
            } else {
                // if in the same month
                if (today_date.day > due_day){
                    // get the days and print message
                    int overdue = today_date.day - due_day;
                    cout << borrowed[j]->getBookName() << " is " << overdue << " days overdue." << endl;
                    cout << "   - A fine of " << overdue << "£ has to be paid." << endl;
                } else { // still in time
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

// getter method for staffID
int Librarian::getStaffID()
{
    return staffID;
}

// setter method for staffID
void Librarian::setStaffID(int staffID)
{
    this->staffID = staffID;
}

// getter method for salary
int Librarian::getSalary()
{
    return salary;
}

// setter method for staffID
void Librarian::setSalary(int salary)
{
    this->salary = salary;
}


// part of helper functions
int get_member_position(int mID)
{
    int error_flag = -1;

    // iterate through members vector
    for (int i=0; i < (int) members.size(); i++){
        // compare ids, if they match then the ID is vaild and existent
        if(members[i].getMemberId() == to_string(mID)){
            return i; // return index of member object
        }
    }

    return error_flag; // when not found
}

int get_book_position(int bID)
{
    int error_flag = -1;

    // iterate through book vector
    for (int i=0; i < (int) books.size(); i++){
        // compare ids, if they match then the ID is vaild and existent
        if(books[i].getBookID() == to_string(bID)){
            return i; // return index of book object
        }
    }

    return error_flag; // when not found
}

// checks if the member is part of vector, used when adding a member 
bool check_member_id(int mID)
{
    if (members.empty())
        return false; // if no member objects are created
    
    // iterate through members vector to check all instances
    for(int i = 0; i < (int) members.size(); i++){
        if(members[i].getMemberId() == to_string(mID)){ // if IDs match
            cout << "Member ID was already used, please enter a different one...\n\n";
            return true;
        }
    }

    return false; // not found
}