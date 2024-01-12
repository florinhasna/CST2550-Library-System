#include "Person.h" //  HelperFunctions.h and Book.h already included in Person.h

Librarian* logged_in;

int main()
{
    cout << "Initialising program... " << endl;
    cout << "Putting books on the shelf... " << "\n\n";
    load_books();
    cout << "The program is ready to be used!" << "\n\n";
    do{
        start();
    } while(true);
    return 0;
}

void load_books() // loading books from csv file to books vector
{
    string file = "library_books";

    ifstream booksFile(file.append(".csv")); // open the file

    do{
        // check if the file is open
        if (!booksFile.is_open()) {
            cerr << "Error opening the file, the name of the file was altered or moved." << "\n" <<" Specify the name or path..." << endl;
            cout << "DO NOT INCLUDE THE FILE FORMAT! Waiting input: ";
            booksFile.open(file.append(".csv"));
            cin >> file;
        }
    } while(!booksFile.is_open());

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

    cout <<"Books loaded successfuly!" << "\n\n";

    booksFile.close();
}

void start()
{
    // get and validate input of user of the desired action taken
    string choice;
    int int_choice;
    do{
        cout << "Select one of the options to proceed (e.g. Select 1 to login to your librarian account): " << endl;
        cout << "1. Login" << endl;
        cout << "2. Create a librarian account" << endl;
        cout << "3. Exit" << "\n\n";
        cin >> choice;

        int_choice = read_and_convert_integers(choice);
    } while(!(int_choice > 0 && int_choice < 4));

    cout << "\n";

    switch(int_choice){
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
    regex int_input("^[0-9]+$");
    regex name_pattern("^[A-Za-z]{3,}\\s[A-Za-z]{3,}$");
    regex address_pattern("^[1-9]+\\s[a-zA-Z]{3,}\\s[a-zA-Z]{3,}\\,\\s[A-Z0-9]{2,}\\s[A-Z0-9]{3,3}$");
    regex email_pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    // declare neccessary variables
    string sID, salary;
    string name, address, email;

    // read in librarian details
    do{
        cout << "Enter a four numbers long unique staff ID: ";
        cin >> sID;
    } while (!regex_match(sID, int_input) || check_staff_id(stoi(sID))); 
    cin.ignore();

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
    
    do{
        cout << "Enter annual salary: ";
        cin >> salary;
    } while (!regex_match(salary, int_input) && !(stoi(salary) > 1000));

    librarians.push_back(Librarian(stoi(sID), name, address, email, stoi(salary)));

    cout << "\nThe librarian " << name << " has been successfuly created.\n\n Data received:\n";
    cout << "NAME: " << name << endl;
    cout << "ADDRESS: " << address << endl;
    cout << "EMAIL: " << email << endl;
    cout << "STAFF ID: " << sID << endl; 
    cout << "SALARY: £" << salary << "\n\n";
}

void load_menu()
{
    string choice;
    int int_choice;
    
    do{
        do{
            cout << "Please select an option: " << "\n";
            cout << "1. Add a member" << endl;
            cout << "2. Issue a book to a member" << endl;
            cout << "3. Return a book" << endl;
            cout << "4. Display the books borrowed by a member" << endl;
            cout << "5. Calculate fines of a member" << endl;
            cout << "6. Logout" << endl;
            cout << "\n";
            cin >> choice;

            int_choice = read_and_convert_integers(choice);
        } while(!(int_choice > 0 && int_choice < 7));
        
        switch(int_choice){
            case 1: logged_in->addMember();     
                    cout << "\n"; 
                    break;
            case 2: issue_book(); break;
            case 3: return_book(); break;
            case 4: display_books(); break;
            case 5: calculate_fine(); break;
            case 6: cout << "Logging out..." << "\n\n"; 
                    logged_in = nullptr;
        }
    } while(int_choice != 6);
}

void issue_book()
{
    int mID, bID;
    cout << "Enter member ID of the person who would like to borrow: ";
    cin >> mID;
    cout << "Enter the desired book ID: ";
    cin >> bID;
    logged_in->issueBook(mID, bID);
    cout << endl;
}

void display_books()
{
    int mID;
    cout << "Enter member ID to see books borrowed by that person: ";
    cin >> mID;
    logged_in->displayBorrowedBooks(mID);
    cout << endl;
}

void calculate_fine() 
{
    int mID;
    cout << "Enter member ID to see outstanding fine/s: ";
    cin >> mID;
    logged_in->calcFine(mID);
    cout << endl;
}

void return_book()
{
    int mID, bID;
    cout << "Enter member ID of the person who would like to return: ";
    cin >> mID;
    cout << "Enter book ID of the book to be returned: ";
    cin >> bID;
    logged_in->returnBook(mID, bID);
    cout << endl;
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
bool check_staff_id(int sID)
{
    if (librarians.empty())
        return false;
    
    for(int i = 0; i < (int) librarians.size(); i++){
        if(librarians[i].getStaffID() == sID){
            cout << "Staff ID was already used, please enter a different one...\n\n";
            return true;
        }
    }

    return false;
}