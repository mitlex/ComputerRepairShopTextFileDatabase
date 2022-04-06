// AUTHOR: mitlex
// TITLE: Computer Repair Shop Database
// DATE: 3rd December 2021
// VERSION: v1
// DESCRIPTION: 
//
// This program reads a .txt file of customer data, creates a "customer" object for each line in the file, and populates an array where each element
// is a customer object. The user is shown a menu of options that will allow them to query the database. Each query option will attempt to match user 
// input to particular attributes of one or many customer objects and print those customer objects on screen for the user to see. 
// Each customer object can be thought of as a record.
// The customers array can be thought of as a "database" of customer records that can be queried.
// Users also have the option to write new customer records to the .txt file as long as there is enough space in the customers array
// 
// INPUT: file of customer data
// OUTPUT: database query results

#include <iostream>
#include <fstream>
#include <string>
#include "Customer.h"
using namespace std;

//takes string and makes all characters lower case
string toLowerCase(string& str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }

    return str;
}

//count number of lines in .txt file
int countLines()
{
    ifstream myFile;
    myFile.open("customers.txt");

    string line; //used to check how many lines in file
    int numLines = 0;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            numLines++;
        }
    }
    else //if file isn't open
    {
        cout << "Error opening file to populate database" << endl;
        exit(1); //close app without crashing
    }
    myFile.close();

    return numLines;
}

//compare num lines in .txt file to customers array size
bool compareLinesToArraySize(int numLines, int arrayLength)
{
    if (numLines >= arrayLength)
    {
        return false;
    }

    return true;
}

//general function logic taken from example code given from course
//return whether or not customers array is large enough to add new customer
bool safeToAddCustomer(Customer customers[], int arrayLength)
{
    int numLines = countLines();

    bool safeToAddCustomers = true;
    if (!compareLinesToArraySize(numLines, arrayLength))
    {
        cout << "Database has reached capacity of " << arrayLength << " records, please delete records from .txt source file" << endl << endl;
        safeToAddCustomers = false;
    }

    return safeToAddCustomers;
}

//read .txt file and populate customers array
void populateCustomerArray(Customer customers[], int arrayLength)
{
    ifstream myFile;
    myFile.open("customers.txt");

    if (myFile.is_open())
    {
        string firstName, surName, phoneNum, age, jobCost, jobDesc;
        int lineNum = 0; //current line in file

        //create customer objects and put them in customers array
        while (!myFile.eof())
        {
            myFile >> firstName >> surName >> phoneNum >> age >> jobCost;
            getline(myFile >> ws, jobDesc); //>> ws removes leading whitespace, credit - https://stackoverflow.com/questions/45322228/c-how-to-skip-first-whitespace-while-using-getline-with-ifstream-object-to

            //make entire job description, first name and surname strings lower case
            //allows for consistent job description and customer name queries

            toLowerCase(jobDesc);
            toLowerCase(firstName);
            toLowerCase(surName);

            //make dummy customer
            Customer temp;

            temp.setFirstName(firstName);
            temp.setSurName(surName);
            temp.setPhoneNum(phoneNum);
            temp.setAge(age);
            temp.setJobCost(jobCost);
            temp.setJobDescription(jobDesc);

            customers[lineNum] = temp;

            lineNum++;
        }
    }
    else //if file isn't open
    {
        cout << "Error opening file to populate database" << endl;
        exit(1); //close app without crashing
    }
    myFile.close();
}

string getUserInput()
{
    string input = "";
    cin >> input;

    return input;
}

//validate user input as certain number of digits
//used to validate age, repair cost and phone number query inputs
bool validateInput(string input, const int strLength)
{
    if (strLength == 3) //3 is max age and repair cost string length
    {
        if (input.length() > strLength)
        {
            return false;
        }
    }
    else if (strLength == 11) //11 is phone num string length
    {
        if (input.length() != strLength)
        {
            return false;
        }
    }

    for (int i = 0; i < input.length(); i++)
    {
        if (isdigit(input[i]) == false)
        {
            return false;
        }
    }
    return true;
}

//general function logic taken from example code given from course
//get user input for age, repair cost or phone num queries
string digitInput(const int strLength)
{
    string input = getUserInput();

    while (!validateInput(input, strLength))
    {
        cout << "Invalid input, please try again: ";
        input = getUserInput();
    }

    return input;
}

//prevent menu output to allow user to see query results
//credit: https://stackoverflow.com/questions/37234253/why-is-this-press-enter-to-continue-code-in-c-not-working
void pressEnterToContinue()
{
    cout << "***YOUR QUERY RESULTS ARE DISPLAYED ABOVE***" << endl << endl;
    cout << "Press enter to continue to the options menu." << endl;
    cin.ignore();
    cin.ignore();
}

//outputs all customer records containing matching first name and last name
void nameQuery(Customer customers[], int arrayLength)
{
    string fName, sName;

    //explain query functionality
    cout << endl;
    cout << "This query will return customer records that match exactly with the first and surnames you input." << endl << endl;

    //get user inputs
    cout << "Please input the first name of the customer: ";
    cin >> fName;
    toLowerCase(fName);
    cout << "Please input the surname of the customer: ";
    cin >> sName;
    toLowerCase(sName);
    cout << endl;

    bool match = false;

    cout << "***QUERY RESULTS***: " << endl << endl;

    for (int i = 0; i < arrayLength; i++)
    {
        if (customers[i].getFirstName() == "") //prevent checking of default constructed customer objects
        {
            break;
        }
        else if (fName == customers[i].getFirstName() && sName == customers[i].getSurName())
        {
            cout << customers[i];
            cout << endl;
            match = true;
        }
    }
    if (!match)
    {
        cout << "No customers of that name exist in the database." << endl << endl;
    }

    pressEnterToContinue();
}

//outputs all customer records where a user input substring 
//is found inside the job description of that customer record
void jobDescriptionQuery(Customer customers[], int arrayLength)
{
    string jobDesc;

    //query functionality explanation and user input
    cout << endl << "Please input anything relevant to a job description." << endl;
    cout << "For example, inputting \"keyboard\" will return all records with \"keyboard\" in the job description." << endl;
    cin >> jobDesc;
    cout << endl;

    toLowerCase(jobDesc);

    bool match = false;

    cout << "***QUERY RESULTS***: " << endl << endl;

    for (int i = 0; i < arrayLength; i++)
    {
        if (customers[i].getFirstName() == "") //prevent checking of default constructed customer objects
        {
            break;
        }
        //match record if jobDesc is a substring of current customer object job description
        //credit - https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
        else if (customers[i].getJobDescription().find(jobDesc) != std::string::npos)
        {
            cout << customers[i];
            cout << endl;
            match = true;
        }
    }
    if (!match)
    {
        cout << "No customer records with that job description exist in the database." << endl << endl;
    }
    pressEnterToContinue();
}

//outputs all records that fall within a user defined age bracket
void ageQuery(Customer customers[], int arrayLength)
{
    const int ageStrLength = 3; //allow for inputs 0-999
    string minAge;
    string maxAge;

    //explain query functionality
    cout << endl << "This query asks you to input an age range: a minimum age, and a maximum age." << endl;
    cout << "It will return any records in the database where customers fall within the age bracket you have set." << endl;
    cout << "You can set the minimum age and maximum age as the same age to return records for a specific age." << endl;
    cout << "Ages greater than 3 digits will not be accepted." << endl;

    //get user inputs
    cout << endl << "Please input the minimum age: ";
    minAge = digitInput(ageStrLength);
    cout << endl << "Please input the maximum age: ";
    maxAge = digitInput(ageStrLength);
    cout << endl;

    //convert strings to integers for comparison
    int minAgeInt = stoi(minAge);
    int maxAgeInt = stoi(maxAge);

    bool match = false;

    cout << "***QUERY RESULTS***: " << endl << endl;

    for (int i = 0; i < arrayLength; i++)
    {
        if (customers[i].getFirstName() == "") //prevent checking of default constructed customer objects
        {
            break;
        }
        //match record if customer age within user defined age bracket
        else if ((stoi(customers[i].getAge()) >= minAgeInt) && (stoi(customers[i].getAge()) <= maxAgeInt))
        {
            cout << customers[i];
            cout << endl;
            match = true;
        }
    }
    if (!match)
    {
        cout << "No customer records exist in the database where age falls within the age range you input." << endl << endl;
    }
    pressEnterToContinue();
}

//outputs all records that match a phone number input by user
void phoneNumberQuery(Customer customers[], int arrayLength)
{
    const int phoneNumLength = 11; //allow for inputs 11 digits long e.g. 07000000001
    string phoneNum;

    //explain query functionality
    cout << endl << "This query returns records that match a specific phone number" << endl;
    cout << "Phone numbers of 11 digits length are accepted e.g. 07000000001" << endl;

    //get user input
    cout << endl << "Please input phone number: ";
    phoneNum = digitInput(phoneNumLength);
    cout << endl;

    bool match = false;

    cout << "***QUERY RESULTS***: " << endl << endl;

    for (int i = 0; i < arrayLength; i++)
    {
        if (customers[i].getPhoneNum() == "") //prevent checking of default constructed customer objects
        {
            break;
        }
        //output records with phone numbers matching user input
        else if ((customers[i].getPhoneNum() == phoneNum))
        {
            cout << customers[i];
            cout << endl;
            match = true;
        }
    }
    if (!match)
    {
        cout << "No customer records exist in the database with that phone number." << endl << endl;
    }
    pressEnterToContinue();
}

//outputs all records that fall within a user defined job cost bracket -- refactor some stuff like the query explanation is same as age more or less
void repairCostQuery(Customer customers[], int arrayLength)
{
    const int costStrLength = 3; //allow for inputs 0-999 - repair shop doesn't carry out jobs > £999 in value
    string minCost;
    string maxCost;

    //explain query functionality
    cout << endl << "This query asks you to input a job cost range: a minimum cost, and a maximum cost." << endl;
    cout << "It will return any records in the database where customers fall within the job cost bracket you have set." << endl;
    cout << "You can set the minimum job cost and maximum job cost as the same job cost to return records for a specific job cost." << endl;

    //get user inputs
    cout << endl << "Please input the minimum price: ";
    minCost = digitInput(costStrLength);
    cout << endl << "Please input the maximum price: ";
    maxCost = digitInput(costStrLength);
    cout << endl;

    int minCostInt = stoi(minCost);
    int maxCostInt = stoi(maxCost);

    bool match = false;

    cout << "***QUERY RESULTS***: " << endl << endl;

    for (int i = 0; i < arrayLength; i++)
    {
        if (customers[i].getFirstName() == "") //prevent checking of default constructed customer objects
        {
            break;
        }
        //match record if job cost within user defined job cost bracket
        else if ((stoi(customers[i].getJobCost()) >= minCostInt) && (stoi(customers[i].getJobCost()) <= maxCostInt))
        {
            cout << customers[i];
            cout << endl;
            match = true;
        }
    }
    if (!match)
    {
        cout << "No customer records exist in the database where job cost falls within the job cost range you input." << endl << endl;
    }
    pressEnterToContinue();
}

//writes a new customer to the customers.txt file
void addCustomerToFile(Customer customers[], int arrayLength)
{
    ofstream myFile;
    myFile.open("customers.txt", ios::app); //open file in append mode

    if (myFile.is_open())
    {
        //check if adding a new customer will make num lines in file > customers array size
        if (safeToAddCustomer(customers, arrayLength))
        {
            string firstName, surName, phoneNum, age, jobCost, jobDesc;
            const int costStrLength = 3; //allow for inputs 0-999 - repair shop doesn't carry out jobs > £999 in value
            const int phoneNumLength = 11; //allow for inputs 11 digits long e.g. 07000000001
            const int ageStrLength = 3; //allow for inputs 0-999        

            //get user inputs for record
            cout << "Please enter customer first name: ";
            cin >> firstName;
            cout << "Please enter customer surname: ";
            cin >> surName;
            cout << "Please enter customer phone number (11 digits exactly): ";
            phoneNum = digitInput(phoneNumLength);
            cout << "Please enter customer age (3 digits maximum): ";
            age = digitInput(ageStrLength);
            cout << "Please enter job cost (\x9C) (NOTE: only whole numbers accepted, e.g. enter 15 for \x9C" << "15): ";
            jobCost = digitInput(costStrLength);

            cout << endl;

            cout << "Please enter job description: ";
            cin.ignore();
            getline(cin, jobDesc);
            cout << endl;

            //write user inputs to .txt file
            myFile << "\n" << firstName << " " << surName << " " << phoneNum << " " << age << " " << jobCost << " " << jobDesc;
        }
    }
    else //if file isn't open
    {
        cout << "Error opening file" << endl;
        exit(1); //close app without crashing
    }
    myFile.close();

    cout << "Please note that you will need to quit (enter letter Q at menu) and restart the program to query newly added customers." << endl << endl;
}

//general function logic taken from example code given from course
//prompt user to pick an option from menu
char userMenuChoice()
{
    //get user choice
    cout << "Please enter A, B, C, D, E, F or Q (the first letter you enter will be input): " << endl;
    string input;
    char ans;
    getline(cin, input);
    while (input == "")
        getline(cin, input);
    ans = input[0];
    return ans;
}

//general function logic taken from example code given from course
void displayMenu()
{
    cout << "Here are your query options:" << endl << endl;

    cout << "***READ FROM DATABASE OPTIONS***" << endl;
    cout << "Query by:" << endl;
    cout << "A) Customer first and last name" << endl;
    cout << "B) Job description" << endl;
    cout << "C) A range of customer ages" << endl;
    cout << "D) Customer phone number" << endl;
    cout << "E) A range of job prices" << endl << endl;

    cout << "***OTHER OPTIONS***" << endl;
    cout << "F) Add a new customer to the database" << endl;
    cout << "Q) Quit the Program" << endl << endl;
}

//general function logic taken from example code given from course
//run query selected by user
void runMenu(Customer customers[], int arrayLength)
{
    //display menu
    displayMenu();

    //perform queries
    bool anotherQuery = true;
    int answer;
    do
    {
        answer = userMenuChoice();
        switch (answer)
        {
        case 'A':
        case 'a':
            nameQuery(customers, arrayLength);
            displayMenu();
            break;
        case 'B':
        case 'b':
            jobDescriptionQuery(customers, arrayLength);
            displayMenu();
            break;
        case 'C':
        case 'c':
            ageQuery(customers, arrayLength);
            displayMenu();
            break;
        case 'D':
        case 'd':
            phoneNumberQuery(customers, arrayLength);
            displayMenu();
            break;
        case 'E':
        case 'e':
            repairCostQuery(customers, arrayLength);
            displayMenu();
            break;
        case 'F':
        case 'f':
            addCustomerToFile(customers, arrayLength);
            displayMenu();
            break;
        case 'Q':
        case 'q':
            cout << endl << "Thank you for using the Computer Repair Shop Database! Goodbye!" << endl;
            anotherQuery = false;
            break;
        default:
            cout << "Your choice was invalid, please try again. " << endl << endl;
        }
    } while (anotherQuery);
}

void welcome()
{
    cout << "**************************************************" << endl;
    cout << "***WELCOME TO THE COMPUTER REPAIR SHOP DATABASE***" << endl;
    cout << "**************************************************" << endl << endl;
}

int main()
{
    //variable declarations
    const int arraySize = 75; //max number of customers in database
    Customer customers[arraySize]; //store customer objects here

    welcome(); //program welcome message

    populateCustomerArray(customers, arraySize); //read in file and populate customers array
    int customersLength = sizeof(customers) / sizeof(customers[0]); //calculate length of array

    //run menu for querying customer data
    runMenu(customers, customersLength);

    return 0;
}
