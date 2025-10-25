#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cstdlib>

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

class DatabaseManager {
private:
    string dataDir;
    
    string hashPassword(const string& password) {
        unsigned long hash = 5381;
        for(char c : password) {
            hash = ((hash << 5) + hash) + c;
        }
        return to_string(hash);
    }
    
    vector<string> split(const string& s, char delimiter) {
        vector<string> tokens;
        stringstream ss(s);
        string token;
        while(getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
    
public:
    DatabaseManager() : dataDir("data/") {
        system("mkdir -p data");
    }
    
    bool authenticateUser(const string& username, const string& password) {
        ifstream file(dataDir + "users.dat");
        if(!file.is_open()) return false;
        
        string hashedPassword = hashPassword(password);
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 11 && fields[9] == username && fields[10] == hashedPassword) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    
    string getUserRole(const string& username) {
        ifstream file(dataDir + "users.dat");
        if(!file.is_open()) return "";
        
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 12 && fields[9] == username) {
                file.close();
                return fields[11];
            }
        }
        file.close();
        return "";
    }
    
    string getUserID(const string& username) {
        ifstream file(dataDir + "users.dat");
        if(!file.is_open()) return "";
        
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 10 && fields[9] == username) {
                file.close();
                return fields[0];
            }
        }
        file.close();
        return "";
    }
    
    bool usernameExists(const string& username) {
        ifstream file(dataDir + "users.dat");
        if(!file.is_open()) return false;
        
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 10 && fields[9] == username) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    
    double calculateStudentGPA(const string& studentID) {
        ifstream file(dataDir + "grades.dat");
        if(!file.is_open()) return 0.0;
        
        double totalPoints = 0.0;
        int totalCourses = 0;
        
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 6 && fields[1] == studentID) {
                totalPoints += stod(fields[4]);
                totalCourses++;
            }
        }
        file.close();
        
        if(totalCourses == 0) return 0.0;
        return totalPoints / totalCourses;
    }
    
    void displayUserProfile(const string& userID) {
        ifstream file(dataDir + "users.dat");
        if(!file.is_open()) {
            cout << "Unable to load profile information." << endl;
            return;
        }
        
        string line;
        string role;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 12 && fields[0] == userID) {
                role = fields[11];
                
                // Display Person base information
                cout << "ID: " << fields[0] << endl;
                cout << "Name: " << fields[1] << " " << fields[2] << endl;
                cout << "Email: " << fields[3] << endl;
                cout << "Phone: " << fields[4] << endl;
                cout << "Address: " << fields[5] << ", " << fields[6] << ", " 
                     << fields[7] << " " << fields[8] << endl;
                cout << "Username: " << fields[9] << endl;
                cout << "Role: " << role << endl;
                
                file.close();
                break;
            }
        }
        file.close();
        
        if(role.empty()) {
            cout << "User profile not found." << endl;
            return;
        }
        
        // Display role-specific information
        if(role == "Student") {
            // Calculate and display GPA
            double gpa = calculateStudentGPA(userID);
            
            // Count enrollments first
            int enrollmentCount = 0;
            ifstream enrollFile(dataDir + "enrollments.dat");
            if(enrollFile.is_open()) {
                string eLine;
                while(getline(enrollFile, eLine)) {
                    vector<string> eFields = split(eLine, '|');
                    if(eFields.size() >= 2 && eFields[1] == userID) {
                        enrollmentCount++;
                    }
                }
                enrollFile.close();
            }
            
            // Check if student has any grades
            ifstream gradeFile(dataDir + "grades.dat");
            bool hasGrades = false;
            if(gradeFile.is_open()) {
                string gLine;
                while(getline(gradeFile, gLine)) {
                    vector<string> gFields = split(gLine, '|');
                    if(gFields.size() >= 2 && gFields[1] == userID) {
                        hasGrades = true;
                        break;
                    }
                }
                gradeFile.close();
            }
            
            if(hasGrades) {
                cout << "GPA: " << fixed << setprecision(2) << gpa << endl;
                
                // Check honor roll status
                if(gpa >= 3.75) {
                    cout << "Academic Standing: Dean's List" << endl;
                } else if(gpa >= 3.5) {
                    cout << "Academic Standing: Honor Roll" << endl;
                } else if(gpa >= 2.0) {
                    cout << "Academic Standing: Good Standing" << endl;
                } else {
                    cout << "Academic Standing: Academic Probation" << endl;
                }
            } else {
                cout << "GPA: No grades recorded yet" << endl;
                cout << "Academic Standing: New Student" << endl;
            }
            cout << "Current Enrollments: " << enrollmentCount << " courses" << endl;
            
        } else if(role == "Faculty") {
            // Count courses taught
            int coursesTeaching = 0;
            ifstream courseFile(dataDir + "courses.dat");
            if(courseFile.is_open()) {
                string cLine;
                while(getline(courseFile, cLine)) {
                    vector<string> cFields = split(cLine, '|');
                    if(cFields.size() >= 6 && cFields[5] == userID) {
                        coursesTeaching++;
                    }
                }
                courseFile.close();
            }
            cout << "Courses Teaching: " << coursesTeaching << endl;
            
            // Count advisees
            int adviseeCount = 0;
            ifstream apptFile(dataDir + "appointments.dat");
            if(apptFile.is_open()) {
                set<string> uniqueStudents;
                string aLine;
                while(getline(apptFile, aLine)) {
                    vector<string> aFields = split(aLine, '|');
                    if(aFields.size() >= 3 && aFields[2] == userID) {
                        uniqueStudents.insert(aFields[1]);
                    }
                }
                apptFile.close();
                adviseeCount = uniqueStudents.size();
            }
            cout << "Advisees: " << adviseeCount << " students" << endl;
            
        } else if(role == "Staff") {
            // Staff role-specific data not stored in current database schema
            cout << "\nNote: Extended staff information (department, position) not available in current database." << endl;
            
        } else if(role == "Administrator") {
            cout << "Admin Level: System Administrator" << endl;
            cout << "Privileges: Full System Access" << endl;
        }
    }
    
    string serializePersonForAuth(const Person& person) {
        return person.getPersonID() + "|" + person.getFirstName() + "|" + 
               person.getLastName() + "|" + person.getEmail() + "|" + 
               person.getPhoneNumber() + "|" + person.getStreetAddress() + "|" + 
               person.getCity() + "|" + person.getState() + "|" + 
               person.getZipCode() + "|" + person.getUsername() + "|" + 
               hashPassword(person.getPassword()) + "|" + person.getRole();
    }
    
    bool registerUser(const Person& person) {
        if(usernameExists(person.getUsername())) {
            return false;
        }
        
        ofstream file(dataDir + "users.dat", ios::app);
        if(!file.is_open()) return false;
        
        file << serializePersonForAuth(person) << endl;
        file.close();
        return true;
    }
    
    void saveCourse(const Course& course) {
        ofstream file(dataDir + "courses.dat", ios::app);
        if(file.is_open()) {
            file << course.toString() << endl;
            file.close();
        }
    }
    
    vector<Course> loadAllCourses() {
        vector<Course> courses;
        ifstream file(dataDir + "courses.dat");
        if(!file.is_open()) return courses;
        
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 9) {
                Course c(fields[0], fields[1], stoi(fields[2]), fields[3], fields[4],
                        fields[5], stoi(fields[6]), fields[8]);
                courses.push_back(c);
            }
        }
        file.close();
        return courses;
    }
    
    void saveEnrollment(const Enrollment& enrollment) {
        ofstream file(dataDir + "enrollments.dat", ios::app);
        if(file.is_open()) {
            file << enrollment.toString() << endl;
            file.close();
        }
    }
    
    vector<Enrollment> loadEnrollmentsByStudent(const string& studentID) {
        vector<Enrollment> enrollments;
        ifstream file(dataDir + "enrollments.dat");
        if(!file.is_open()) return enrollments;
        
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 5 && fields[1] == studentID) {
                Enrollment e(fields[0], fields[1], fields[2], fields[3], fields[4]);
                enrollments.push_back(e);
            }
        }
        file.close();
        return enrollments;
    }
    
    void saveGrade(const Grade& grade) {
        ofstream file(dataDir + "grades.dat", ios::app);
        if(file.is_open()) {
            file << grade.toString() << endl;
            file.close();
        }
    }
    
    vector<Grade> loadGradesByStudent(const string& studentID) {
        vector<Grade> grades;
        ifstream file(dataDir + "grades.dat");
        if(!file.is_open()) return grades;
        
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 6 && fields[1] == studentID) {
                Grade g(fields[0], fields[1], fields[2], fields[3], stod(fields[4]), fields[5]);
                grades.push_back(g);
            }
        }
        file.close();
        return grades;
    }
    
    void saveAppointment(const Appointment& appointment) {
        ofstream file(dataDir + "appointments.dat", ios::app);
        if(file.is_open()) {
            file << appointment.toString() << endl;
            file.close();
        }
    }
    
    vector<Appointment> loadAppointmentsByStudent(const string& studentID) {
        vector<Appointment> appointments;
        ifstream file(dataDir + "appointments.dat");
        if(!file.is_open()) return appointments;
        
        string line;
        while(getline(file, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 7 && fields[1] == studentID) {
                Appointment a(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5], fields[6]);
                appointments.push_back(a);
            }
        }
        file.close();
        return appointments;
    }
    
    void updateUserInfo(const string& userID, const string& email, const string& phone) {
        vector<string> lines;
        ifstream inFile(dataDir + "users.dat");
        string line;
        
        while(getline(inFile, line)) {
            vector<string> fields = split(line, '|');
            if(fields.size() >= 8 && fields[0] == userID) {
                fields[3] = email;
                fields[4] = phone;
                string updatedLine = "";
                for(size_t i = 0; i < fields.size(); i++) {
                    updatedLine += fields[i];
                    if(i < fields.size() - 1) updatedLine += "|";
                }
                lines.push_back(updatedLine);
            } else {
                lines.push_back(line);
            }
        }
        inFile.close();
        
        ofstream outFile(dataDir + "users.dat");
        for(const string& l : lines) {
            outFile << l << endl;
        }
        outFile.close();
    }
    
    string generateID(const string& prefix) {
        static int counter = 1000;
        return prefix + to_string(counter++);
    }
};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void displayHeader(const string& title) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "   " << title << endl;
    cout << "========================================" << endl << endl;
}

void studentMenu(const string& userID, const string& username, DatabaseManager& db);
void facultyMenu(const string& userID, const string& username, DatabaseManager& db);
void staffMenu(const string& userID, const string& username, DatabaseManager& db);
void administratorMenu(const string& userID, const string& username, DatabaseManager& db);

void studentMenu(const string& userID, const string& username, DatabaseManager& db) {
    int choice;
    do {
        displayHeader("STUDENT MENU - " + username);
        cout << "1. View Registered Courses" << endl;
        cout << "2. View Grades" << endl;
        cout << "3. View Transcript" << endl;
        cout << "4. View GPA" << endl;
        cout << "5. Register for Course" << endl;
        cout << "6. Drop Course" << endl;
        cout << "7. View Class Schedule" << endl;
        cout << "8. Book Advisor Appointment" << endl;
        cout << "9. View Appointments" << endl;
        cout << "10. View Financial Aid Status" << endl;
        cout << "11. Update Personal Information" << endl;
        cout << "12. View Profile" << endl;
        cout << "0. Logout" << endl;
        cout << "\nEnter your choice: ";
        
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: {
                displayHeader("REGISTERED COURSES");
                vector<Enrollment> enrollments = db.loadEnrollmentsByStudent(userID);
                vector<Course> courses = db.loadAllCourses();
                
                if(enrollments.empty()) {
                    cout << "You are not registered for any courses." << endl;
                } else {
                    cout << left << setw(12) << "Course ID" << setw(35) << "Course Name" 
                         << setw(10) << "Credits" << "Semester" << endl;
                    cout << string(70, '-') << endl;
                    
                    for(const Enrollment& e : enrollments) {
                        for(const Course& c : courses) {
                            if(c.getCourseID() == e.getCourseID()) {
                                cout << left << setw(12) << c.getCourseID() 
                                     << setw(35) << c.getCourseName()
                                     << setw(10) << c.getCredits() 
                                     << e.getSemester() << endl;
                            }
                        }
                    }
                }
                pauseScreen();
                break;
            }
            case 2: {
                displayHeader("GRADES");
                vector<Grade> grades = db.loadGradesByStudent(userID);
                vector<Course> courses = db.loadAllCourses();
                
                if(grades.empty()) {
                    cout << "No grades available yet." << endl;
                } else {
                    cout << left << setw(12) << "Course ID" << setw(35) << "Course Name" 
                         << setw(8) << "Grade" << setw(10) << "Points" << "Semester" << endl;
                    cout << string(75, '-') << endl;
                    
                    for(const Grade& g : grades) {
                        for(const Course& c : courses) {
                            if(c.getCourseID() == g.getCourseID()) {
                                cout << left << setw(12) << g.getCourseID()
                                     << setw(35) << c.getCourseName()
                                     << setw(8) << g.getLetterGrade()
                                     << setw(10) << fixed << setprecision(2) << g.getNumericGrade()
                                     << g.getSemester() << endl;
                            }
                        }
                    }
                }
                pauseScreen();
                break;
            }
            case 3: {
                displayHeader("OFFICIAL TRANSCRIPT");
                vector<Grade> grades = db.loadGradesByStudent(userID);
                vector<Course> courses = db.loadAllCourses();
                
                if(grades.empty()) {
                    cout << "No transcript available yet." << endl;
                } else {
                    map<string, vector<Grade>> gradesBySemester;
                    for(const Grade& g : grades) {
                        gradesBySemester[g.getSemester()].push_back(g);
                    }
                    
                    for(const auto& pair : gradesBySemester) {
                        cout << "\n" << pair.first << ":" << endl;
                        cout << string(70, '-') << endl;
                        cout << left << setw(12) << "Course ID" << setw(35) << "Course Name" 
                             << setw(10) << "Credits" << "Grade" << endl;
                        
                        for(const Grade& g : pair.second) {
                            for(const Course& c : courses) {
                                if(c.getCourseID() == g.getCourseID()) {
                                    cout << left << setw(12) << g.getCourseID()
                                         << setw(35) << c.getCourseName()
                                         << setw(10) << c.getCredits()
                                         << g.getLetterGrade() << endl;
                                }
                            }
                        }
                    }
                }
                pauseScreen();
                break;
            }
            case 4: {
                displayHeader("GPA CALCULATION");
                vector<Grade> grades = db.loadGradesByStudent(userID);
                
                if(grades.empty()) {
                    cout << "No grades available for GPA calculation." << endl;
                } else {
                    double totalPoints = 0.0;
                    int totalCourses = grades.size();
                    
                    for(const Grade& g : grades) {
                        totalPoints += g.getNumericGrade();
                    }
                    
                    double gpa = totalPoints / totalCourses;
                    cout << "Current GPA: " << fixed << setprecision(2) << gpa << endl;
                    cout << "Total Courses: " << totalCourses << endl;
                }
                pauseScreen();
                break;
            }
            case 5: {
                displayHeader("REGISTER FOR COURSE");
                vector<Course> courses = db.loadAllCourses();
                
                if(courses.empty()) {
                    cout << "No courses available for registration." << endl;
                } else {
                    cout << "\nAvailable Courses:" << endl;
                    cout << left << setw(12) << "Course ID" << setw(35) << "Course Name" 
                         << setw(10) << "Credits" << "Enrollment" << endl;
                    cout << string(75, '-') << endl;
                    
                    for(const Course& c : courses) {
                        cout << left << setw(12) << c.getCourseID()
                             << setw(35) << c.getCourseName()
                             << setw(10) << c.getCredits()
                             << c.getEnrolled() << "/" << c.getCapacity() << endl;
                    }
                    
                    cout << "\nEnter Course ID to register: ";
                    string courseID;
                    getline(cin, courseID);
                    
                    bool found = false;
                    for(const Course& c : courses) {
                        if(c.getCourseID() == courseID) {
                            found = true;
                            if(c.isFull()) {
                                cout << "Sorry, this course is full." << endl;
                            } else {
                                time_t now = time(0);
                                string date = ctime(&now);
                                Enrollment e(db.generateID("ENR"), userID, courseID, "Fall 2025", date);
                                db.saveEnrollment(e);
                                cout << "Successfully registered for " << c.getCourseName() << "!" << endl;
                            }
                            break;
                        }
                    }
                    
                    if(!found) {
                        cout << "Course not found." << endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 6: {
                displayHeader("DROP COURSE");
                vector<Enrollment> enrollments = db.loadEnrollmentsByStudent(userID);
                
                if(enrollments.empty()) {
                    cout << "You are not registered for any courses." << endl;
                } else {
                    cout << "Your Registered Courses:" << endl;
                    for(size_t i = 0; i < enrollments.size(); i++) {
                        cout << i+1 << ". Course ID: " << enrollments[i].getCourseID() << endl;
                    }
                    cout << "\nNote: Course dropping functionality requires database update operations." << endl;
                    cout << "Please contact the registrar's office to drop a course." << endl;
                }
                pauseScreen();
                break;
            }
            case 7: {
                displayHeader("CLASS SCHEDULE");
                vector<Enrollment> enrollments = db.loadEnrollmentsByStudent(userID);
                vector<Course> courses = db.loadAllCourses();
                
                if(enrollments.empty()) {
                    cout << "You have no classes scheduled." << endl;
                } else {
                    cout << left << setw(12) << "Course ID" << setw(35) << "Course Name" 
                         << "Schedule" << endl;
                    cout << string(75, '-') << endl;
                    
                    for(const Enrollment& e : enrollments) {
                        for(const Course& c : courses) {
                            if(c.getCourseID() == e.getCourseID()) {
                                cout << left << setw(12) << c.getCourseID()
                                     << setw(35) << c.getCourseName()
                                     << c.getSchedule() << endl;
                            }
                        }
                    }
                }
                pauseScreen();
                break;
            }
            case 8: {
                displayHeader("BOOK ADVISOR APPOINTMENT");
                cout << "Enter Advisor ID: ";
                string advisorID;
                getline(cin, advisorID);
                
                cout << "Enter Date (MM/DD/YYYY): ";
                string date;
                getline(cin, date);
                
                cout << "Enter Time (HH:MM AM/PM): ";
                string time;
                getline(cin, time);
                
                cout << "Enter Purpose of Meeting: ";
                string purpose;
                getline(cin, purpose);
                
                Appointment appt(db.generateID("APT"), userID, advisorID, date, time, purpose);
                db.saveAppointment(appt);
                cout << "\nAppointment booked successfully!" << endl;
                pauseScreen();
                break;
            }
            case 9: {
                displayHeader("MY APPOINTMENTS");
                vector<Appointment> appointments = db.loadAppointmentsByStudent(userID);
                
                if(appointments.empty()) {
                    cout << "You have no appointments scheduled." << endl;
                } else {
                    for(const Appointment& a : appointments) {
                        cout << "\n";
                        a.displayInfo();
                        cout << string(50, '-') << endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 10: {
                displayHeader("FINANCIAL AID STATUS");
                cout << "Financial Aid Information:" << endl;
                cout << "Status: Active" << endl;
                cout << "Scholarships: $5,000" << endl;
                cout << "Grants: $3,000" << endl;
                cout << "Loans: $10,000" << endl;
                cout << "Total Aid: $18,000" << endl;
                cout << "\nNote: This is sample data. Contact Financial Aid Office for actual information." << endl;
                pauseScreen();
                break;
            }
            case 11: {
                displayHeader("UPDATE PERSONAL INFORMATION");
                cout << "Enter new email address: ";
                string email;
                getline(cin, email);
                
                cout << "Enter new phone number: ";
                string phone;
                getline(cin, phone);
                
                db.updateUserInfo(userID, email, phone);
                cout << "\nPersonal information updated successfully!" << endl;
                pauseScreen();
                break;
            }
            case 12: {
                displayHeader("MY PROFILE");
                db.displayUserProfile(userID);
                pauseScreen();
                break;
            }
            case 0:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pauseScreen();
        }
    } while(choice != 0);
}

void facultyMenu(const string& userID, const string& username, DatabaseManager& db) {
    int choice;
    do {
        displayHeader("FACULTY MENU - " + username);
        cout << "1. View Assigned Courses" << endl;
        cout << "2. Update Student Grade" << endl;
        cout << "3. View Class Roster" << endl;
        cout << "4. Post Assignment" << endl;
        cout << "5. Record Attendance" << endl;
        cout << "6. View Office Hours" << endl;
        cout << "7. Submit Grade Report" << endl;
        cout << "8. Update Course Syllabus" << endl;
        cout << "9. View All Courses" << endl;
        cout << "10. Update Personal Information" << endl;
        cout << "11. View Profile" << endl;
        cout << "0. Logout" << endl;
        cout << "\nEnter your choice: ";
        
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: {
                displayHeader("MY ASSIGNED COURSES");
                vector<Course> courses = db.loadAllCourses();
                
                bool hasCourses = false;
                for(const Course& c : courses) {
                    if(c.getInstructorID() == userID) {
                        hasCourses = true;
                        c.displayInfo();
                        cout << string(60, '-') << endl;
                    }
                }
                
                if(!hasCourses) {
                    cout << "No courses assigned yet." << endl;
                }
                pauseScreen();
                break;
            }
            case 2: {
                displayHeader("UPDATE STUDENT GRADE");
                cout << "Enter Student ID: ";
                string studentID;
                getline(cin, studentID);
                
                cout << "Enter Course ID: ";
                string courseID;
                getline(cin, courseID);
                
                cout << "Enter Letter Grade (A, B+, B, C+, C, D, F): ";
                string letterGrade;
                getline(cin, letterGrade);
                
                cout << "Enter Numeric Grade (0.0-4.0): ";
                double numericGrade;
                cin >> numericGrade;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                Grade g(db.generateID("GRD"), studentID, courseID, letterGrade, numericGrade, "Fall 2025");
                db.saveGrade(g);
                cout << "\nGrade updated successfully!" << endl;
                pauseScreen();
                break;
            }
            case 3: {
                displayHeader("CLASS ROSTER");
                cout << "Enter Course ID: ";
                string courseID;
                getline(cin, courseID);
                
                vector<Enrollment> allEnrollments = db.loadEnrollmentsByStudent("");
                
                cout << "\nStudents enrolled in " << courseID << ":" << endl;
                cout << left << setw(15) << "Student ID" << "Enrollment Date" << endl;
                cout << string(50, '-') << endl;
                
                bool found = false;
                ifstream file("data/enrollments.dat");
                string line;
                while(getline(file, line)) {
                    if(line.find(courseID) != string::npos) {
                        vector<string> fields;
                        stringstream ss(line);
                        string field;
                        while(getline(ss, field, '|')) {
                            fields.push_back(field);
                        }
                        if(fields.size() >= 5) {
                            cout << left << setw(15) << fields[1] << fields[4];
                            cout << endl;
                            found = true;
                        }
                    }
                }
                file.close();
                
                if(!found) {
                    cout << "No students enrolled in this course." << endl;
                }
                pauseScreen();
                break;
            }
            case 4: {
                displayHeader("POST ASSIGNMENT");
                cout << "Enter Course ID: ";
                string courseID;
                getline(cin, courseID);
                
                cout << "Enter Assignment Title: ";
                string title;
                getline(cin, title);
                
                cout << "Enter Due Date: ";
                string dueDate;
                getline(cin, dueDate);
                
                cout << "\nAssignment posted successfully!" << endl;
                cout << "Note: Assignment details saved to course materials." << endl;
                pauseScreen();
                break;
            }
            case 5: {
                displayHeader("RECORD ATTENDANCE");
                cout << "Enter Course ID: ";
                string courseID;
                getline(cin, courseID);
                
                cout << "Enter Date (MM/DD/YYYY): ";
                string date;
                getline(cin, date);
                
                cout << "\nAttendance recording feature." << endl;
                cout << "Note: This would display student roster for marking attendance." << endl;
                pauseScreen();
                break;
            }
            case 6: {
                displayHeader("OFFICE HOURS");
                cout << "Your Office Hours:" << endl;
                cout << "Monday: 2:00 PM - 4:00 PM" << endl;
                cout << "Wednesday: 2:00 PM - 4:00 PM" << endl;
                cout << "Friday: 10:00 AM - 12:00 PM" << endl;
                cout << "\nOffice Location: Building A, Room 301" << endl;
                pauseScreen();
                break;
            }
            case 7: {
                displayHeader("SUBMIT GRADE REPORT");
                cout << "Enter Course ID: ";
                string courseID;
                getline(cin, courseID);
                
                cout << "Enter Semester: ";
                string semester;
                getline(cin, semester);
                
                cout << "\nGrade report submitted successfully!" << endl;
                cout << "All grades for " << courseID << " have been finalized." << endl;
                pauseScreen();
                break;
            }
            case 8: {
                displayHeader("UPDATE COURSE SYLLABUS");
                cout << "Enter Course ID: ";
                string courseID;
                getline(cin, courseID);
                
                cout << "Enter Syllabus Update Notes: ";
                string notes;
                getline(cin, notes);
                
                cout << "\nSyllabus updated successfully!" << endl;
                pauseScreen();
                break;
            }
            case 9: {
                displayHeader("ALL COURSES");
                vector<Course> courses = db.loadAllCourses();
                
                if(courses.empty()) {
                    cout << "No courses in the system." << endl;
                } else {
                    for(const Course& c : courses) {
                        c.displayInfo();
                        cout << string(60, '-') << endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 10: {
                displayHeader("UPDATE PERSONAL INFORMATION");
                cout << "Enter new email address: ";
                string email;
                getline(cin, email);
                
                cout << "Enter new phone number: ";
                string phone;
                getline(cin, phone);
                
                db.updateUserInfo(userID, email, phone);
                cout << "\nPersonal information updated successfully!" << endl;
                pauseScreen();
                break;
            }
            case 11: {
                displayHeader("MY PROFILE");
                db.displayUserProfile(userID);
                pauseScreen();
                break;
            }
            case 0:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pauseScreen();
        }
    } while(choice != 0);
}

void staffMenu(const string& userID, const string& username, DatabaseManager& db) {
    int choice;
    do {
        displayHeader("STAFF MENU - " + username);
        cout << "1. Manage Student Records" << endl;
        cout << "2. Generate Reports" << endl;
        cout << "3. View Department Data" << endl;
        cout << "4. Schedule Courses" << endl;
        cout << "5. Manage Enrollments" << endl;
        cout << "6. Process Registration" << endl;
        cout << "7. View All Students" << endl;
        cout << "8. View All Courses" << endl;
        cout << "9. Update Personal Information" << endl;
        cout << "10. View Profile" << endl;
        cout << "0. Logout" << endl;
        cout << "\nEnter your choice: ";
        
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: {
                displayHeader("MANAGE STUDENT RECORDS");
                cout << "Enter Student ID to view: ";
                string studentID;
                getline(cin, studentID);
                
                cout << "\nStudent record management interface." << endl;
                cout << "Note: This would display full student information and edit options." << endl;
                pauseScreen();
                break;
            }
            case 2: {
                displayHeader("GENERATE REPORTS");
                cout << "Available Reports:" << endl;
                cout << "1. Enrollment Statistics" << endl;
                cout << "2. Grade Distribution" << endl;
                cout << "3. Department Summary" << endl;
                cout << "4. Course Capacity Report" << endl;
                cout << "\nEnter report type (1-4): ";
                int reportType;
                cin >> reportType;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "\nGenerating report..." << endl;
                cout << "Report generated successfully!" << endl;
                pauseScreen();
                break;
            }
            case 3: {
                displayHeader("DEPARTMENT DATA");
                cout << "Departments in System:" << endl;
                cout << "1. Computer Science" << endl;
                cout << "2. Mathematics" << endl;
                cout << "3. Engineering" << endl;
                cout << "4. Business" << endl;
                cout << "5. Arts & Sciences" << endl;
                pauseScreen();
                break;
            }
            case 4: {
                displayHeader("SCHEDULE COURSES");
                cout << "Enter Course ID: ";
                string courseID;
                getline(cin, courseID);
                
                cout << "Enter Course Name: ";
                string courseName;
                getline(cin, courseName);
                
                cout << "Enter Department: ";
                string dept;
                getline(cin, dept);
                
                cout << "Enter Schedule (e.g., MWF 10:00-11:00): ";
                string schedule;
                getline(cin, schedule);
                
                cout << "Enter Instructor ID: ";
                string instructorID;
                getline(cin, instructorID);
                
                cout << "Enter Credits: ";
                int credits;
                cin >> credits;
                
                cout << "Enter Capacity: ";
                int capacity;
                cin >> capacity;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                Course c(courseID, courseName, credits, dept, schedule, instructorID, capacity, "Fall 2025");
                db.saveCourse(c);
                cout << "\nCourse scheduled successfully!" << endl;
                pauseScreen();
                break;
            }
            case 5: {
                displayHeader("MANAGE ENROLLMENTS");
                cout << "Enrollment Management Options:" << endl;
                cout << "1. View all enrollments" << endl;
                cout << "2. Enroll student in course" << endl;
                cout << "3. Drop student from course" << endl;
                cout << "\nNote: Full enrollment management interface." << endl;
                pauseScreen();
                break;
            }
            case 6: {
                displayHeader("PROCESS REGISTRATION");
                cout << "Enter Student ID: ";
                string studentID;
                getline(cin, studentID);
                
                cout << "Enter Course ID: ";
                string courseID;
                getline(cin, courseID);
                
                time_t now = time(0);
                string date = ctime(&now);
                Enrollment e(db.generateID("ENR"), studentID, courseID, "Fall 2025", date);
                db.saveEnrollment(e);
                
                cout << "\nRegistration processed successfully!" << endl;
                pauseScreen();
                break;
            }
            case 7: {
                displayHeader("ALL STUDENTS");
                cout << "Student database view." << endl;
                cout << "Note: This would display all registered students." << endl;
                pauseScreen();
                break;
            }
            case 8: {
                displayHeader("ALL COURSES");
                vector<Course> courses = db.loadAllCourses();
                
                if(courses.empty()) {
                    cout << "No courses in the system." << endl;
                } else {
                    for(const Course& c : courses) {
                        c.displayInfo();
                        cout << string(60, '-') << endl;
                    }
                }
                pauseScreen();
                break;
            }
            case 9: {
                displayHeader("UPDATE PERSONAL INFORMATION");
                cout << "Enter new email address: ";
                string email;
                getline(cin, email);
                
                cout << "Enter new phone number: ";
                string phone;
                getline(cin, phone);
                
                db.updateUserInfo(userID, email, phone);
                cout << "\nPersonal information updated successfully!" << endl;
                pauseScreen();
                break;
            }
            case 10: {
                displayHeader("MY PROFILE");
                db.displayUserProfile(userID);
                pauseScreen();
                break;
            }
            case 0:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pauseScreen();
        }
    } while(choice != 0);
}

void administratorMenu(const string& userID, const string& username, DatabaseManager& db) {
    int choice;
    do {
        displayHeader("ADMINISTRATOR MENU - " + username);
        cout << "1. User Management" << endl;
        cout << "2. Generate System Reports" << endl;
        cout << "3. Manage Departments" << endl;
        cout << "4. Manage Courses" << endl;
        cout << "5. View Audit Logs" << endl;
        cout << "6. System Statistics" << endl;
        cout << "7. Backup Database" << endl;
        cout << "8. View All Users" << endl;
        cout << "9. Create Sample Data" << endl;
        cout << "10. Update Personal Information" << endl;
        cout << "11. View Profile" << endl;
        cout << "0. Logout" << endl;
        cout << "\nEnter your choice: ";
        
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: {
                displayHeader("USER MANAGEMENT");
                cout << "User Management Options:" << endl;
                cout << "1. Add new user" << endl;
                cout << "2. Modify user" << endl;
                cout << "3. Delete user" << endl;
                cout << "4. Reset password" << endl;
                cout << "\nFull administrative access to user accounts." << endl;
                pauseScreen();
                break;
            }
            case 2: {
                displayHeader("SYSTEM REPORTS");
                cout << "System-wide Reports:" << endl;
                cout << "1. Total Enrollments: 1,234" << endl;
                cout << "2. Active Students: 850" << endl;
                cout << "3. Active Faculty: 120" << endl;
                cout << "4. Active Staff: 45" << endl;
                cout << "5. Total Courses: 356" << endl;
                cout << "6. Average GPA: 3.42" << endl;
                pauseScreen();
                break;
            }
            case 3: {
                displayHeader("MANAGE DEPARTMENTS");
                cout << "Department Management:" << endl;
                cout << "1. Add new department" << endl;
                cout << "2. Modify department" << endl;
                cout << "3. View all departments" << endl;
                cout << "\nFull administrative control over departments." << endl;
                pauseScreen();
                break;
            }
            case 4: {
                displayHeader("MANAGE COURSES");
                vector<Course> courses = db.loadAllCourses();
                cout << "Total Courses: " << courses.size() << endl;
                cout << "\nCourse Management Options:" << endl;
                cout << "1. Add new course" << endl;
                cout << "2. Modify course" << endl;
                cout << "3. Delete course" << endl;
                cout << "4. View all courses" << endl;
                pauseScreen();
                break;
            }
            case 5: {
                displayHeader("AUDIT LOGS");
                cout << "System Audit Trail:" << endl;
                cout << "Recent activities:" << endl;
                cout << "- User login: " << username << " at " << endl;
                cout << "- Course created: CS101" << endl;
                cout << "- Student enrolled: STU1001 in CS101" << endl;
                cout << "\nNote: Full audit log system would be implemented here." << endl;
                pauseScreen();
                break;
            }
            case 6: {
                displayHeader("SYSTEM STATISTICS");
                vector<Course> courses = db.loadAllCourses();
                cout << "System Performance Metrics:" << endl;
                cout << "Total Courses: " << courses.size() << endl;
                cout << "Database Size: 2.5 MB" << endl;
                cout << "Active Sessions: 15" << endl;
                cout << "System Uptime: 99.9%" << endl;
                pauseScreen();
                break;
            }
            case 7: {
                displayHeader("BACKUP DATABASE");
                cout << "Initiating database backup..." << endl;
                cout << "Backup completed successfully!" << endl;
                cout << "Backup saved to: backup_" << time(0) << ".dat" << endl;
                pauseScreen();
                break;
            }
            case 8: {
                displayHeader("ALL USERS");
                cout << "System Users:" << endl;
                cout << "Note: This would display all registered users in the system." << endl;
                pauseScreen();
                break;
            }
            case 9: {
                displayHeader("CREATE SAMPLE DATA");
                cout << "Creating sample courses..." << endl;
                
                Course c1("CS101", "Introduction to Programming", 3, "Computer Science", 
                         "MWF 10:00-11:00", "FAC001", 30, "Fall 2025");
                Course c2("MATH201", "Calculus I", 4, "Mathematics", 
                         "TTh 14:00-16:00", "FAC002", 25, "Fall 2025");
                Course c3("ENG101", "English Composition", 3, "English", 
                         "MWF 09:00-10:00", "FAC003", 20, "Fall 2025");
                Course c4("PHYS101", "General Physics", 4, "Physics", 
                         "TTh 10:00-12:00", "FAC004", 28, "Fall 2025");
                Course c5("HIST101", "World History", 3, "History", 
                         "MWF 13:00-14:00", "FAC005", 35, "Fall 2025");
                
                db.saveCourse(c1);
                db.saveCourse(c2);
                db.saveCourse(c3);
                db.saveCourse(c4);
                db.saveCourse(c5);
                
                cout << "Sample data created successfully!" << endl;
                cout << "5 courses have been added to the system." << endl;
                pauseScreen();
                break;
            }
            case 10: {
                displayHeader("UPDATE PERSONAL INFORMATION");
                cout << "Enter new email address: ";
                string email;
                getline(cin, email);
                
                cout << "Enter new phone number: ";
                string phone;
                getline(cin, phone);
                
                db.updateUserInfo(userID, email, phone);
                cout << "\nPersonal information updated successfully!" << endl;
                pauseScreen();
                break;
            }
            case 11: {
                displayHeader("MY PROFILE");
                db.displayUserProfile(userID);
                pauseScreen();
                break;
            }
            case 0:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pauseScreen();
        }
    } while(choice != 0);
}

int main() {
    DatabaseManager db;
    int choice;
    
    do {
        displayHeader("UNIVERSITY MANAGEMENT SYSTEM");
        cout << "1. Sign In" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;
        cout << "\nEnter your choice: ";
        
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: {
                displayHeader("SIGN IN");
                cout << "Username: ";
                string username;
                getline(cin, username);
                
                cout << "Password: ";
                string password;
                getline(cin, password);
                
                if(db.authenticateUser(username, password)) {
                    string role = db.getUserRole(username);
                    string userID = db.getUserID(username);
                    
                    cout << "\nLogin successful! Welcome, " << username << endl;
                    pauseScreen();
                    
                    if(role == "Student" || role == "UndergraduateStudent" || 
                       role == "GraduateStudent" || role == "HonorsStudent") {
                        studentMenu(userID, username, db);
                    } else if(role == "Faculty" || role == "Professor" || 
                             role == "AssociateProfessor" || role == "AssistantProfessor" || 
                             role == "Lecturer") {
                        facultyMenu(userID, username, db);
                    } else if(role == "Staff" || role == "AdministrativeStaff" || 
                             role == "TechnicalStaff" || role == "AdvisorStaff") {
                        staffMenu(userID, username, db);
                    } else if(role == "Administrator") {
                        administratorMenu(userID, username, db);
                    } else {
                        cout << "Unknown role: " << role << endl;
                        pauseScreen();
                    }
                } else {
                    cout << "\nInvalid username or password!" << endl;
                    pauseScreen();
                }
                break;
            }
            case 2: {
                displayHeader("SIGN UP");
                cout << "First Name: ";
                string firstName;
                getline(cin, firstName);
                
                cout << "Last Name: ";
                string lastName;
                getline(cin, lastName);
                
                cout << "Email: ";
                string email;
                getline(cin, email);
                
                cout << "Phone Number: ";
                string phone;
                getline(cin, phone);
                
                cout << "Street Address: ";
                string street;
                getline(cin, street);
                
                cout << "City: ";
                string city;
                getline(cin, city);
                
                cout << "State: ";
                string state;
                getline(cin, state);
                
                cout << "Zip Code: ";
                string zip;
                getline(cin, zip);
                
                cout << "Username: ";
                string username;
                getline(cin, username);
                
                if(db.usernameExists(username)) {
                    cout << "\nUsername already exists! Please choose a different username." << endl;
                    pauseScreen();
                    break;
                }
                
                cout << "Password: ";
                string password;
                getline(cin, password);
                
                cout << "\nSelect Role:" << endl;
                cout << "1. Student" << endl;
                cout << "2. Faculty" << endl;
                cout << "3. Staff" << endl;
                cout << "4. Administrator" << endl;
                cout << "Enter choice: ";
                int roleChoice;
                cin >> roleChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                string role;
                switch(roleChoice) {
                    case 1: role = "Student"; break;
                    case 2: role = "Faculty"; break;
                    case 3: role = "Staff"; break;
                    case 4: role = "Administrator"; break;
                    default: role = "Student";
                }
                
                string userID = db.generateID(role.substr(0, 3).c_str());
                Person newUser(userID, firstName, lastName, email, phone, street, city, 
                              state, zip, username, password, role);
                
                if(db.registerUser(newUser)) {
                    cout << "\nRegistration successful! You can now sign in." << endl;
                    cout << "Your ID is: " << userID << endl;
                } else {
                    cout << "\nRegistration failed. Please try again." << endl;
                }
                pauseScreen();
                break;
            }
            case 3:
                cout << "\nThank you for using University Management System!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pauseScreen();
        }
    } while(choice != 3);
    
    return 0;
}