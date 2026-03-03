#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Person {
protected:
    string personID;
    string firstName;
    string lastName;
    string email;
    string phoneNumber;
    string streetAddress;
    string city;
    string state;
    string zipCode;
    string username;
    string password;
    string role;
    
public:
    Person() {}
    Person(string id, string fname, string lname, string em, string phone, 
           string street, string ct, string st, string zip, string user, string pass, string r)
        : personID(id), firstName(fname), lastName(lname), email(em), phoneNumber(phone),
          streetAddress(street), city(ct), state(st), zipCode(zip), username(user), password(pass), role(r) {}
    
    virtual ~Person() {}
    
    string getPersonID() const { return personID; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getEmail() const { return email; }
    string getPhoneNumber() const { return phoneNumber; }
    string getStreetAddress() const { return streetAddress; }
    string getCity() const { return city; }
    string getState() const { return state; }
    string getZipCode() const { return zipCode; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    string getFullAddress() const { return streetAddress + ", " + city + ", " + state + " " + zipCode; }
    
    void setEmail(string em) { email = em; }
    void setPhoneNumber(string phone) { phoneNumber = phone; }
    void setAddress(string street, string ct, string st, string zip) {
        streetAddress = street;
        city = ct;
        state = st;
        zipCode = zip;
    }
    
    virtual string toString() const {
        return personID + "|" + firstName + "|" + lastName + "|" + email + "|" + 
               phoneNumber + "|" + streetAddress + "|" + city + "|" + state + "|" + 
               zipCode + "|" + username + "|" + password + "|" + role;
    }
    
    virtual void displayInfo() const {
        cout << "ID: " << personID << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Address: " << getFullAddress() << endl;
    }
};
