#pragma once
#include "student.h"
#include "faculty.h"
#include "course.h"
#include <fstream>
#include <cstdlib>
#include <limits>
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
    
    double convertTo4PointScale(double numericGrade) {
        // Convert 0-100 numeric grade to 4.0 scale
        if(numericGrade >= 93.0) return 4.0;      // A
        if(numericGrade >= 90.0) return 3.7;      // A-
        if(numericGrade >= 87.0) return 3.3;      // B+
        if(numericGrade >= 83.0) return 3.0;      // B
        if(numericGrade >= 80.0) return 2.7;      // B-
        if(numericGrade >= 77.0) return 2.3;      // C+
        if(numericGrade >= 73.0) return 2.0;      // C
        if(numericGrade >= 70.0) return 1.7;      // C-
        if(numericGrade >= 67.0) return 1.3;      // D+
        if(numericGrade >= 63.0) return 1.0;      // D
        if(numericGrade >= 60.0) return 0.7;      // D-
        return 0.0;                               // F
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
                double numericGrade = stod(fields[4]);
                totalPoints += convertTo4PointScale(numericGrade);
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
                cout << "GPA: " << fixed << setprecision(2) << gpa << " / 4.0" << endl;
                
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
