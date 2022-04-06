DISCLAIMER: any names, phone numbers, ages etc. used in this program were randomly made up by me.

This assignment was created as part of the coursework for the following module:
https://www.dundee.ac.uk/module/ac51002

This is a basic program written in C++ that functions as a pseudo-database for a computer repair shop. The program aims to showcase an example of the basics of object-oriented programming, containing a user-defined class called "Customer" with appropriate attributes and methods such as constructors and mutators.

Here is a description of the general program functionality:

This program reads in a .txt file (customers.txt) of customer data, creates a "customer" object for each line in the file, and populates an array where each element is a customer object. Each customer object can be thought of as a record. The customers array can be thought of as a "database" of customer records that can be queried.

Here is the first few lines of the customers.txt file:

![image](https://user-images.githubusercontent.com/94235400/161753337-43a95f36-f3a3-4169-aea3-edadfce860e2.png)

From left to right:
First name, last name, phone number, age, job cost, job description

The user is shown a menu of options that will allow them to query the database. Each query option will attempt to match user input to particular attributes of one or many customer objects and print those customer objects on screen for the user to see. 

Users also have the option to write new customer records to the .txt file as long as there is enough space in the customers array.

Here is an example below where I query the database for job descriptions containing the word "Monitor":


![image](https://user-images.githubusercontent.com/94235400/161750602-6fb9fd72-4561-4169-9952-28c1c1e0d9a0.png)


