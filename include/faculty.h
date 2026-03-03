#pragma once
#include "person.h"
class Faculty : public Person {
protected:
    string facultyID;
    string department;
    string officeLocation;
    string officeHours;
    vector<string> coursesTeaching;
    
public:
    Faculty() {}
    Faculty(string id, string fname, string lname, string em, string phone,
           string street, string ct, string st, string zip, string user, string pass,
           string dept, string office, string hours)
        : Person(id, fname, lname, em, phone, street, ct, st, zip, user, pass, "Faculty"),
          facultyID(id), department(dept), officeLocation(office), officeHours(hours) {}
    
    string getDepartment() const { return department; }
    string getOfficeLocation() const { return officeLocation; }
    string getOfficeHours() const { return officeHours; }
    vector<string> getCoursesTeaching() const { return coursesTeaching; }
    
    void addCourse(string courseID) { coursesTeaching.push_back(courseID); }
    void setOfficeHours(string hours) { officeHours = hours; }
    
    string toString() const override {
        string courses = "";
        for(size_t i = 0; i < coursesTeaching.size(); i++) {
            courses += coursesTeaching[i];
            if(i < coursesTeaching.size() - 1) courses += ",";
        }
        return Person::toString() + "|" + department + "|" + officeLocation + "|" + 
               officeHours + "|" + courses;
    }
    
    void displayInfo() const override {
        Person::displayInfo();
        cout << "Department: " << department << endl;
        cout << "Office: " << officeLocation << endl;
        cout << "Office Hours: " << officeHours << endl;
    }
};

class Professor : public Faculty {
public:
    Professor() {}
    Professor(string id, string fname, string lname, string em, string phone,
             string street, string ct, string st, string zip, string user, string pass,
             string dept, string office, string hours)
        : Faculty(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
                 dept, office, hours) {
        role = "Professor";
    }
};

class AssociateProfessor : public Faculty {
public:
    AssociateProfessor() {}
    AssociateProfessor(string id, string fname, string lname, string em, string phone,
                      string street, string ct, string st, string zip, string user, string pass,
                      string dept, string office, string hours)
        : Faculty(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
                 dept, office, hours) {
        role = "AssociateProfessor";
    }
};

class AssistantProfessor : public Faculty {
public:
    AssistantProfessor() {}
    AssistantProfessor(string id, string fname, string lname, string em, string phone,
                      string street, string ct, string st, string zip, string user, string pass,
                      string dept, string office, string hours)
        : Faculty(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
                 dept, office, hours) {
        role = "AssistantProfessor";
    }
};

class Lecturer : public Faculty {
public:
    Lecturer() {}
    Lecturer(string id, string fname, string lname, string em, string phone,
            string street, string ct, string st, string zip, string user, string pass,
            string dept, string office, string hours)
        : Faculty(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
                 dept, office, hours) {
        role = "Lecturer";
    }
};

class Staff : public Person {
protected:
    string staffID;
    string staffRole;
    string department;
    string officeLocation;
    
public:
    Staff() {}
    Staff(string id, string fname, string lname, string em, string phone,
         string street, string ct, string st, string zip, string user, string pass,
         string staffR, string dept, string office)
        : Person(id, fname, lname, em, phone, street, ct, st, zip, user, pass, "Staff"),
          staffID(id), staffRole(staffR), department(dept), officeLocation(office) {}
    
    string getStaffRole() const { return staffRole; }
    string getDepartment() const { return department; }
    string getOfficeLocation() const { return officeLocation; }
    
    string toString() const override {
        return Person::toString() + "|" + staffRole + "|" + department + "|" + officeLocation;
    }
    
    void displayInfo() const override {
        Person::displayInfo();
        cout << "Staff Role: " << staffRole << endl;
        cout << "Department: " << department << endl;
        cout << "Office: " << officeLocation << endl;
    }
};

class AdministrativeStaff : public Staff {
public:
    AdministrativeStaff() {}
    AdministrativeStaff(string id, string fname, string lname, string em, string phone,
                       string street, string ct, string st, string zip, string user, string pass,
                       string dept, string office)
        : Staff(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
               "Administrative", dept, office) {
        role = "AdministrativeStaff";
    }
};

class TechnicalStaff : public Staff {
public:
    TechnicalStaff() {}
    TechnicalStaff(string id, string fname, string lname, string em, string phone,
                  string street, string ct, string st, string zip, string user, string pass,
                  string dept, string office)
        : Staff(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
               "Technical", dept, office) {
        role = "TechnicalStaff";
    }
};

class AdvisorStaff : public Staff {
private:
    vector<string> advisees;
    
public:
    AdvisorStaff() {}
    AdvisorStaff(string id, string fname, string lname, string em, string phone,
                string street, string ct, string st, string zip, string user, string pass,
                string dept, string office)
        : Staff(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
               "Advisor", dept, office) {
        role = "AdvisorStaff";
    }
    
    void addAdvisee(string studentID) { advisees.push_back(studentID); }
    vector<string> getAdvisees() const { return advisees; }
};

class Administrator : public Person {
private:
    string adminLevel;
    
public:
    Administrator() {}
    Administrator(string id, string fname, string lname, string em, string phone,
                 string street, string ct, string st, string zip, string user, string pass,
                 string level)
        : Person(id, fname, lname, em, phone, street, ct, st, zip, user, pass, "Administrator"),
          adminLevel(level) {}
    
    string getAdminLevel() const { return adminLevel; }
};
