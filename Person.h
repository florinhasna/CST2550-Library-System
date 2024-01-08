#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>

class Person
{
    private:
        std::string name;
        std::string address;
        std::string email;
    public:
        virtual ~Person();
        std::string getName();
        void setName(std::string name);
        std::string getAddress();
        void setAddress(std::string address);
        std::string getEmail();
        void setEmail(std::string email);
};

#endif