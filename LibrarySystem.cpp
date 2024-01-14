#include "Person.h" //  HelperFunctions.h and Book.h already included in Person.h

Librarian* logged_in; // pointer to a librarian object that is used when logging in

int main()
{
    // print message
    cout << "Initialising program... " << endl;
    cout << "Putting books on the shelf... " << "\n\n";
    load_books(); // read books from file, create a Book object for each book
    cout << "The program is ready to be used!" << "\n\n";
    // infinite loop, program can be terminated below
    do{
        start(); // start program
    } while(true);
    return 0;
}

void load_books() // loading books from csv file to books vector
{
    string file = "library_books"; // file name

    ifstream booksFile(file.append(".csv")); // open the file

    do{
        // check if the file is open
        if (!booksFile.is_open()) {
            // if not, prompting the user to insert the name of the file
            cerr << "Error opening the file, the name of the file was altered or moved.\n" <<" Specify the name or path..." << endl;
            cout << "DO NOT INCLUDE THE FILE FORMAT! Waiting input: ";
            booksFile.open(file.append(".csv")); // attach format
            cin >> file;
        }
    } while(!booksFile.is_open()); // until right input is given

    string line; // to hold a line of the file

    int row_number = 0; // to keep track of rows, needed only as 0 to skip header line of the file
    while(getline(booksFile, line)){ // until reaches eof
        // read in a line
        istringstream iss(line);
        string row;
        getline(iss, row, '\r'); // read in row at row separator flag '\r'

        if (row_number == 0){ // if header row
            row_number++;
            continue;
        }

        vector<string> aBook; // create a vector to hold data of a book

        string cell; // to store a cell of data from the row
        istringstream cell_finder(row);
        while(getline(cell_finder, cell, ',')){ // get elements separated by coma
            if(cell[0] =='\"'){ // case where the name of the book contains coma
                string part_of_name = cell.append(","); // add the coma back
                while(getline(cell_finder, cell, ',')){
                    if(cell[(int) cell.size() - 1] =='\"'){ // find the end of the name
                        aBook.push_back(part_of_name.append(cell)); // append to name
                    } else {
                        aBook.push_back(cell); // continue reading the line
                    }
                }
            } else { // otherwise simply add it to the vector
                aBook.push_back(cell);
            }
        }
        // add to books vector a Book object with relevant informations
        books.push_back(Book(stoi(aBook[0]), aBook[1], aBook[3], aBook[4]));
        // index 0 for ID, 1 for book name, 3 for author's first name, 4 for author's last name
        
        // clear the vector containing the data of the file to store new data in the next iteration
        aBook.clear(); 
        row_number++;
    }

    cout <<"Books loaded successfuly!" << "\n\n"; // end of reading the file in

    booksFile.close(); // close the file
}

void start()
{
    // get and validate input of user of the desired action taken
    string choice;
    int int_choice;
    do{ // menu to select an option by librarian
        cout << "Select one of the options to proceed (e.g. Select 1 to login to your librarian account): " << endl;
        cout << "1. Login" << endl;
        cout << "2. Create a librarian account" << endl;
        cout << "3. Exit" << "\n\n";
        cin >> choice;

        // check the choice if right input is given, -1 is error flag
        int_choice = read_and_convert_integers(choice);
    } while(!(int_choice > 0 && int_choice < 4));

    cout << "\n";

    switch(int_choice){ // switch between choices accordingly
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
        add_librarian(); // redirect to create an account
    } else {
        cin.ignore(); // otherwise just read in the data for logging in
        string sID;
        int int_sID = -1;
        do{
            // read the input and validate input
            cout << "Enter staff ID to authenticate: ";
            getline(cin, sID);
            int_sID = read_and_convert_integers(sID);
        } while (int_sID == -1); // while is not the error flag

        // validate login by checking if the librarian account is existent
        for (int i=0; i < (int) librarians.size(); i++){
            if(int_sID == librarians[i].getStaffID()){
                cout << "\n" << "Welcome " << librarians[i].getName() << "! ";
                logged_in = &librarians[i]; // set logged in pointer
                load_menu(); // load menu with choices for librarian's actions
                break; // stop iteration
            } 

            // last iteration and incorrect input
            if (i == (int) librarians.size() - 1 && !(int_sID == librarians[i].getStaffID())){
                cout << "\nIncorrect staff ID...\n\n";
            }
        }
    }      
}

void add_librarian() // create a librarian account
{
    // regex to validate input
    regex name_pattern("^[A-Za-z]{3,}\\s[A-Za-z]{3,}$");
    regex address_pattern("^[1-9]+\\s[a-zA-Z]{3,}\\s[a-zA-Z]{3,}\\,\\s[A-Z0-9]{2,}\\s[A-Z0-9]{3,3}$");
    regex email_pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");

    // declare neccessary variables
    string sID, salary;
    string name, address, email;
    int int_sID, int_salary;

    cin.ignore(); // to avoid unwanted behaviour
    // read in librarian details and validate them, using loops to make sure the right input is given
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

    // add the object to the vector holding Librarian instances
    librarians.push_back(Librarian(int_sID, name, address, email, int_salary));

    // print data given
    cout << "\nThe librarian " << name << " has been successfuly created.\n\n Data received:\n";
    cout << "NAME: " << name << endl;
    cout << "ADDRESS: " << address << endl;
    cout << "EMAIL: " << email << endl;
    cout << "STAFF ID: " << int_sID << endl; 
    cout << "SALARY: £" << int_salary << "\n\n";
}

// librarian's set of options
void load_menu()
{
    // to get input
    string choice;
    int int_choice;
    
    do{
        do{
            // print list of options and read input
            cout << "Please select an option: " << "\n";
            cout << "1. Add a member" << endl;
            cout << "2. Issue a book to a member" << endl;
            cout << "3. Return a book" << endl;
            cout << "4. Display the books borrowed by a member" << endl;
            cout << "5. Calculate fines of a member" << endl;
            cout << "6. Logout" << endl;
            cout << "\n";
            cin >> choice;

            int_choice = read_and_convert_integers(choice); // checks and validates input
        } while(!(int_choice > 0 && int_choice < 7));
        
        switch(int_choice){ // switch between cases accordingly
            case 1: logged_in->addMember(); // adding a new member to the library
                    cout << "\n"; 
                    break;
            case 2: issue_book(); break; // issuing a book to a member
            case 3: return_book(); break; // a member returning the book
            case 4: display_books(); break; // display the books borrowed by a member
            case 5: calculate_fine(); break; // calculate the fines owed by the member
            case 6: cout << "Logging out..." << "\n\n"; // log out, return back to login menu
                    logged_in = nullptr; // set the pointer as null
        }
    } while(int_choice != 6); // loop until logging out
}

void issue_book() // issue book to a member
{
    // declare variables
    string mID, bID;
    int int_mID = -1;
    int int_bID = -1;
    cin.ignore(); // avoid unwanted behaviour
    
    // get input for member ID and book ID and validate strings to be integers
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
    
    // when everything has been given
    logged_in->issueBook(int_mID, int_bID);
    cout << endl;
}

// display books borrow by a member
void display_books()
{
    // declare variables
    string mID;
    int int_mID = -1;
    cin.ignore(); // avoid unwanted behaviour

    do{ // read and validate input
        cout << "Enter member ID to see books borrowed by that person: ";
        getline(cin, mID);
        int_mID = read_and_convert_integers(mID);
    } while(int_mID == -1);

    // display books of member
    logged_in->displayBorrowedBooks(int_mID);
    cout << endl;
}

// calculate fine of a member
void calculate_fine() 
{
    // declare variables
    string mID;
    int int_mID = -1;
    cin.ignore(); // avoid unwanted behaviour
    do{ // read and validate input
        cout << "Enter member ID to see outstanding fines of a member: ";
        getline(cin, mID);
        int_mID = read_and_convert_integers(mID);
    } while(int_mID == -1);
    
    // calculate the fine of the member
    logged_in->calcFine(int_mID);
    cout << endl;
}

// member returning a book
void return_book()
{
    // declare variables
    string mID, bID;
    int int_mID = -1;
    int int_bID = -1;
    cin.ignore(); // avoid unwanted behaviour
    
    // get the right input for member ID and book ID
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
    
    // return book of the given ids when validated
    logged_in->returnBook(int_mID, int_bID);
    cout << endl;
}

// check if the staff id was already used
bool check_staff_id(int sID)
{
    // if no accout was created, then it was not used
    if (librarians.empty())
        return false;
    
    // iterate the vector the see if any of the existing IDs are matching the given ID
    for(int i = 0; i < (int) librarians.size(); i++){
        if(librarians[i].getStaffID() == sID){
            cout << "Staff ID was already used, please enter a different one...\n\n";
            return true; // means is used
        }
    }

    return false; // it was not used
}