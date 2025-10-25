# University Management System - Quick Start Guide

## Getting Started

The University Management System is now running! Access it through the console tab above.

### First Time Setup

1. **Create an Administrator Account**
   - Select option `2` (Sign Up)
   - Fill in your personal information
   - When prompted for role, select `4` (Administrator)
   - Complete registration

2. **Sign In as Administrator**
   - Select option `1` (Sign In)
   - Enter your username and password
   - You'll be taken to the Administrator Menu

3. **Create Sample Data**
   - From the Administrator Menu, select option `9`
   - This creates 5 sample courses you can use for testing

### Creating Different User Types

You can create accounts for different roles:

**Student Account**: Choose role `1` during sign-up
- Access student menu with course registration, grades, transcripts, etc.

**Faculty Account**: Choose role `2` during sign-up
- Access faculty menu to manage courses, update grades, view rosters, etc.

**Staff Account**: Choose role `3` during sign-up
- Access staff menu for student records, reports, scheduling, etc.

**Administrator Account**: Choose role `4` during sign-up
- Full system access and management capabilities

## Key Features by Role

### Students Can:
- View and register for courses
- Check grades and transcripts
- Calculate GPA
- Book advisor appointments
- View class schedule
- Update personal information

### Faculty Can:
- View assigned courses
- Update student grades
- View class rosters
- Post assignments
- Record attendance
- Manage office hours
- Submit grade reports

### Staff Can:
- Manage student records
- Generate various reports
- Schedule courses
- Process registrations
- View department data
- Manage enrollments

### Administrators Can:
- Full user management
- Create sample data
- Generate system-wide reports
- Manage departments and courses
- View system statistics
- Backup database

## Example Workflow

1. **Sign up as Administrator** → Create sample courses
2. **Sign up as Faculty** → Assign yourself to courses (using instructor IDs from sample data)
3. **Sign up as Student** → Register for courses
4. **As Faculty** → Update student grades
5. **As Student** → View grades and transcript

## Data Persistence

All data is automatically saved to the `data/` directory:
- User credentials and profiles
- Course catalog
- Enrollments
- Grades
- Appointments

Your data persists between sessions!

## Tips

- Use the Administrator account to explore all system features
- Create sample courses before testing student registration
- Each role has unique menu options tailored to their needs
- All users can update their personal information (email, phone)

## Security Note

The system uses password hashing for credential storage. For demonstration purposes, it uses a simple hash function. In a production environment, this should be upgraded to bcrypt, scrypt, or Argon2 with salt.

## Need Help?

Check `replit.md` for complete documentation including:
- Full class hierarchy
- Detailed feature list
- Technical architecture
- Future enhancement ideas
