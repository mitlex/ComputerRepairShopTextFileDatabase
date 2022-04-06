#pragma once
#include <string>

using namespace std;

class Customer
{
private:
    string firstName;
    string surName;
    string phoneNum;
    string age;
    string jobCost;
    string jobDescription;

public:
    //constructors
    Customer();
    Customer(string fn, string sn, string pn, string a, string c, string rc);

    //mutators
    string getFirstName();
    void setFirstName(string fn);

    string getSurName();
    void setSurName(string sn);

    string getPhoneNum();
    void setPhoneNum(string pn);

    string getAge();
    void setAge(string a);

    string getJobDescription();
    void setJobDescription(string c);

    string getJobCost();
    void setJobCost(string jc);

    //overload << to allow customer objects to be output with cout
    friend ostream& operator << (ostream& outs, const Customer& c);
};


