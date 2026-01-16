# 🏢 Hostel Management System

<div align="center">

```
██╗  ██╗ ██████╗ ███████╗████████╗███████╗██╗         
██║  ██║██╔═══██╗██╔════╝╚══██╔══╝██╔════╝██║         
███████║██║   ██║███████╗   ██║   █████╗  ██║         
██╔══██║██║   ██║╚════██║   ██║   ██╔══╝  ██║         
██║  ██║╚██████╔╝███████║   ██║   ███████╗███████╗    
╚═╝  ╚═╝ ╚═════╝ ╚══════╝   ╚═╝   ╚══════╝╚══════╝    
                                                        
███╗   ███╗ ██████╗ ████████╗
████╗ ████║██╔════╝ ╚══██╔══╝
██╔████╔██║██║  ███╗   ██║   
██║╚██╔╝██║██║   ██║   ██║   
██║ ╚═╝ ██║╚██████╔╝   ██║   
╚═╝     ╚═╝ ╚═════╝    ╚═╝   
```

*Complete console-based hostel administration and student portal*

[![Language](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://www.microsoft.com/windows)
[![File Management](https://img.shields.io/badge/File_I%2FO-Enabled-success?style=for-the-badge)](https://github.com)

</div>

---

## 📖 About

A comprehensive Hostel Management System built in C++ that streamlines hostel operations through an intuitive console interface. This system features dual-portal access (Admin & Student), file-based persistent storage, and complete management of students, rooms, fees, mess services, and visitor records.

### ✨ Key Features

#### 👨‍💼 Admin Portal
- **Student Management**
  - Add, view, edit, and delete student records
  - Search functionality with instant results
  - Track student details (ID, name, phone, email, room assignment)
  - Custom password system for each student

- **Room Management**
  - Assign students to rooms (2 students per room, 50 rooms total)
  - View current room allocations
  - Edit room assignments
  - Automatic room availability tracking

- **Fee Management**
  - Assign hostel fees to students
  - Mark fees as paid/unpaid
  - View individual student fee status
  - Generate unpaid fees report
  - Track mess fees separately

- **Visitor Management**
  - Register visitor check-ins/check-outs
  - Track visitor details (name, CNIC, relation to student)
  - Maintain comprehensive visitor logs
  - Search visitor records
  - Track currently checked-in visitors

- **Mess Management**
  - Set daily breakfast, lunch, and dinner menus
  - View current meal schedules

#### 👨‍🎓 Student Portal
- **Profile Management**
  - View personal details
  - Check room assignment and roommate info
  - Secure login with student ID and password

- **Financial Dashboard**
  - View hostel fee status
  - Check mess billing
  - Track payment status

- **Services**
  - View mess menu schedules
  - Check visitor history

---

## 🎯 System Architecture

### Data Structures

```cpp
struct Student {
    int id;              // Unique student identifier
    string name;         // Full name
    string studentPhone; // Contact number
    int roomID;          // Assigned room (1-50)
    int fees;            // Hostel fees amount
    bool feesPaid;       // Payment status
    string email;        // Email address
    string password;     // Login password (default: "123")
    int MessFees;        // Mess charges
    bool MessPaid;       // Mess payment status
};

struct Visitor {
    string visitorName;   // Visitor's name
    string relation;      // Relationship to student
    string CNIC;          // National ID card number
    int studentIDToVisit; // Which student they're visiting
    string timeIn;        // Check-in time
    string timeOut;       // Check-out time
    bool isStillIn;       // Currently in hostel?
};

struct Room {
    int StudentID1;      // First occupant
    int StudentID2;      // Second occupant
};
```

### Capacity
- **Students**: Up to 100
- **Rooms**: 50 rooms (2 students each)
- **Visitors**: Log capacity of 200 entries

---

## 🚀 Getting Started

### Prerequisites

- Windows OS (uses Windows.h for console manipulation)
- C++ compiler (MinGW, MSVC, or Visual Studio)
- Terminal/Console with UTF-8 support

### Compilation

Using g++:
```bash
g++ main.cpp -o HostelManagementSystem.exe
```

Using Visual Studio:
```bash
cl main.cpp /Fe:HostelManagementSystem.exe
```

### Running the System

```bash
./HostelManagementSystem.exe
```

The system launches in fullscreen mode with the main login menu.

---

## 🔐 Default Credentials

### Admin Access
- **Username**: `Admin`
- **Password**: `Admin`

### Student Access
- **Default Password**: `123` (for all new students)
- Students login using their assigned Student ID

---

## 🎮 User Guide

### Admin Workflow

1. **Adding a New Student**
   ```
   Main Menu → Admin Login → Student Management → Add Student
   Enter: ID, Name, Phone, Email
   Student is created with default password "123"
   ```

2. **Assigning a Room**
   ```
   Admin Menu → Room Management → Assign Room
   Enter: Room ID (1-50), Student 1 ID, Student 2 ID
   System validates and assigns
   ```

3. **Managing Fees**
   ```
   Admin Menu → Fees Management → Assign Fees
   Enter: Student ID, Fee Amount
   Later: Mark as Paid when student pays
   ```

4. **Registering a Visitor**
   ```
   Admin Menu → Visitor Management → Add Visitor
   Enter: Name, CNIC, Relation, Student ID to Visit
   Time is automatically logged
   ```

### Student Workflow

1. **Login**
   ```
   Main Menu → Student Login
   Enter: Student ID and Password
   ```

2. **View Profile**
   ```
   Student Dashboard → View My Profile
   See: Name, ID, Phone, Email, Room Assignment
   ```

3. **Check Fee Status**
   ```
   Student Dashboard → View Fee Status
   See: Hostel fees, Mess fees, Payment status
   ```

4. **View Visitors**
   ```
   Student Dashboard → My Visitors
   See: All visitors who came to meet you
   ```

---

## 💾 Data Persistence

The system uses file-based storage for permanent data retention:

### Files Created
- `MAIN.txt` - Student records database
- `MAINROOMS.txt` - Room allocation data
- Visitor logs and mess menu data (in-memory, can be extended to files)

### Data Format
Data is stored in pipe-delimited format for easy parsing:
```
ID|Name|Phone|RoomID|Fees|FeesPaid|Email|Password|MessFees|MessPaid
```

### Auto-Save Feature
- Student data is automatically saved after every modification
- Room assignments persist across sessions
- All changes are immediately written to disk

---

## 🎨 Interface Features

### Visual Elements
- **Colored Console Output**: Different colors for headers, warnings, inputs
- **Box Drawings**: Unicode box-drawing characters for professional UI
- **Shadow Effects**: Depth simulation for dialog boxes
- **Slow Print Animation**: Text typewriter effect for important messages
- **Clear Screen Management**: Organized content display

### Color Coding
- 🔴 **Red (4)**: Warnings and errors
- 🟢 **Green (10)**: Labels and success messages
- 🔵 **Cyan (11)**: Box borders and titles
- ⚪ **White (7)**: General text and input

### Navigation
- Arrow key navigation in menus
- Number-based selection
- Keyboard shortcuts for quick actions
- Press 'F' to confirm selections

---

## 🛠️ Technical Implementation

### Key Programming Concepts

**File I/O Operations**
- Text file reading/writing with fstream
- Pipe-delimited data parsing
- Persistent storage implementation

**Data Validation**
- Student ID uniqueness checking
- Room availability verification
- Input validation and error handling

**Search Algorithms**
- Linear search for student records
- ID-based lookup functions
- Visitor history filtering

**User Authentication**
- Credential verification system
- Role-based access control (Admin/Student)
- Password management

**Console Graphics**
- Windows API for cursor positioning
- Color manipulation using ANSI codes
- Box-drawing characters for UI

---

## 📊 System Modules

### 1. Student Module
```
├── Add Student
├── View All Students
├── Edit Student Details
├── Delete Student
└── Search Student
```

### 2. Room Module
```
├── Assign Room
├── View All Rooms
└── Edit Room Assignment
```

### 3. Fees Module
```
├── Assign Fees
├── Mark Fee Paid
├── View Fee Status
└── View Unpaid List
```

### 4. Visitor Module
```
├── Add Visitor (Check-in)
├── Check-out Visitor
├── View Current Visitors
├── View Visitor Log
└── Search Visitor
```

### 5. Mess Module
```
├── Set Breakfast Menu
├── Set Lunch Menu
├── Set Dinner Menu
└── View All Menus
```

---

## 🔧 Code Structure

### Main Components

```cpp
// Core Data Arrays
Student students[100];    // Student database
Room room[50];           // Room allocations
Visitor visitor[200];    // Visitor records

// Admin Functions
void addStudent();
void assignRoom();
void assignFees();
void getVisitor();

// Student Functions
void viewMyProfile(int index);
void viewMyRoom(int index);
void viewMyFeeStatus(int index);

// Utility Functions
void getData();          // Load from files
void addData();          // Save to files
int searchStudent(int ID);
void generateColors(int k);
```

---

## 📈 Statistics & Reporting

The system provides various analytical views:

- **Unpaid Fees Report**: List all students with pending payments
- **Room Occupancy**: View which rooms are occupied/vacant
- **Visitor Activity**: Track visitor frequency and patterns
- **Student Count**: Total enrolled students
- **Payment Statistics**: Track fee collection status

---

## 🎓 Educational Value

This project demonstrates:

- **Data Structure Design**: Effective use of structs for organizing related data
- **File Handling**: Complete CRUD operations with persistent storage
- **User Interface Design**: Console-based UI/UX principles
- **Access Control**: Role-based authentication systems
- **Search & Sort**: Efficient data retrieval algorithms
- **Input Validation**: Robust error checking and handling
- **Menu-Driven Architecture**: Modular program design
- **State Management**: Tracking and updating system state

---

## 🔮 Future Enhancements

Potential improvements for future versions:

- [ ] Database integration (MySQL/SQLite)
- [ ] Network support for multi-terminal access
- [ ] Backup and restore functionality
- [ ] Advanced reporting with charts/graphs
- [ ] Email notification system
- [ ] Automated fee calculation
- [ ] Student attendance tracking
- [ ] Complaint management system
- [ ] Room maintenance scheduling
- [ ] Export reports to PDF/Excel
- [ ] Enhanced security (password encryption)
- [ ] GUI version using Qt/wxWidgets

---

## 🚨 Important Notes

- **Data Safety**: Always backup `MAIN.txt` and `MAINROOMS.txt` before major updates
- **First Run**: System creates data files automatically on first run
- **Admin Access**: Change default admin credentials in production use
- **Student Passwords**: Students should change default password "123" after first login
- **Screen Resolution**: Best viewed in fullscreen mode (auto-enabled)
- **Data Limits**: Respect array size limits (100 students, 50 rooms, 200 visitor logs)

---

## 📝 License

This project is open source and available for educational purposes.

---

## 👨‍💻 Author

Created as a first-semester C++ programming project demonstrating comprehensive system design and implementation skills.

---

<div align="center">

**Manage smarter, live better! 🏢✨**

*"Efficient hostel management through elegant code"*

</div>
