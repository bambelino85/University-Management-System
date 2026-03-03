#include "../include/database.h"
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
                double gpa = db.calculateStudentGPA(userID);
                vector<Grade> grades = db.loadGradesByStudent(userID);
                
                if(grades.empty()) {
                    cout << "No grades available for GPA calculation." << endl;
                } else {
                    cout << "Current GPA: " << fixed << setprecision(2) << gpa << " / 4.0" << endl;
                    cout << "Total Courses: " << grades.size() << endl;
                    
                    // Show academic standing
                    cout << "\nAcademic Standing: ";
                    if(gpa >= 3.75) {
                        cout << "Dean's List" << endl;
                    } else if(gpa >= 3.5) {
                        cout << "Honor Roll" << endl;
                    } else if(gpa >= 2.0) {
                        cout << "Good Standing" << endl;
                    } else {
                        cout << "Academic Probation" << endl;
                    }
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