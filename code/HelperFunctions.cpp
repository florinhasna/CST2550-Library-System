#include "HelperFunctions.h"

// importing the current time and date
time_t t = time(0);
tm* now = localtime(&t);

string Date::getCurrentDay() // Date method to return current date
{ 
    // load year, month and day into the Date member
    this->year = now->tm_year + 1900;
    this->month = now->tm_mon + 1;
    this->day = now->tm_mday;

    string result; // declare an empty string

    // build the string holding the date of format dd/mm/yyyy
    result.append(to_string(this->day));
    result.append("/");
    result.append(to_string(this->month));
    result.append("/");
    result.append(to_string(this->year));

    return result; // return the date
}

string Date::getDueDate() // Date method to return dueDate to be set in a book that is borrowed
{
    // initialize the day, month and year
    this->getCurrentDay();
    string result; // declare an empty string use dto be built

    int days_in_month; // declare integer to hold the days in the relevant month after checking

    // months with 30 days
    if (this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11){
        days_in_month = 30;  
    } else if(this->month == 2) { // february
        // checking if is a leap year or not
        if(this->year % 4 == 0){
            days_in_month = 29;
        } else {
            days_in_month = 28;
        }
    } else { // other months with 31
        days_in_month = 31;
    }

    // if the month is changing when adding the 3 days, change month
    if (this->day + 3 > days_in_month){
        // will get the correct day, e.g. if day = 31, then it will become 3
        this->day = this->day + 3 - days_in_month;
        this->month = this->month + 1;

        // if the year is changing
        if (this->month + 1 > 12){
            this->year = this->year + 1;
            this->month = 1;
        }
    } else { // otherwise keep month and year as it is and only increase the day
        this->day = this->day + 3; 
    }

    // build string with computed date
    result.append(to_string(this->day));
    result.append("/");
    result.append(to_string(this->month));
    result.append("/");
    result.append(to_string(this->year));

    return result; // return the date
}

// method to check a string input, which should be made only of numbers, returns the string converted to int
int read_and_convert_integers(string input)
{
    // if nothing has been inserted
    if(input.empty()){
        return -1; // -1 considered as error flag
    }

    // regex used to validate input
    regex int_input("^[0-9]+$");

    if(!regex_match(input, int_input)){ // if it fails the check, then is not containing only numbers
        cout << "\nYou need to insert a numerical value...\n\n";
        return -1;
    } else { // if passes, return converted string to int
        return stoi(input);
    }
}