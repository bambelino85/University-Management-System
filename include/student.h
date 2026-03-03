#pragma once
#include "person.h"
#include <iomanip>
class Student : public Person {
protected:
    string studentID;
    string major;
    double gpa;
    string enrollmentStatus;
    string academicStanding;
    int creditsCompleted;
    string advisorID;
    
public:
    Student() : gpa(0.0), creditsCompleted(0) {}
    Student(string id, string fname, string lname, string em, string phone, 
            string street, string ct, string st, string zip, string user, string pass,
            string maj, double g, string status, string standing, int credits, string advisor)
        : Person(id, fname, lname, em, phone, street, ct, st, zip, user, pass, "Student"),
          studentID(id), major(maj), gpa(g), enrollmentStatus(status), 
          academicStanding(standing), creditsCompleted(credits), advisorID(advisor) {}
    
    string getMajor() const { return major; }
    double getGPA() const { return gpa; }
    string getEnrollmentStatus() const { return enrollmentStatus; }
    string getAcademicStanding() const { return academicStanding; }
    int getCreditsCompleted() const { return creditsCompleted; }
    string getAdvisorID() const { return advisorID; }
    
    void setMajor(string maj) { major = maj; }
    void setGPA(double g) { gpa = g; }
    void setAdvisorID(string advisor) { advisorID = advisor; }
    
    string toString() const override {
        return Person::toString() + "|" + major + "|" + to_string(gpa) + "|" + 
               enrollmentStatus + "|" + academicStanding + "|" + to_string(creditsCompleted) + 
               "|" + advisorID;
    }
    
    void displayInfo() const override {
        Person::displayInfo();
        cout << "Major: " << major << endl;
        cout << "GPA: " << fixed << setprecision(2) << gpa << endl;
        cout << "Status: " << enrollmentStatus << endl;
        cout << "Academic Standing: " << academicStanding << endl;
        cout << "Credits Completed: " << creditsCompleted << endl;
    }
};

class UndergraduateStudent : public Student {
private:
    string expectedGraduationYear;
    
public:
    UndergraduateStudent() {}
    UndergraduateStudent(string id, string fname, string lname, string em, string phone,
                        string street, string ct, string st, string zip, string user, string pass,
                        string maj, double g, string status, string standing, int credits, 
                        string advisor, string gradYear)
        : Student(id, fname, lname, em, phone, street, ct, st, zip, user, pass, 
                 maj, g, status, standing, credits, advisor),
          expectedGraduationYear(gradYear) {
        role = "UndergraduateStudent";
    }
    
    string getExpectedGraduationYear() const { return expectedGraduationYear; }
};

class GraduateStudent : public Student {
private:
    string thesisTitle;
    string researchArea;
    string advisorName;
    
public:
    GraduateStudent() {}
    GraduateStudent(string id, string fname, string lname, string em, string phone,
                   string street, string ct, string st, string zip, string user, string pass,
                   string maj, double g, string status, string standing, int credits,
                   string advisor, string thesis, string research)
        : Student(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
                 maj, g, status, standing, credits, advisor),
          thesisTitle(thesis), researchArea(research) {
        role = "GraduateStudent";
    }
    
    string getThesisTitle() const { return thesisTitle; }
    string getResearchArea() const { return researchArea; }
};

class HonorsStudent : public Student {
private:
    string honorsProgram;
    double honorsGPARequirement;
    
public:
    HonorsStudent() : honorsGPARequirement(3.5) {}
    HonorsStudent(string id, string fname, string lname, string em, string phone,
                 string street, string ct, string st, string zip, string user, string pass,
                 string maj, double g, string status, string standing, int credits,
                 string advisor, string program)
        : Student(id, fname, lname, em, phone, street, ct, st, zip, user, pass,
                 maj, g, status, standing, credits, advisor),
          honorsProgram(program), honorsGPARequirement(3.5) {
        role = "HonorsStudent";
    }
    
    string getHonorsProgram() const { return honorsProgram; }
    bool meetsHonorsRequirement() const { return gpa >= honorsGPARequirement; }
};
