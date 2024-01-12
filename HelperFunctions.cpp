#include "HelperFunctions.h"

time_t t = time(0);
tm* now = localtime(&t);

string Date::getCurrentDay(){
    this->year = now->tm_year + 1900;
    this->month = now->tm_mon + 1;
    this->day = now->tm_mday;

    string result;

    result.append(to_string(this->day));
    result.append("/");
    result.append(to_string(this->month));
    result.append("/");
    result.append(to_string(this->year));

    return result;
}

string Date::getDueDate(){
    this->year = now->tm_year + 1900;
    this->month = now->tm_mon + 1;
    this->day = now->tm_mday;

    string result;

    int days_in_month;

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

    // if changes month
    if (this->day + 3 > days_in_month){
        this->day = this->day + 3 - days_in_month;
        this->month = this->month + 1;

        // if changes year
        if (this->month + 1 > 12){
            this->year = this->year + 1;
            this->month = 1;
        }
    } else {
        this->day = this->day + 3; 
    }

    result.append(to_string(this->day));
    result.append("/");
    result.append(to_string(this->month));
    result.append("/");
    result.append(to_string(this->year));

    return result;
}

int read_and_convert_integers(string input)
{
    if(input.empty()){
        return -1;
    }

    regex int_input("^[0-9]+$");
    if(!regex_match(input, int_input)){
        cout << "\nYou need to insert a numerical value...\n\n";
        return -1;
    } else {
        return stoi(input);
    }
}