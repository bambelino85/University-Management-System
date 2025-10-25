# University Management System

## Overview
A comprehensive University Management System built in C++ with role-based access control, file-based database persistence, and extensive menu options for students, faculty, staff, and administrators.

**Current State**: Fully functional with complete class hierarchy, authentication system, and role-specific menus.

**Last Updated**: October 25, 2025

## Recent Changes
- October 25, 2025: Complete implementation of University Management System
  - Created comprehensive class hierarchy with Person base class
  - Implemented specialized classes for Students, Faculty, Staff, and Administrators
  - Built file-based database management system with data persistence
  - Implemented secure authentication with password hashing
  - Created role-based access control (RBAC) system
  - Added extensive menu options for all user roles

## Project Architecture

### Class Hierarchy

#### Base Class
- **Person**: Base class with common attributes (ID, name, email, phone, address, username, password, role)

#### Student Classes
- **Student**: Base student class with major, GPA, enrollment status, academic standing, credits, advisor
- **UndergraduateStudent**: Extends Student with graduation year
- **GraduateStudent**: Extends Student with thesis title and research area
- **HonorsStudent**: Extends Student with honors program information

#### Faculty Classes
- **Faculty**: Base faculty class with department, office location, office hours, courses teaching
- **Professor**: Full Professor
- **AssociateProfessor**: Associate Professor
- **AssistantProfessor**: Assistant Professor
- **Lecturer**: Lecturer position

#### Staff Classes
- **Staff**: Base staff class with staff role, department, office location
- **AdministrativeStaff**: Administrative staff members
- **TechnicalStaff**: Technical support staff
- **AdvisorStaff**: Academic advisors with advisee management

#### Administrator
- **Administrator**: System administrators with full access

### Academic Entity Classes
- **Course**: courseID, name, credits, department, schedule, instructor, capacity, enrollment
- **Department**: departmentID, name, department head, building
- **Major**: majorID, name, department, required credits
- **Enrollment**: Links students to courses with semester information
- **Grade**: Stores student grades with letter and numeric values
- **Appointment**: Manages advisor appointments with students

### System Components

#### Authentication System
- Secure password hashing using hash function
- Username and password validation
- User role identification
- Credential storage in `data/users.dat`

#### Database Management System
- File-based storage in `data/` directory
- Files: users.dat, courses.dat, enrollments.dat, grades.dat, appointments.dat
- CRUD operations for all entities
- Data persistence across sessions

#### Role-Based Access Control (RBAC)
- Different menu options based on user role
- Permission enforcement for sensitive operations
- Isolated functionality for each role type

### Menu Options by Role

#### Student Menu (12 options)
1. View Registered Courses
2. View Grades
3. View Transcript
4. View GPA
5. Register for Course
6. Drop Course
7. View Class Schedule
8. Book Advisor Appointment
9. View Appointments
10. View Financial Aid Status
11. Update Personal Information
12. View Profile

#### Faculty Menu (11 options)
1. View Assigned Courses
2. Update Student Grade
3. View Class Roster
4. Post Assignment
5. Record Attendance
6. View Office Hours
7. Submit Grade Report
8. Update Course Syllabus
9. View All Courses
10. Update Personal Information
11. View Profile

#### Staff Menu (10 options)
1. Manage Student Records
2. Generate Reports
3. View Department Data
4. Schedule Courses
5. Manage Enrollments
6. Process Registration
7. View All Students
8. View All Courses
9. Update Personal Information
10. View Profile

#### Administrator Menu (10 options)
1. User Management
2. Generate System Reports
3. Manage Departments
4. Manage Courses
5. View Audit Logs
6. System Statistics
7. Backup Database
8. View All Users
9. Create Sample Data
10. Update Personal Information

## Technical Details

### Dependencies
- C++ Standard Library (C++11)
- No external dependencies required

### Build System
- Makefile for easy compilation
- Clang++ compiler with C++11 standard
- Compiler flags: -Wall -Wextra for warnings

### File Structure
```
.
├── main.cpp              # Complete system implementation
├── Makefile              # Build configuration
├── data/                 # Database files directory
│   ├── users.dat         # User credentials and information
│   ├── courses.dat       # Course catalog
│   ├── enrollments.dat   # Student course registrations
│   ├── grades.dat        # Student grades
│   └── appointments.dat  # Advisor appointments
└── replit.md             # Project documentation
```

### Compilation and Execution
```bash
make           # Compile the program
make run       # Compile and run
make clean     # Remove compiled files
./university_system  # Run directly
```

## Features

### User Management
- Sign up with comprehensive personal information
- Sign in with username/password authentication
- Role selection during registration
- Secure credential storage

### Data Persistence
- All data stored in pipe-delimited text files
- Automatic file creation on first use
- Data survives program restarts
- Simple backup and restore capabilities

### Security
- Password hashing for secure storage (Note: Uses simple DJB2 hash for demonstration purposes; production systems should use bcrypt/scrypt/Argon2 with salting)
- Role-based access restrictions
- Input validation throughout
- Protected administrative functions
- Credentials stored separately from plaintext data

### User Experience
- Clear console-based interface
- Screen clearing between menus
- Pause between operations
- Formatted table displays
- Helpful error messages

## Getting Started

1. **First Time Setup**
   - Compile the program: `make`
   - Run the program: `./university_system`
   - Sign up as an Administrator to access all features
   - Use "Create Sample Data" in admin menu to populate courses

2. **Regular Use**
   - Sign in with your username and password
   - Navigate menus using number choices
   - Update personal information as needed
   - Access role-specific functionality

3. **Sample Data**
   - Administrators can create sample courses using option 9
   - Creates 5 courses across different departments
   - Helps test registration and enrollment features

## Future Enhancements

### Planned Features
- Advanced reporting with grade distributions and analytics
- Course prerequisite checking and validation
- Waitlist management for full courses
- Email notification system for deadlines
- Enhanced security with password complexity requirements
- Account lockout after failed login attempts
- Degree audit system for graduation requirements

### Possible Improvements
- Export data to CSV/PDF format
- Import bulk data from files
- Advanced search and filtering
- Student financial account management
- Library integration
- Housing and meal plan management
- Event calendar and scheduling

## Notes
- This is a console-based application (TUI)
- Database files are created automatically in `data/` directory
- Password hashing uses a simple hash function (suitable for demonstration)
- All menus return to main menu on logout
- Data validation ensures system stability
