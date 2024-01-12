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
        cin.ignore();
        string sID;
        int int_sID = -1;
        do{
            cout << "Enter staff ID to authenticate: ";
            getline(cin, sID);
            int_sID = read_and_convert_integers(sID);
        } while (int_sID == -1);

        // validate login
        for (int i=0; i < (int) librarians.size(); i++){
            if(int_sID == librarians[i].getStaffID()){
                cout << "\n" << "Welcome " << librarians[i].getName() << "! ";
                logged_in = &librarians[i];
                load_menu();
                break;
            } 

            if (i == (int) librarians.size() - 1 && !(int_sID == librarians[i].getStaffID())){
                cout << "\nIncorrect staff ID...\n\n";
            }
        }
    }      
}

void add_librarian()
{
    regex name_pattern("^[A-Za-z]{3,}\\s[A-Za-z]{3,}$");
    regex address_pattern("^[1-9]+\\s[a-zA-Z]{3,}\\s[a-zA-Z]{3,}\\,\\s[A-Z0-9]{2,}\\s[A-Z0-9]{3,3}$");
    regex email_pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    // declare neccessary variables
    string sID, salary;
    string name, address, email;
    int int_sID, int_salary;

    cin.ignore();
    // read in librarian details
    do{
        cout << "Enter a four numbers long unique staff ID: ";
        getline(cin, sID);
        int_sID = read_and_convert_integers(sID);
    } while (!(int_sID > 999 && int_sID < 10000) || check_staff_id(int_sID)); 

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
        getline(cin, salary);
        int_salary = read_and_convert_integers(salary);
    } while (!(int_salary > 1000));

    librarians.push_back(Librarian(int_sID, name, address, email, int_salary));

    cout << "\nThe librarian " << name << " has been successfuly created.\n\n Data received:\n";
    cout << "NAME: " << name << endl;
    cout << "ADDRESS: " << address << endl;
    cout << "EMAIL: " << email << endl;
    cout << "STAFF ID: " << int_sID << endl; 
    cout << "SALARY: £" << int_salary << "\n\n";
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
    string mID, bID;
    int int_mID = -1;
    int int_bID = -1;
    cin.ignore();
    
    do{
        cout << "Enter member ID of the person who would like to borrow: ";
        getline(cin, mID);
        int_mID = read_and_convert_integers(mID);
    } while (int_mID == -1);
    
    do{
        cout << "Enter the desired book ID: ";
        getline(cin, bID);
        int_bID = read_and_convert_integers(bID);
    } while (int_bID == -1);
    
    logged_in->issueBook(int_mID, int_bID);
    cout << endl;
}

void display_books()
{
    string mID;
    int int_mID = -1;
    cin.ignore();

    do{
        cout << "Enter member ID to see books borrowed by that person: ";
        getline(cin, mID);
        int_mID = read_and_convert_integers(mID);
    } while(int_mID == -1);

    logged_in->displayBorrowedBooks(int_mID);
    cout << endl;
}

void calculate_fine() 
{
    string mID;
    int int_mID = -1;
    cin.ignore();
    do{
        cout << "Enter member ID to see outstanding fines of a member: ";
        getline(cin, mID);
        int_mID = read_and_convert_integers(mID);
    } while(int_mID == -1);
    
    logged_in->calcFine(int_mID);
    cout << endl;
}

void return_book()
{
    string mID, bID;
    int int_mID = -1;
    int int_bID = -1;
    cin.ignore();
    
    do{
        cout << "Enter member ID of the person who would like to return: ";
        getline(cin, mID);
        int_mID = read_and_convert_integers(mID);
    } while (int_mID == -1);
    
    do{
        cout << "Enter the book ID: ";
        getline(cin, bID);
        int_bID = read_and_convert_integers(bID);
    } while (int_bID == -1);
    
    logged_in->returnBook(int_mID, int_bID);
    cout << endl;
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