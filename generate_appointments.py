#!/usr/bin/env python3
import random
from datetime import datetime, timedelta

# Read all student IDs
student_ids = []
with open('data/users.dat', 'r') as f:
    for line in f:
        fields = line.strip().split('|')
        if len(fields) >= 12 and fields[11] == 'Student':
            student_ids.append(fields[0])

# Read all faculty IDs (advisors)
faculty_ids = []
with open('data/users.dat', 'r') as f:
    for line in f:
        fields = line.strip().split('|')
        if len(fields) >= 12 and fields[11] == 'Faculty':
            faculty_ids.append(fields[0])

print(f"Found {len(student_ids)} students and {len(faculty_ids)} faculty members")

# Generate appointment data
appointments = []
appointment_id = 1

# Academic year dates
fall_start = datetime(2024, 8, 20)
fall_end = datetime(2024, 12, 15)
spring_start = datetime(2025, 1, 10)
spring_end = datetime(2025, 5, 10)
summer_start = datetime(2025, 5, 20)
summer_end = datetime(2025, 8, 10)
fall2025_start = datetime(2025, 8, 25)
fall2025_end = datetime(2025, 12, 20)

today = datetime(2025, 10, 25)

purposes = [
    "Course Selection for Next Semester",
    "Academic Planning",
    "Career Guidance",
    "Grade Discussion",
    "Study Abroad Consultation",
    "Major Declaration",
    "Research Opportunities",
    "Internship Planning",
    "Academic Probation Discussion",
    "Graduation Requirements Review",
    "Transfer Credit Evaluation",
    "Schedule Adjustment",
    "Academic Performance Review",
    "Thesis Planning"
]

times = ["09:00", "10:00", "11:00", "13:00", "14:00", "15:00", "16:00"]

# For each student, generate 2-4 appointments (mix of past and upcoming)
for student_id in student_ids:
    # Assign a primary advisor
    advisor_id = random.choice(faculty_ids)
    
    # Generate 2-4 appointments per student
    num_appointments = random.randint(2, 4)
    
    for i in range(num_appointments):
        # 60% chance of past appointment, 40% upcoming
        if random.random() < 0.6:
            # Past appointment (Completed)
            status = "Completed"
            # Random date in the past year
            date_options = []
            
            # Fall 2024
            current = fall_start
            while current <= fall_end and current < today:
                if current.weekday() < 5:  # Weekday
                    date_options.append(current)
                current += timedelta(days=1)
            
            # Spring 2025
            current = spring_start
            while current <= spring_end and current < today:
                if current.weekday() < 5:
                    date_options.append(current)
                current += timedelta(days=1)
            
            # Summer 2025
            current = summer_start
            while current <= summer_end and current < today:
                if current.weekday() < 5:
                    date_options.append(current)
                current += timedelta(days=1)
            
            # Fall 2025 (up to today)
            current = fall2025_start
            while current < today:
                if current.weekday() < 5:
                    date_options.append(current)
                current += timedelta(days=1)
            
            if date_options:
                appt_date = random.choice(date_options)
            else:
                appt_date = today - timedelta(days=random.randint(1, 30))
        else:
            # Upcoming appointment (Scheduled)
            status = "Scheduled"
            # Future date in the next 60 days
            days_ahead = random.randint(1, 60)
            appt_date = today + timedelta(days=days_ahead)
            
            # Make sure it's a weekday
            while appt_date.weekday() >= 5:
                appt_date += timedelta(days=1)
        
        # Format date as YYYY-MM-DD
        date_str = appt_date.strftime("%Y-%m-%d")
        time_str = random.choice(times)
        purpose = random.choice(purposes)
        
        # Sometimes use a different advisor
        if random.random() < 0.1:
            current_advisor = random.choice(faculty_ids)
        else:
            current_advisor = advisor_id
        
        # APT001, APT002, etc.
        appt_id = f"APT{appointment_id:03d}"
        
        appointment = f"{appt_id}|{student_id}|{current_advisor}|{date_str}|{time_str}|{purpose}|{status}"
        appointments.append(appointment)
        appointment_id += 1

# Write appointments to file
with open('data/appointments.dat', 'w') as f:
    for appt in appointments:
        f.write(appt + '\n')

print(f"Generated {len(appointments)} appointments")

# Count by status
completed = sum(1 for a in appointments if a.endswith('|Completed'))
scheduled = sum(1 for a in appointments if a.endswith('|Scheduled'))
print(f"Completed: {completed}, Scheduled: {scheduled}")
