#include "Customer.h"
#include <iostream>

//constructors
Customer::Customer()
{
    firstName = "";
    surName = "";
    phoneNum = "";
    age = "";
    jobDescription = "";
    jobCost = "";
}

Customer::Customer(string fn, string sn, string pn, string a, string jd, string jc)
{
    firstName = fn;
    surName = sn;
    phoneNum = pn;
    age = a;
    jobDescription = jd;
    jobCost = jc;
}

//mutators

string Customer::getFirstName()
{
    return firstName;
}

void Customer::setFirstName(string fn)
{
    firstName = fn;
}

string Customer::getSurName()
{
    return surName;
}

void Customer::setSurName(string sn)
{
    surName = sn;
}

string Customer::getPhoneNum()
{
    return phoneNum;
}

void Customer::setPhoneNum(string pn)
{
    phoneNum = pn;
}

string Customer::getAge()
{
    return age;
}

void Customer::setAge(string a)
{
    age = a;
}

string Customer::getJobDescription()
{
    return jobDescription;
}

void Customer::setJobDescription(string jd)
{
    jobDescription = jd;
}

string Customer::getJobCost()
{
    return jobCost;
}

void Customer::setJobCost(string jc)
{
    jobCost = jc;
}

//overloaded << to allow for terminal output of customer objects
ostream& operator<<(ostream& outs, const Customer& c)
{
    outs << "First Name: " << c.firstName << " " << endl
        << "Surname: " << c.surName << " " << endl
        << "Phone Number: " << c.phoneNum << " " << endl
        << "Age: " << c.age << " " << endl
        << "Job description: " << c.jobDescription << " " << endl
        << "Amount to charge customer: \x9C" << c.jobCost << endl;
    return outs;
}

