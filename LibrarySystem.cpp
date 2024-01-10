#include "Person.h" // Book.h already included in Person.h
#include <fstream>
#include <sstream>
using namespace std;

void load_books(); // read books from a file
void start(); // initialize the program
void add_librarian(); // create a Librarian object
void login(); // login to the Librarian account
void load_menu(); // loads menu after login

vector<Librarian> librarians;
vector<Book> books;
Librarian* logged_in;

int main(){
    do{
        load_books();
        start();
    } while(true);
    return 0;
}

void load_books()
{
    cout << "Putting books on the shelf... " << "\n\n";  

    ifstream booksFile("library_books.csv"); // open the file

    // check if the file is open
    if (!booksFile.is_open()) {
        cerr << "Error opening the file, exiting..." << endl;
        exit(1); // exit error 1
    }
    
    string line;

    int row_number = 0;
    while(getline(booksFile, line)){
        // read in a line
        istringstream iss(line);
        string row;
        getline(iss, row, '\r');

        if (row_number == 0){
            row_number++;
            continue;
        }

        vector<string> aBook;

        string cell;
        istringstream cell_finder(row);
        while(getline(cell_finder, cell, ',')){
            if(cell[0] =='\"'){ // case where the name of the book contains coma
                string part_of_name = cell.append(","); // add the coma back
                while(getline(cell_finder, cell, ',')){
                    if(cell[(int) cell.size() - 1] =='\"'){ // find the end of the name
                        aBook.push_back(part_of_name.append(cell)); // append to name
                    } else {
                        aBook.push_back(cell); // continue reading the line
                    }
                }
            } else {
                aBook.push_back(cell);
            }
        }

        books.push_back(Book(stoi(aBook[0]), aBook[1], aBook[3], aBook[4]));
        
        aBook.clear();
        row_number++;
    }

    booksFile.close();
}

void start()
{
    // get and validate input of user of the desired action taken
    int choice;
    do{
        cout << "Select one of the options to proceed (e.g. Select 1 to login to your librarian account): " << endl;
        cout << "1. Login" << endl;
        cout << "2. Create a librarian account" << endl;
        cout << "3. Exit" << "\n\n";
        cin >> choice;
    } while(!(choice > 0 && choice < 4));

    cout << "\n";

    switch(choice){
        case 1: login(); break;
        case 2: add_librarian(); break;
        case 3: cout << "Exiting program..."; exit(0); 
    }
}

// A librarian authenticating with his staffID
void login()
{
    // check if there is any account created for a librarian
    if (librarians.size() == 0){
        cout << "There are no accounts created, you need to create an account... redirecting" << "\n" << endl;
        add_librarian();
    } else {
        cout << "Enter staff ID to authenticate: ";
        int sID;
        cin >> sID;

        // validate login
        for (int i=0; i < (int) librarians.size(); i++){
            if(sID == librarians[i].getStaffID()){
                cout << "\n" << "Welcome " << librarians[i].getName() << "! ";
                logged_in = &librarians[i];
                load_menu();
                break;
            } 

            if (i == (int) librarians.size() - 1 && !(sID == librarians[i].getStaffID())){
                cout << "Incorrect staff ID, try again... " << endl;
            }
        }
    }      
}

void add_librarian()
{
    // declare neccessary variables
    int sID, salary;
    string name, address, email;

    // read in librarian details
    cout << "Enter a unique staff ID: ";
    cin >> sID;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter address: ";
    getline(cin, address);

    cout << "Enter E-Mail: ";
    getline(cin, email);

    cout << "Enter salary: ";
    cin >> salary;

    librarians.push_back(Librarian(sID, name, address, email, salary));

    cout << "\n" << "Staff ID number: " << sID << " has been created successfully" << "\n\n";
}

void load_menu()
{
    int choice;
    do{
        cout << "Please select a valid option: " << "\n\n";
        cout << "1. Add a member" << endl;
        cout << "2. Issue a book" << endl;
        cout << "3. Return a book" << endl;
        cout << "4. Display the books borrowed by a member" << endl;
        cout << "5. Logout" << endl;
        cout << "\n";
        cin >> choice;
    } while(!(choice > 0 && choice < 6));
    
    switch(choice){
        case 1: logged_in->addMember(); break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: cout << "Logging out..." << "\n\n"; 
                logged_in = nullptr;
    }
}