#pragma once
#include "person.h"
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
class Course {
private:
    string courseID;
    string courseName;
    int credits;
    string department;
    string schedule;
    string instructorID;
    int capacity;
    int enrolled;
    string semester;
    
public:
    Course() : credits(0), capacity(0), enrolled(0) {}
    Course(string id, string name, int cred, string dept, string sched, 
           string instructor, int cap, string sem)
        : courseID(id), courseName(name), credits(cred), department(dept),
          schedule(sched), instructorID(instructor), capacity(cap), enrolled(0), semester(sem) {}
    
    string getCourseID() const { return courseID; }
    string getCourseName() const { return courseName; }
    int getCredits() const { return credits; }
    string getDepartment() const { return department; }
    string getSchedule() const { return schedule; }
    string getInstructorID() const { return instructorID; }
    int getCapacity() const { return capacity; }
    int getEnrolled() const { return enrolled; }
    string getSemester() const { return semester; }
    
    bool isFull() const { return enrolled >= capacity; }
    void incrementEnrolled() { if(enrolled < capacity) enrolled++; }
    void decrementEnrolled() { if(enrolled > 0) enrolled--; }
    void setInstructorID(string id) { instructorID = id; }
    void setSchedule(string sched) { schedule = sched; }
    
    string toString() const {
        return courseID + "|" + courseName + "|" + to_string(credits) + "|" + 
               department + "|" + schedule + "|" + instructorID + "|" + 
               to_string(capacity) + "|" + to_string(enrolled) + "|" + semester;
    }
    
    void displayInfo() const {
        cout << "Course ID: " << courseID << endl;
        cout << "Name: " << courseName << endl;
        cout << "Credits: " << credits << endl;
        cout << "Department: " << department << endl;
        cout << "Schedule: " << schedule << endl;
        cout << "Instructor ID: " << instructorID << endl;
        cout << "Enrollment: " << enrolled << "/" << capacity << endl;
        cout << "Semester: " << semester << endl;
    }
};

class Department {
private:
    string departmentID;
    string departmentName;
    string departmentHead;
    string building;
    
public:
    Department() {}
    Department(string id, string name, string head, string bldg)
        : departmentID(id), departmentName(name), departmentHead(head), building(bldg) {}
    
    string getDepartmentID() const { return departmentID; }
    string getDepartmentName() const { return departmentName; }
    string getDepartmentHead() const { return departmentHead; }
    string getBuilding() const { return building; }
    
    string toString() const {
        return departmentID + "|" + departmentName + "|" + departmentHead + "|" + building;
    }
};

class Major {
private:
    string majorID;
    string majorName;
    string department;
    int requiredCredits;
    
public:
    Major() : requiredCredits(0) {}
    Major(string id, string name, string dept, int credits)
        : majorID(id), majorName(name), department(dept), requiredCredits(credits) {}
    
    string getMajorID() const { return majorID; }
    string getMajorName() const { return majorName; }
    string getDepartment() const { return department; }
    int getRequiredCredits() const { return requiredCredits; }
    
    string toString() const {
        return majorID + "|" + majorName + "|" + department + "|" + to_string(requiredCredits);
    }
};

class Enrollment {
private:
    string enrollmentID;
    string studentID;
    string courseID;
    string semester;
    string enrollmentDate;
    
public:
    Enrollment() {}
    Enrollment(string id, string studID, string crsID, string sem, string date)
        : enrollmentID(id), studentID(studID), courseID(crsID), semester(sem), enrollmentDate(date) {}
    
    string getEnrollmentID() const { return enrollmentID; }
    string getStudentID() const { return studentID; }
    string getCourseID() const { return courseID; }
    string getSemester() const { return semester; }
    
    string toString() const {
        return enrollmentID + "|" + studentID + "|" + courseID + "|" + semester + "|" + enrollmentDate;
    }
};

class Grade {
private:
    string gradeID;
    string studentID;
    string courseID;
    string letterGrade;
    double numericGrade;
    string semester;
    
public:
    Grade() : numericGrade(0.0) {}
    Grade(string id, string studID, string crsID, string letter, double numeric, string sem)
        : gradeID(id), studentID(studID), courseID(crsID), letterGrade(letter), 
          numericGrade(numeric), semester(sem) {}
    
    string getGradeID() const { return gradeID; }
    string getStudentID() const { return studentID; }
    string getCourseID() const { return courseID; }
    string getLetterGrade() const { return letterGrade; }
    double getNumericGrade() const { return numericGrade; }
    string getSemester() const { return semester; }
    
    void setLetterGrade(string grade) { letterGrade = grade; }
    void setNumericGrade(double grade) { numericGrade = grade; }
    
    string toString() const {
        return gradeID + "|" + studentID + "|" + courseID + "|" + letterGrade + "|" + 
               to_string(numericGrade) + "|" + semester;
    }
};

class Appointment {
private:
    string appointmentID;
    string studentID;
    string advisorID;
    string date;
    string time;
    string purpose;
    string status;
    
public:
    Appointment() {}
    Appointment(string id, string studID, string advID, string dt, string tm, string purp, string stat = "Scheduled")
        : appointmentID(id), studentID(studID), advisorID(advID), date(dt), 
          time(tm), purpose(purp), status(stat) {}
    
    string getAppointmentID() const { return appointmentID; }
    string getStudentID() const { return studentID; }
    string getAdvisorID() const { return advisorID; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getPurpose() const { return purpose; }
    string getStatus() const { return status; }
    
    void setStatus(string stat) { status = stat; }
    
    string toString() const {
        return appointmentID + "|" + studentID + "|" + advisorID + "|" + date + "|" + 
               time + "|" + purpose + "|" + status;
    }
    
    void displayInfo() const {
        cout << "Appointment ID: " << appointmentID << endl;
        cout << "Date: " << date << " at " << time << endl;
        cout << "Advisor ID: " << advisorID << endl;
        cout << "Purpose: " << purpose << endl;
        cout << "Status: " << status << endl;
    }
};
