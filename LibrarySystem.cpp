#include <iostream>
#include "Person.h"
#include "Book.h"
using namespace std;

void start(); // initialize the program
void add_librarian(); // create a Librarian object
void login(); // login to the Librarian account

vector<Librarian> librarians;

int main(){
    start();
    return 0;
}

void start(){
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
        case 3: break;
    }
}

// A librarian authenticating with his staffID
void login(){
    cout << "Enter staff ID to authenticate: ";
    int sID;
    cin >> sID;

    // validate login
    for (int i=0; i < (int)librarians.size(); i++){
        if(sID == librarians[i].getStaffID()){
            cout << "\n" << "Welcome " << librarians[i].getName();
        } else {
            cout << "\n" << "Incorrect. Try again!" << endl;
            login();
        }
    }  
}

void add_librarian(){
    // declare neccessary variables
    int sID, salary;
    string name, address, email;

    // read in librarian details
    cout << "Enter a unique staff ID: ";
    cin >> sID;
    cout << "Enter name: ";
    getline(cin, name);
    cin.ignore(); // read a line
    cout << "Enter address: ";
    getline(cin, address);
    cin.ignore();
    cout << "Enter E-Mail: ";
    cin >> email;
    cout << "Enter salary: ";
    cin >> salary;

    librarians.push_back(Librarian(sID, name, address, email, salary));

    cout << "\n" << "Staff ID number: " << sID << " has been created successfully" << endl;
    cout << "\n";

    start();
}