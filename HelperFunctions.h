#ifndef _HELPERFUNCTIONS_H_
#define _HELPERFUNCTIONS_H_

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <regex>
#include <fstream>
#include <sstream>
using namespace std;

struct Date{
    int year;
    int month;
    int day;

    string getCurrentDay();
    string getDueDate();
    int getDay();
};

class Person;
class Member;
class Book;
class Librarian;

void load_books(); // read books from a file, puts them in a vector
void start(); // initialize the program
int read_and_convert_integers(string input); // get numerical string input from user and validate it 
void add_librarian(); // create a Librarian object
void login(); // login to the Librarian account
void load_menu(); // loads menu after login
void issue_book(); // get input to issue a book
void return_book(); // get input to return a book
void display_books(); // get input to display the borrowed books
void calculate_fine(); // get input to calculate the fines of a member
bool check_member_id(int mID); // checks if a member id was already used
bool check_staff_id(int sID); // checks if a staff id was already used
int get_member_position(int mID); // return the index position of a member in vector 'members';
int get_book_position(int bID); // return the index position of a book in vector 'books';

extern vector<Book> books;
extern vector<Member> members;
extern vector<Librarian> librarians;

#endif