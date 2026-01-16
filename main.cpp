#include <algorithm>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <ctime>
#define WIDTH 152
using namespace std;
const int boxX =48;
const int boxY = 13;
const int boxWidth = 40;
const int WARNING_RED = 4;
const int INPUT_WHITE = 7;
//Function Declarations
//print FUnctions
void printHeading();
void printAdminOptions(int selected,int &choice);
void clearStage();
void saveVisitors();
void printLog();
void logSupport(int startFrom);
void searchVisitor();
void checkOutVisitor();
void printMainLogin(int selected,int &choice) ;
void printColoredWord(string text, int colorCode);
void mainPrint(int &choice,string s[],const int rows,const string title);
void generateColors(int k);
void gotoxy(int x, int y);
void hideCursor();
void addData();
void getData();
void getStudentChoice();
void viewCurrentVisitors();
void addStudent();
void viewStudents();
void editStudent();
void deleteStudent();
void searchRecord();
void visitorLog(int index);
void assignFees();
void markPaid();
void viewFeeStatus();
void getVisitorOptions();
int searchStudent(int ID);
void UpdateRoom();
void getFeesChoice();
void getVisitorData() ;
void saveVisitors();
void getRoomChoice() ;
void viewMyProfile(int index);
void assignRoom();
void viewRooms() ;
void setFullScreen();
void editRoom();
void unpaidList();
void slowPrint(string s, int speed);
void clearInputBuffer();
void getStudentLogin(bool &access,int &ID);
void viewMyRoom(int index);
void viewMyFeeStatus(int index);
void getMessOptions();
void getVisitor();
void printMenu(string menu[],int rows,int selected,string title);
int getMainChoice(int &choice,string s[],int rows);
void studentChoice(int &choice) ;
const int DEFAULT_COLOR = 7;
void viewMyBilling(int index) ;
void viewMessMenu();
void viewMyVisitors(int studentID);
//Function Declarations
//ADMIN CREDENTIALS
const string AdminUsername = "Admin";
const string AdminPass = "Admin";
void drawShadow(int x, int y, int width, int height);

//Used Structs Instead of Parallel Arrays
struct Student {
    int id{};
    string name;
    string studentPhone;
    int roomID{};
    int fees{};
    bool feesPaid = false;
    string email;
    string password = "123";
    int MessFees = 0;
    bool MessPaid = false;
};
struct Visitor {
    string visitorName;
    string relation;
    string CNIC;
    int studentIDToVisit;
    string timeIn;
    string timeOut;
    bool isStillIn = false;
};
Student students[100];
struct Room {
    int StudentID1 = 0;
    int StudentID2 = 0;
};
Visitor visitor[200];
Room room[50];
string breakfastMenu = "Not Set";
string lunchMenu = "Not Set";
string dinnerMenu = "Not Set";
int studentsCount = 0;
void drawBox(int x, int y, int width, int height, string title);
void adminLoginPage(bool &AdminAccess);
int roomsCount = 0;
int visitorCount  = 0;
fstream studentFile;
fstream visitorFile;
int main() {
    int mainChoice = 0;
    SetConsoleOutputCP(CP_UTF8);
    hideCursor();
    setFullScreen();
    getData();
    bool AdminAccess = false;
    bool studentAccess = false;
    while (mainChoice != 2) {
        printHeading();
        printMainLogin(0,mainChoice);
        if (mainChoice == 0) {
            adminLoginPage(AdminAccess);
            printHeading();
            if (AdminAccess) {
                int choice = 0;
                while (choice != 5) {
                    printHeading();
                    printAdminOptions(0,choice);
                    if (choice == 0) {
                        getStudentChoice();
                    }else if (choice == 1) {
                        getRoomChoice();
                    }else if (choice == 2) {
                        getFeesChoice();
                    }else if (choice == 3) {
                        getVisitorOptions();
                    }else if (choice == 4) {
                        getMessOptions();
                    }
                }
            }
        }else if (mainChoice == 1) {
            int ID;
            getStudentLogin(studentAccess,ID);
            if (studentAccess) {
                int choice = 0;
                while (choice != 6) {
                    studentChoice(choice);
                    if (choice == 0) {
                        viewMyProfile(ID);
                    }else if (choice == 1) {
                        viewMyRoom(ID);
                    }else if(choice == 2) {
                        viewMyFeeStatus(ID);
                    }else if (choice == 3) {
                        viewMessMenu();
                    }else if (choice ==4) {
                        viewMyBilling(ID);
                    }else if (choice == 5) {
                        viewMyVisitors(ID);
                    }
                }
            }
        }
    }
    return 0;
}
void clearStage() {
    int h;

    for (int y = 13; y < 25; y++) {
        gotoxy(0, y);
        for(int x = 0; x < WIDTH; x++) cout << " ";
    }
}
void slowPrint(string s, int speed) {
    for (char c : s) {
        cout << c;
        Sleep(speed);
    }
}
void addData() {
    studentFile.open("MAIN.txt",ios::out);
    studentFile << studentsCount << "\n";
    for (int i = 0; i < studentsCount; i++) {
        studentFile << students[i].id << "|" << students[i].name << "|"
                    << students[i].studentPhone << "|" << students[i].roomID << "|"
                    << students[i].fees << "|" << students[i].feesPaid << "|"
                    << students[i].email << "|" << students[i].password << "|"
                    << students[i].MessFees <<"|" << students[i].MessPaid << '\n';
    }
    studentFile.close();
}
void getData() {
    studentFile.open("MAIN.txt", ios::in);
    if (!studentFile) return;
    studentFile >> studentsCount;
    studentFile.ignore();
    string temp;
    for (int i = 0; i < studentsCount; i++) {
        getline(studentFile, temp, '|');
        if(!temp.empty()) students[i].id = stoi(temp);
        getline(studentFile, students[i].name, '|');
        getline(studentFile, students[i].studentPhone, '|');
        getline(studentFile, temp, '|');
        if(!temp.empty()) students[i].roomID = stoi(temp);
        getline(studentFile, temp, '|');
        if(!temp.empty()) students[i].fees = stoi(temp);
        getline(studentFile, temp, '|');
        students[i].feesPaid = (temp == "1");
        getline(studentFile, students[i].email, '|');
        getline(studentFile, students[i].password, '|');
        getline(studentFile, temp, '|');
        if(!temp.empty()) students[i].MessFees = stoi(temp);
        getline(studentFile, temp, '\n');
        students[i].MessPaid = (temp == "1");
        studentFile >> ws;
    }
    studentFile.close();
    studentFile.open("MAINROOMS.txt", ios::in);
    if (!studentFile) return;
    for (int i = 0; i < 50; i++) {
        getline(studentFile, temp, '|');
        getline(studentFile, temp, '|');
        if(!temp.empty()) room[i].StudentID1 = stoi(temp);
        getline(studentFile, temp, '\n');
        if(!temp.empty()) room[i].StudentID2 = stoi(temp);
        studentFile >> ws;
    }
    studentFile.close();
}
void clearInputBuffer() {
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    FlushConsoleInputBuffer(hStdIn);
    while (_kbhit()) {_getch();}
    fflush(stdin);
}
void setFullScreen() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}
void drawBox(int x, int y, int width, int height, string title) {
    drawShadow(x,y,width,height);
    generateColors(11);
    gotoxy(x, y);
    cout << "╔";
    for (int i = 0; i < width - 2; i++) cout << "═";
    cout << "╗";
    for (int i = 1; i < height; i++) {
        gotoxy(x, y + i); cout << "║";
        gotoxy(x + width - 1, y + i); cout << "║";
    }
    gotoxy(x, y + height);
    cout << "╚";
    for (int i = 0; i < width - 2; i++) cout << "═";
    cout << "╝";
    int titlePos = x + (width / 2) - (title.length() / 2);
    gotoxy(titlePos, y);
    generateColors(143);
    cout << " " << title << " ";
}
void adminLoginPage(bool &access) {
    clearStage();
    clearInputBuffer();
    int startX = boxX, startY = boxY;
    int width = 40, height = 10;
    drawBox(startX, startY, width, height, "ADMIN SECURE ACCESS");
    generateColors(INPUT_WHITE);
    gotoxy(startX + 4, startY + 3); cout << "USERNAME: ";
    gotoxy(startX + 4, startY + 5); cout << "PASSWORD: ";
    generateColors(8);
    gotoxy(startX + 14, startY + 3); cout << "____________________";
    gotoxy(startX + 14, startY + 5); cout << "____________________";
    string user, pass;
    generateColors(15);
    gotoxy(startX + 14, startY + 3);
    cin >> user;
    gotoxy(startX + 14, startY + 5);
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) {
            break;
        }
        else if (ch == 8) {
            if (pass.length() > 0) {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == 32 || ch == 0 || ch == 224) {

            continue;
        }
        else {
            pass += ch;
            cout << '*';
        }
    }
    if (user == "admin" && pass == "123") {
        gotoxy(startX + 10, startY + 8);
        generateColors(10);
        access = true;
        slowPrint("ACCESS GRANTED! Welcome.",3);
    } else {
        access = false;
        gotoxy(startX + 8, startY + 8);
        generateColors(WARNING_RED);
        slowPrint("ACCESS DENIED. Try again.",3);
    }
    Sleep(2000);
}
void drawShadow(int x, int y, int width, int height) {
    generateColors(8);
    for (int i = 1; i <= height; i++) {
        gotoxy(x + width, y + i);
        cout << "█";
    }
    gotoxy(x + 1, y + height + 1);
    for (int i = 0; i < width; i++) {
        cout << "█";
    }
}
void printMenu(string menu[],int rows,int selected,string title) {
    int x = 50;
    int y = 14;
    generateColors(10);
    for (int i = 0 ; i < rows ; i++) {
        gotoxy(55,y+i);
        if (i == selected) {
            printColoredWord(menu[i],122);
        }else {
            printColoredWord(menu[i],10);
        }
    }
}
int getMainChoice(int &choice,string s[],int rows) {
    choice = 0;
    while (true) {
        if (GetAsyncKeyState(VK_UP)) {
            if (choice > 0) {
                choice--;
                printMenu(s,rows,choice,"Menu");
            }
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            if (choice < rows-1) {
                choice++;
                printMenu(s,rows,choice,"Menu");
            }
        }
        if (GetAsyncKeyState('F')) {
            return 0;
        }
        Sleep(150);
    }
}
void printHeading() {
    system("cls");
    generateColors(11);
    int x = 32;
    int y = 0;
    string heading[][87] = {
        {"  ██╗  ██╗ ██████╗ ███████╗████████╗███████╗██╗     ███████╗██╗      ██████╗ ██╗    ██╗"},
        {"  ██║  ██║██╔═══██╗██╔════╝╚══██╔══╝██╔════╝██║     ██╔════╝██║     ██╔═══██╗██║    ██║"},
        {"  ███████║██║   ██║███████╗   ██║   █████╗  ██║     █████╗  ██║     ██║   ██║██║ █╗ ██║"},
        {"  ██╔══██║██║   ██║╚════██║   ██║   ██╔══╝  ██║     ██╔══╝  ██║     ██║   ██║██║███╗██║"},
        {"  ██║  ██║╚██████╔╝███████║   ██║   ███████╗███████╗██║     ███████╗╚██████╔╝╚███╔███╔╝"},
        {"  ╚═╝  ╚═╝ ╚═════╝ ╚══════╝   ╚═╝   ╚══════╝╚══════╝╚═╝     ╚══════╝ ╚═════╝  ╚══╝╚══╝ "}
    };
    for (int i = 0; i < 6 ; i++) {
        gotoxy(x,y);
        for (int j = 0; j < 87; j++) {
            cout << heading[i][j];
        }
        y++;
    }
    cout << endl;
    generateColors(8);
    cout << "  ";
    for(int i=0; i<145; i++) cout << "═";
    cout << endl;
    generateColors(15);
    gotoxy(x+3,y+1);
    cout << "    >> PREMIER HOSTEL MANAGEMENT SYSTEM | SECURE ACCESS | v2.0" << endl;
    generateColors(8);
    cout << "  ";
    for(int i=0; i<145; i++) cout << "═";
    cout << endl;
    generateColors(INPUT_WHITE);
    cout << endl;
}
void printMainLogin(int selected,int &choice) {
    string s[] = {
        "  [1] Login as Admin  ",
        "  [2] Login as Student",
        "  [3] Exit Program    ",
    };
    drawBox(48,13,40,5,"Menu");
    printMenu(s,sizeof(s)/sizeof(string),selected,"Menu");
    getMainChoice(choice,s,sizeof(s)/sizeof(string));
}
void assignMonthlyMessDues() {
    clearStage();
    clearInputBuffer();
    clearInputBuffer();
    drawBox(boxX,boxY,boxWidth+20,4,"SET MESS FEES");
    int monthlyRate;
    gotoxy(boxX+3,boxY+1);
    generateColors(10);
    cout << "Enter the Monthly Mess Charge for ALL students: ";
    cin >> monthlyRate;
    if (monthlyRate < 0) {
        gotoxy(boxX+5,boxY+3);
        generateColors(4);
        printColoredWord("Invalid amount. Please enter a positive value.", 12);
    } else {
        for (int i = 0; i < studentsCount; i++) {
            students[i].MessFees += monthlyRate;
        }
        generateColors(10);
        gotoxy(boxX+5,boxY+3);
        slowPrint("Successfully added " + to_string((int)monthlyRate) + " to all " + to_string(studentsCount) + " students.",5);
    }
    addData();
    getch();
}
void addExtraCharge() {
    clearStage();
    int ID;
    clearInputBuffer();
    drawBox(boxX,boxY,boxWidth,9,"ADD STUDENT DETAILS");
    int j = 3;
    generateColors(10);
    const string s[] = {"Student ID : ","Assign Extra Charges : "};
    for ( const string& i : s){
        gotoxy(boxX+3,boxY+j);
        cout << i;
        j += 2;
    }
    generateColors(INPUT_WHITE);
    gotoxy(boxX+17,boxY+3);
    cin >> ID;
    ID = searchStudent(ID);
    if (ID != -1) {
        gotoxy(boxX+26,boxY+5);
        int fees;
        do {
            cin >> fees;
            students[ID].MessFees += fees;
        }while (fees <= 10);
        gotoxy(boxX+6,boxY+8);
        generateColors(10);
        slowPrint("Fees Assigned Successfully!",5);
    }else {
        gotoxy(boxX+6,boxY+7);
        generateColors(WARNING_RED);
        cout << "INVALID STUDENT ID.";
        gotoxy(boxX+17,boxY+8);
        cout << "RETURNING TO MAIN MENU";
    }
    addData();
    getch();
}
void allMessDues() {
    clearStage();
    clearInputBuffer();
    generateColors(10);
    drawBox(20,boxY,WIDTH-60,studentsCount + 3,"DUES LIST");
    gotoxy(23,14);
    generateColors(10);
    cout << left <<setw(5)<< "ID" << setw(20)<< "NAME" << setw(20)<< "PHONE"<<setw(10)<<"MESS FEE"<<setw(15)<<"Fees Status"<<setw(20);
    gotoxy(23,15);
    for (int j=38 ; j <WIDTH-70;j++ )
        cout << "=";
    int currentY=16;
    for (int i = 0; i < studentsCount ; i++) {
            gotoxy(23,currentY);
            cout << left << setw(5) << students[i].id
                 << setw(20) << students[i].name
                 << setw(20) << students[i].studentPhone
                 << setw(10) << students[i].MessFees;
        if (students[i].MessFees == true) {
            printColoredWord("Paid",9);
        }else {
            printColoredWord("Unpaid",WARNING_RED);
        }
            currentY++;
    }
    getch();
}
void updateMessMenu() {
    clearStage();
    clearInputBuffer();
    string labels[] = {"Breakfast : ", "Lunch : ", "Dinner : "};
    drawBox(boxX, boxY, boxWidth, 11, "UPDATE TODAY'S MENU");
    int j = 3;
    generateColors(10);
    for (const string& label : labels) {
        gotoxy(boxX + 3, boxY + j);
        cout << label;
        j += 2;
    }
    gotoxy(boxX + 15, boxY + 3);
    getline(cin, breakfastMenu);
    gotoxy(boxX + 15, boxY + 5);
    getline(cin, lunchMenu);
    gotoxy(boxX + 15, boxY + 7);
    getline(cin, dinnerMenu);
    gotoxy(boxX + 3, boxY + 10);
    generateColors(10);
    fstream mess;
    mess.open("mess.txt",ios::in);
    mess<< breakfastMenu << "|" << lunchMenu << "|" << dinnerMenu;
    mess.close();
    cout << "Menu Updated Successfully!";
    getch();
}
void getMessOptions() {
    int choice = 0;
    clearInputBuffer();
    clearStage();
    string s[] = {" [1] Assign Monthly Mess Bill"," [2] Add Extra Charges"," [3] View All Mess Dues"," [4] Update Today's Menu"," [5] Exit to Main Menu"};
    mainPrint(choice,s,sizeof(s)/sizeof(string),"Mess Options");
    if (choice == 0) {
        assignMonthlyMessDues();
    }else if (choice == 1) {
        addExtraCharge();
    }else if (choice == 2) {
        allMessDues();
    }else if (choice == 3) {
        updateMessMenu();
    }
}
void viewMyBilling(int index) {
    clearStage();
    clearInputBuffer();
    const int x = 30;
    drawBox(x, boxY, 90, 4, "MY BILLING & FEE STATUS");
    gotoxy(x+3, 14);
    generateColors(14);
    cout << left << setw(10) << "ID" 
         << setw(20) << "NAME" 
         << setw(15) << "HOSTEL FEE" 
         << setw(15) << "FEE STATUS" 
         << setw(15) << "MESS BILL" 
         << setw(11) << "TOTAL DUE";
    gotoxy(x+3, 15);
    generateColors(8);
    for (int j = 0; j < WIDTH - 70; j++) cout << "=";
    gotoxy(x+3, 16);
    generateColors(7);
    cout << left << setw(10) << students[index].id
         << setw(20) << students[index].name
         << setw(15) << students[index].fees;
    if (students[index].MessPaid) {
        generateColors(10); cout << left << setw(15) << "Paid";
    } else {
        generateColors(12); cout << left << setw(15) << "Not Paid";
    }
    generateColors(7);
    cout << setw(15) << students[index].MessFees;
    generateColors(14);
    cout << setw(11) << (students[index].fees + students[index].MessFees);
    getch();
}
void viewMyVisitors(int studentID) {
    clearStage();
    clearInputBuffer();
    int x =35;
    drawBox(x, boxY, 85, 10, "MY VISITOR RECORDS");
    gotoxy(x+3, 14);
    generateColors(14);
    cout << left << setw(20) << "VISITOR NAME"
         << setw(20) << "RELATIONSHIP"
         << setw(20) << "TIME IN"
         << setw(20) << "STATUS";
    gotoxy(x+3, 15);
    generateColors(8);
    for (int j = 0; j < 81; j++) cout << "=";
    int rowOffset = 0;
    bool found = false;
    generateColors(7);
    for (int i = 0; i < visitorCount; i++) {
        if (visitor[i].studentIDToVisit == studentID) {
            gotoxy(x+3, 16 + rowOffset);
            cout << left << setw(20) << visitor[i].visitorName
                 << setw(20) << visitor[i].relation
                 << setw(20) << visitor[i].timeIn
                 << setw(20) << "Verified";
            rowOffset++;
            found = true;
        }
    }
    if (!found) {
        gotoxy(50, 17);
        generateColors(12);
        cout << "NO VISITOR RECORDS FOUND!";
    }
    getch();
}
void getVisitorOptions() {
    int choice = 0;
    clearInputBuffer();
    clearStage();
    string s[] = {" [1] Enter a New Visitor"," [2] View Current Visitors"," [3] Visitor Logs"," [4] Search Visitors"," [5] Log Out Visitors "," [6] Exit to Main Menu"};
    mainPrint(choice,s,sizeof(s)/sizeof(string),"Visitor Options");
    getVisitorData();
    if (choice == 0) {
        getVisitor();
    }else if (choice == 1) {
        viewCurrentVisitors();
    }else if (choice == 2) {
        printLog();
    }else if (choice == 3) {
        searchVisitor();
    }else if (choice == 4) {
        checkOutVisitor();
    }
}
void checkOutVisitor() {
     string CNIC;
    clearStage();
    clearInputBuffer();
    drawBox(boxX,boxY,boxWidth,12,"CHECK OUT");
    gotoxy(boxX+3,boxY+2);
    generateColors(10);
    cout << "VISITOR CNIC : ";
    generateColors(INPUT_WHITE);
    cin >> CNIC;
    int foundIndex = -1;
    for (int i = 0; i < visitorCount; i++) {
        if (visitor[i].CNIC == CNIC) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex != -1) {
        gotoxy(boxX+3,boxY+4);
        printColoredWord("Name : ",10);
        printColoredWord(visitor[foundIndex].visitorName,INPUT_WHITE);
        gotoxy(boxX+3,boxY+6);
            printColoredWord("CHECK OUT VISITOR ? :  ",12);
            gotoxy(boxX+12,boxY+8);
            string s[] = {"YES","No"};
            printColoredWord(s[0],498);
            gotoxy(boxX+20,boxY+8);
            printColoredWord(s[1],10);
            int choice = 0;
            while (true) {
                if (GetAsyncKeyState(VK_RIGHT)) {
                    gotoxy(boxX+12,boxY+8);
                    printColoredWord(s[0],10);
                    gotoxy(boxX+20,boxY+8);
                    printColoredWord(s[1],498);
                    choice = 1;
                }
                if (GetAsyncKeyState(VK_LEFT)) {
                    gotoxy(boxX+12,boxY+8);
                    printColoredWord(s[0],498);
                    gotoxy(boxX+20,boxY+8);
                    printColoredWord(s[1],10);
                    choice = 0;
                }
                if (GetAsyncKeyState('F')) {
                    break;
                }
            }
            if (choice == 0) {
                visitor[foundIndex].isStillIn = false;
                time_t now = time(0);
                tm *ltm = localtime(&now);
                char timeBuffer[10];
                for (int i = foundIndex; i < visitorCount -1 ; i++) {
                    visitor[i] = visitor[i+1];
                }
                visitorCount--;
                strftime(timeBuffer, sizeof(timeBuffer), "%H:%M", ltm);
                visitor[foundIndex].timeOut = string(timeBuffer);
                gotoxy(boxX+15,boxY+9);
                generateColors(10);
                slowPrint("Checked Out Visitor ! ",5);
            }
            else if (choice == 1) {
                gotoxy(boxX+15,boxY+9);
                generateColors(WARNING_RED);
                slowPrint("Check Out Failed",5);
            }
    }else {
        generateColors(WARNING_RED);
        gotoxy(boxX+12,boxY+9);
        slowPrint("Invalid CNIC",5);
        gotoxy(boxX+7,boxY+10);
        slowPrint("Returning To Option Menus",5);
    }
    saveVisitors();
    visitorLog(foundIndex);
    clearInputBuffer();
    getch();
}
void searchVisitor() {
    string searchCNIC;
    clearStage();
    drawBox(boxX, boxY, boxWidth, 4, "SEARCH VISITOR");
    gotoxy(boxX + 3, boxY + 2);
    generateColors(10);
    cout << "Enter Visitor CNIC: ";
    generateColors(INPUT_WHITE);
    clearInputBuffer();
    getline(cin, searchCNIC);
    int foundIndex = -1;
    for (int i = 0; i < visitorCount; i++) {
        if (visitor[i].CNIC == searchCNIC) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex != -1) {
        clearStage();
        drawBox(2, boxY, WIDTH - 10, 6, "VISITOR SEARCH RESULT");

        gotoxy(5, 14);
        generateColors(14);
        cout << left << setw(20) << "NAME"
             << setw(18) << "CNIC"
             << setw(10) << "S.ID"
             << setw(15) << "RELATION"
             << setw(10) << "IN"
             << setw(10) << "OUT"
             << setw(15) << "STATUS";
        gotoxy(5, 15);
        generateColors(8);
        for (int j = 0; j < WIDTH - 15; j++) cout << "=";
        gotoxy(5, 16);
        generateColors(15);
        cout << left << setw(20) << visitor[foundIndex].visitorName
             << setw(18) << visitor[foundIndex].CNIC
             << setw(10) << visitor[foundIndex].studentIDToVisit
             << setw(15) << visitor[foundIndex].relation
             << setw(10) << visitor[foundIndex].timeIn
             << setw(10) << visitor[foundIndex].timeOut;
        if (visitor[foundIndex].isStillIn) {
            printColoredWord("Still Inside", 10);
        } else {
            printColoredWord("Checked Out", 12);
        }
        getch();
    } else {
        gotoxy(boxX + 8, boxY + 5);
        printColoredWord("No Visitor Found with that CNIC!", 12);
        getch();
    }
}
void viewCurrentVisitors() {
    clearStage();
    clearInputBuffer();
    generateColors(10);

    int activeCount = 0;
    for (int i = 0; i < visitorCount; i++) {
        if (visitor[i].isStillIn == true) {
            activeCount++;
        }
    }
    drawBox(10, boxY, WIDTH - 20, activeCount + 6, "CURRENT VISITORS");
    gotoxy(13, 14);
    generateColors(14);
    cout << left << setw(10) << "S.ID"
         << setw(20) << "VISITOR NAME"
         << setw(20) << "CNIC"
         << setw(15) << "RELATION"
         << setw(12) << "IN TIME"
         << setw(15) << "STATUS";
    gotoxy(13, 15);
    generateColors(8);
    for (int j = 0; j < 92; j++)
        cout << "═";

    int rowOffset = 0;
    for (int i = 0; i < visitorCount; i++) {
        if (visitor[i].isStillIn == true) {
            gotoxy(13, 16 + rowOffset);
            generateColors(7);
            cout << left << setw(10) << visitor[i].studentIDToVisit
                 << setw(20) << visitor[i].visitorName
                 << setw(20) << visitor[i].CNIC
                 << setw(15) << visitor[i].relation
                 << setw(12) << visitor[i].timeIn;
            printColoredWord("INSIDE", 10);
            rowOffset++;
        }
    }
    if (activeCount == 0) {
        gotoxy(13, 16);
        printColoredWord("NO ACTIVE VISITORS CURRENTLY IN HOSTEL.", 12);
    }
    getch();
}
void printLog() {
    ifstream logFile("visitorsLog.txt");
    int counter = 0;
    string dummy;
    while (getline(logFile, dummy)) {
        counter++;
    }
    logFile.close();
    int totalPages = (counter + 19) / 20;
    if (totalPages == 0) totalPages = 1;
    int currentPage = 1;
    while (true) {
        clearStage();
        drawBox(2, boxY, WIDTH - 10, 25, "VISITOR LOG");
        generateColors(14);
        gotoxy(5, 14);
        cout << left << setw(30) << "VISITOR NAME" << setw(30) << "CNIC"
             << setw(15) << "IN TIME" << setw(15) << "OUT TIME";
        gotoxy(5, 15);
        generateColors(8);
        for (int j = 0; j < 90; j++) cout << "═";
        gotoxy(2, boxY - 2);
        printColoredWord("LEFT/RIGHT ARROW: Navigate | ESC: Exit", 15);
        gotoxy(135, boxY - 2);
        printColoredWord("PAGE " + to_string(currentPage) + " / " + to_string(totalPages), 14);
        logSupport((currentPage - 1) * 20);
        bool redraw = false;
        while (!redraw) {
            if (GetAsyncKeyState(VK_RIGHT)) {
                if (currentPage < totalPages) {
                    currentPage++;
                    redraw = true;
                }
            }
            if (GetAsyncKeyState(VK_LEFT)) {
                if (currentPage > 1) {
                    currentPage--;
                    redraw = true;
                }
            }
            if (GetAsyncKeyState(VK_ESCAPE)) {
                return;
            }
            Sleep(300);
        }
    }
}
void logSupport(int startFrom) {
    ifstream logFile("visitorsLog.txt");
    string line, name, cnic, timeIn, timeOut;
    for (int i = 0; i < startFrom; i++) {
        getline(logFile, line);
    }
    int row = 0;
    while (row < 20 && getline(logFile, line)) {
        stringstream ss(line);
        getline(ss, name, '|');
        getline(ss, cnic, '|');
        getline(ss, timeIn, '|');
        getline(ss, timeOut, '|');
        gotoxy(5, 16 + row);
        generateColors(7);
        cout << left << setw(30) << name
             << setw(30) << cnic
             << setw(15) << timeIn
             << setw(15) << timeOut;
        row++;
    }
    logFile.close();
}
void getVisitorData() {
    visitorFile.open("visitor.txt", ios::in);
    if (!visitorFile) return;
    visitorFile >> visitorCount;
    visitorFile.ignore();
    string temp;
    for (int i = 0; i < visitorCount; i++) {
        getline(visitorFile, visitor[i].visitorName, '|');
        getline(visitorFile, visitor[i].CNIC, '|');
        getline(visitorFile, temp, '|');
        if(!temp.empty()) visitor[i].studentIDToVisit = stoi(temp);
        getline(visitorFile, visitor[i].relation, '|');
        getline(visitorFile, visitor[i].timeIn, '|');
        getline(visitorFile, visitor[i].timeOut, '|');
        getline(visitorFile, temp, '\n');
        visitor[i].isStillIn = (temp == "1");
        visitorFile >> ws;
    }
    visitorFile.close();
}
void visitorLog(int index) {
    ofstream outFile("visitorsLog.txt", ios::app);
    outFile << visitor[index].visitorName << "|"
            <<visitor[index].CNIC << "|"
            << visitor[index].timeIn << "|"
            << visitor[index].timeOut << "\n";
    outFile.close();
}
void saveVisitors() {
    visitorFile.open("visitor.txt", ios::out);
    visitorFile << visitorCount << "\n";
    for (int i = 0; i < visitorCount; i++) {
        visitorFile << visitor[i].visitorName << "|"
                    << visitor[i].CNIC << "|"
                    << visitor[i].studentIDToVisit << "|"
                    << visitor[i].relation << "|"
                    << visitor[i].timeIn << "|"
                    << visitor[i].timeOut << "|"
                    << visitor[i].isStillIn << "\n";
    }
    visitorFile.close();
}
void getVisitor() {
    clearStage();
    clearInputBuffer();
    drawBox(boxX, boxY, boxWidth, 11, "ADD NEW VISITOR");
    string s[] = {"ENTER VISITOR NAME: ","ENTER VISITOR CNIC: ","ENTER STUDENT ID TO VISIT: ","RELATIONSHIP TO STUDENT: "};
    int k = 2;
    for (const string i : s ) {
        gotoxy(boxX + 3, boxY + k);
        generateColors(10);
        cout << i;
        k +=2;
    }
    generateColors(INPUT_WHITE);
    gotoxy(boxX+23,boxY+2);
    getline(cin >> ws, visitor[visitorCount].visitorName);
    gotoxy(boxX + 22, boxY + 4);
    string cnic;
    getline(cin, cnic);
    for (int i = 0 ; i < visitorCount; i++) {
        if (cnic == visitor[i].CNIC) {
            gotoxy(boxX + 3, boxY + 10);
            printColoredWord("CNIC ALREADY EXIST",WARNING_RED);
            clearInputBuffer();
            getch();
            return;
        }
    }
    visitor[visitorCount].CNIC = cnic;
    gotoxy(boxX + 28, boxY + 6);
    int id;
    cin >> id;
    if (searchStudent(id) == -1) {
        gotoxy(boxX + 3, boxY + 10);
        printColoredWord("No Student Found!",WARNING_RED);
        clearInputBuffer();
        getch();
        return;
    }
    visitor[visitorCount].studentIDToVisit = id;
    gotoxy(boxX + 28, boxY + 8);
    getline(cin >> ws, visitor[visitorCount].relation);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timeBuffer[10];
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M", ltm);
    visitor[visitorCount].timeIn = string(timeBuffer);
    visitor[visitorCount].isStillIn = true;
    visitor[visitorCount].timeOut = "N/A";
    visitorLog(visitorCount);
    visitorCount++;
    saveVisitors();
    gotoxy(boxX + 3, boxY + 10);
    printColoredWord("Added Visitor!",10);
    getch();
}
void printAdminOptions(int selected,int &choice) {
    string Options[] = {" [1] Student Management"," [2] Room Management"," [3] Fee Management"," [4] Visitor Options"," [5] Mess Options"," [6] Exit"};
    drawBox(48,13,40,7,"Admin Menu");
    printMenu(Options,sizeof(Options)/sizeof(string),selected,"Menu");
    getMainChoice(choice,Options,sizeof(Options)/sizeof(string));
}
void viewMyProfile(int ID) {
    clearStage();
    clearInputBuffer();
    drawBox(12,boxY,WIDTH-25,4,"SEARCH RESULT");
    gotoxy(15,14);
    generateColors(14);
    cout << left <<setw(5)<< "ID" << setw(20)<< "NAME" << setw(20)<< "PHONE"<<setw(14) <<"ROOM.NO"<<setw(10)<<"FEE"<<setw(15)<<"Fees Status"<<setw(20)<<"LMS Email"<<setw(15)<<"LMS password";
    gotoxy(15,15);
    generateColors(8);
    for (int j=0 ; j <WIDTH-30;j++ )
        cout << "=";
    gotoxy(15,16);
    generateColors(7);
    cout << left << setw(5) << students[ID].id
         << setw(20) << students[ID].name
         << setw(20) << students[ID].studentPhone
         << setw(14) << students[ID].roomID
         << setw(10) << students[ID].fees
         << setw(15) << (students[ID].feesPaid?"Paid":"Not Paid")
         << setw(20) << students[ID].email
         << setw(15) << students[ID].password
         << endl;
    getch();
}
void viewMyRoom(int index) {
    clearStage();
    clearInputBuffer();
    int room_idx = students[index].roomID;
    drawBox(boxX,boxY,50,4,"MY ROOM");
    if (room_idx != 0) {
        gotoxy(boxX+3,boxY+1);
        generateColors(14);
        cout << left <<setw(10)<<"RoomID"<< setw(15)<<"Student 1 "<<setw(15)<<" Student 2"<<endl;
        gotoxy(boxX+3,boxY+2);
        generateColors(8);
        for (int j = 0; j < 45; j++) cout << "═";
        gotoxy(boxX+3,boxY+3);
        generateColors(7);
        cout << left <<setw(10)<<students[index].roomID
             << setw(15)<<room[room_idx - 1].StudentID1
             << setw(15)<<room[room_idx - 1].StudentID2
             << endl;
        int roommateID = 0;
        if (room[room_idx - 1].StudentID1 == index) {
            roommateID = room[room_idx - 1].StudentID2;
        } else if (room[room_idx - 1].StudentID2 == index) {
            roommateID = room[room_idx - 1].StudentID1;
        }
        if (roommateID != 0) {
            int roommateIndex = searchStudent(roommateID);
            if (roommateIndex != -1) {
                drawBox(boxX,boxY+4,50,4,"ROOMMATE DETAILS");
                gotoxy(boxX+3,boxY+5);
                generateColors(14);
                cout << left <<setw(5)<< "ID" << setw(20)<< "NAME" << setw(20)<< "PHONE"<<setw(14) <<"ROOM.NO";
                gotoxy(boxX+3,boxY+6);
                generateColors(8);
                for (int j=0 ; j <WIDTH-15;j++ )
                    cout << "=";
                gotoxy(boxX+3,boxY+7);
                cout << left << setw(5) << students[roommateIndex].id
                     << setw(20) << students[roommateIndex].name
                     << setw(20) << students[roommateIndex].studentPhone
                     << setw(14) << students[roommateIndex].roomID
                     << endl;
                clearInputBuffer();
                getch();
            } else {
                gotoxy(boxX+3,boxY+7);
                generateColors(4);
                printColoredWord("Roommate ID found, but profile is missing.", 12);
            }
        } else {
            gotoxy(boxX+3,boxY+7);
            generateColors(4);
            cout << "Your room is currently empty (no roommate).";
        }
    }else {
        gotoxy(boxX+7,boxY+3);
        generateColors(4);
        cout << "No ROOM ASSIGNED";
    }
    clearInputBuffer();
    getch();
}
void viewMyFeeStatus(int index) {
    clearStage();
    clearInputBuffer();
    drawBox(43,boxY,50,4,"FEES DUE");
    gotoxy(46,14);
    generateColors(14);
    cout << left <<setw(5)<< "ID" << setw(20)<< "NAME" <<setw(10)<<"FEE DUE"<<setw(11)<<"Fees Status";
    // gotoxy(46,15);
    // for (int j = 0 ; j <48;j++ )
    //     cout << "=";
    gotoxy(46,16);
    generateColors(7);
    cout << left << setw(5) << students[index].id
             << setw(20) << students[index].name
             << setw(10) << students[index].fees;
    if (students[index].feesPaid == true) {
        generateColors(10);
    }else {
        generateColors(4);
    }
    cout << setw(11) << (students[index].feesPaid?"Paid":"Not Paid");
    getch();
}
void getStudentLogin(bool &access,int &ID) {
    clearStage();
    clearInputBuffer();
    int startX = boxX, startY = boxY;
    int width = 40, height = 10;
    drawBox(startX, startY, width, height, "STUDENT SECURE ACCESS");
    generateColors(INPUT_WHITE);
    gotoxy(startX + 4, startY + 3); cout << "EMAIL: ";
    gotoxy(startX + 4, startY + 5); cout << "PASSWORD: ";
    generateColors(8);
    gotoxy(startX + 14, startY + 3); cout << "____________________";
    gotoxy(startX + 14, startY + 5); cout << "____________________";
    string user, pass;
    generateColors(15);
    gotoxy(startX + 14, startY + 3);
    cin >> user;
    gotoxy(startX + 14, startY + 5);
    clearInputBuffer();
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) {
            break;
        }
        else if (ch == 8) {
            if (pass.length() > 0) {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == 32 || ch == 0 || ch == 224) {

            continue;
        }
        else {
            pass += ch;
            cout << '*';
        }
    }
    for ( int i = 0; i < studentsCount ; i++) {
        if (students[i].email == user && students[i].password == pass) {
            access = true;
            ID = i;
            break;
        }
    }
    if (access) {
        gotoxy(startX + 10, startY + 8);
        generateColors(10);
        slowPrint("ACCESS GRANTED! Welcome.",3);
    } else {
        gotoxy(startX + 8, startY + 8);
        access = false;
        generateColors(WARNING_RED);
        slowPrint("ACCESS DENIED. Try again.",3);
    }
    Sleep(2000);
}
void studentChoice(int &choice) {
    system("cls");
    printHeading();
    string Options[] = {" [1] My Profile"," [2] Room Details"," [3] Fee Status"," [4] View Mess Menu"," [5] My Mess Bill"," [6] My Visitor History"," [7] Logout"};
    drawBox(48,13,40,9,"Student Menu");
    printMenu(Options,sizeof(Options)/sizeof(string),0,"Menu");
    getMainChoice(choice,Options,sizeof(Options)/sizeof(string));
}
void viewMessMenu() {
    clearStage();
    clearInputBuffer();
    fstream mess;
    mess.open("mes.txt",ios::out);
    string temp;
    drawBox(boxX, boxY, boxWidth, 11, "TODAY'S MESS MENU");
    generateColors(14);
    gotoxy(boxX + 3, boxY + 3);  cout << "BREAKFAST:";
    gotoxy(boxX + 3, boxY + 5);  cout << "LUNCH:";
    gotoxy(boxX + 3, boxY + 7);  cout << "DINNER:";
    generateColors(7);
    getline(mess,temp,'|');
    gotoxy(boxX + 15, boxY + 3); cout << temp;
    getline(mess,temp,'|');
    gotoxy(boxX + 15, boxY + 5); cout << temp;
    getline(mess,temp,'\n');
    gotoxy(boxX + 15, boxY + 7); cout << temp;
    gotoxy(boxX + 3, boxY + 10);
    generateColors(11);
    mess.close();
    cout << "Press any key to return...";
    getch();
}
void getStudentChoice() {
    int studentChoice = 0;
    clearStage();
    string s [] = {" [1] Add Student       "," [2] Search Student  "," [3] View All Students"," [4] Edit Student"," [5] Delete Student"," [6] Back to Main Menu "};
    mainPrint(studentChoice,s,6,"Student Menu");
    if (studentChoice == 0) {
        addStudent();
    }else if (studentChoice == 1) {
        searchRecord();
    }
    else if (studentChoice == 2) {
        viewStudents();
    }else if (studentChoice == 3) {
        editStudent();
    }else if (studentChoice == 4) {
        deleteStudent();
    }
}
void searchRecord() {
    int ID;
    clearStage();
    drawBox(boxX,boxY,boxWidth,4,"SEARCH");
    gotoxy(50,14);
    generateColors(10);
    clearInputBuffer();
    cout << "Enter Student ID : ";
    generateColors(INPUT_WHITE);
    cin >> ID;
    ID = searchStudent(ID);
    if (ID != -1) {
        clearStage();
        clearInputBuffer();
        drawBox(2,boxY,WIDTH-10,4,"SEARCH RESULT");
        gotoxy(5,14);
        generateColors(10);
        cout << left <<setw(5)<< "ID" << setw(20)<< "NAME" << setw(20)<< "PHONE"<<setw(14) <<"ROOM.NO"<<setw(10)<<"FEE"<<setw(15)<<"Fees Status"<<setw(20)<<"LMS Email"<<setw(15)<<"LMS password";
        gotoxy(5,15);
        for (int j=0 ; j <WIDTH-15;j++ )
            cout << "=";
        gotoxy(5,16);
        cout << left << setw(5) << students[ID].id
             << setw(20) << students[ID].name
             << setw(20) << students[ID].studentPhone
             << setw(14) << students[ID].roomID
             << setw(10) << students[ID].fees
             << setw(15) << (students[ID].feesPaid?"Paid":"Not Paid")
             << setw(20) << students[ID].email
             << setw(15) << students[ID].password
             << endl;
        getch();
    }else {
        gotoxy(60,15);
        printColoredWord("No Student Found!",12);
        getch();
    }
}
void addStudent() {
    clearStage();
    clearInputBuffer();
    string s[] = {"Student ID : ","Name : ","Phone Number : ","Set Password : "};
    drawBox(boxX,boxY,boxWidth,13,"ADD STUDENT DETAILS");
    int j = 3;
    generateColors(10);
    for (const string& i : s) {
        gotoxy(boxX+3,boxY+j);
        cout << i;
        j += 2;
    }
    int ID;
    gotoxy(boxX+17,boxY+3);
    cin >> ID;
    students[studentsCount].id = ID;
    while (searchStudent(ID)!=-1) {
        gotoxy(boxX+27,boxY+12);
        generateColors(WARNING_RED);
        cout << "INVALID ID";
        generateColors(10);
        gotoxy(boxX+17,boxY+3);
        cout << "       ";
        cin.ignore();
        gotoxy(boxX+17,boxY+3);
        cin >> ID;
        students[studentsCount].id = ID;
    }
    cin.ignore();
    gotoxy(boxX+17,boxY+5);
    getline(cin,students[studentsCount].name);
    gotoxy(boxX+17,boxY+7);
    cin >> students[studentsCount].studentPhone;
    gotoxy(boxX+17,boxY+9);
    cin >> students[studentsCount].password;
    students[studentsCount].email = (to_string(students[studentsCount].id)+"@uet.edu.pk");
    studentsCount++;
    addData();
}
void viewStudents() {
    clearStage();
    clearInputBuffer();
    generateColors(10);
    drawBox(2,boxY,WIDTH-10,studentsCount + 3,"SEARCH RESULT");
    gotoxy(3,14);
    generateColors(10);
    cout << left <<setw(5)<< "ID" << setw(20)<< "NAME" << setw(20)<< "PHONE"<<setw(14) <<"ROOM.NO"<<setw(10)<<"FEE"<<setw(15)<<"Fees Status"<<setw(20)<<"LMS Email"<<setw(15)<<"LMS password";
    gotoxy(3,15);
    for (int j=0 ; j <WIDTH-15;j++ )
        cout << "=";
    for (int i = 0; i < studentsCount; i++) {
        gotoxy(3,15+i+1);
        cout << left << setw(5) << students[i].id
             << setw(20) << students[i].name
             << setw(20) << students[i].studentPhone
             << setw(14) << students[i].roomID
             << setw(10) << students[i].fees
             << setw(15) << (students[i].feesPaid?"Paid":"Not Paid")
             << setw(20) << students[i].email
             << setw(15) << students[i].password;
    }
    getch();
}
void editStudent() {
    clearStage();
    clearInputBuffer();
    drawBox(boxX,boxY,boxWidth,13,"EDIT STUDENT DETAILS");
    int ID;
    gotoxy(boxX+3,boxY+2);
    printColoredWord("Enter ID : ",10);
    generateColors(INPUT_WHITE);
    cin >> ID;
    ID = searchStudent(ID);
    if (ID != -1) {
        gotoxy(boxX+3,boxY+4);
        printColoredWord("Enter New Student ID :",10);
        cin >> students[ID].id;
        gotoxy(boxX+3,boxY+6);
        printColoredWord("Enter New Student Name :",10);
        cin.ignore();
        getline(cin,students[ID].name);
        gotoxy(boxX+3,boxY+8);
        printColoredWord("Enter New Student Phone Number : ",10);
        cin >> students[ID].studentPhone;
        students[ID].fees = 0;
        students[ID].feesPaid = false;
        gotoxy(boxX+5,boxY+11);
        generateColors(10);
        slowPrint("EDITED SUCCESSFULLY!",6);
    }else {
        gotoxy(boxX+5,boxY+11);
        printColoredWord("INVALID ID",WARNING_RED);
    }
    addData();
    getch();
}
int searchStudent(int ID) {
    for (int i = 0; i < studentsCount; i++) {
        if (students[i].id == ID) {
            return i;
        }
    }
    return -1;
}
void deleteStudent() {
    clearStage();
    clearInputBuffer();
    drawBox(boxX,boxY,boxWidth,5,"DELETE STUDENT DETAILS");
    gotoxy(boxX+3,boxY+2);
    printColoredWord("Enter ID : ",10);
    generateColors(INPUT_WHITE);
    int ID;
    cin >> ID;
    ID = searchStudent(ID);
    if (ID != -1) {
        if (students[ID].roomID != 0 ) {
            if (students[ID].id == room[students[ID].roomID-1].StudentID1) {
                room[students[ID].roomID-1].StudentID1 = 0;
            }else {
                room[students[ID].roomID-1].StudentID2 = 0;
            }
        }
        for (int i = ID; i < studentsCount -1 ; i++) {
            students[i] = students[i+1];
        }
        studentsCount--;
    }else {
        gotoxy(boxX+3,boxY+4);
        printColoredWord("Invalid ID",WARNING_RED);
    }
    addData();
    getch();
}
void mainPrint(int &choice,string s[],const int rows,const string title) {
    drawBox(boxX,boxY,boxWidth,rows+2,title);
    printMenu(s,rows,0,title);
    getMainChoice(choice,s,rows);
}
void getRoomChoice() {
    string s[] =  {" [1] Assign Room"," [2] View Rooms"," [3] Edit Rooms"," [4] Main Menu "};
    int choice = 0;
    clearStage();
    mainPrint(choice,s,4,"Rooms");
    if (choice == 0) {
        assignRoom();
    }else if (choice == 1) {
        viewRooms();
    }else if (choice == 2) {
        editRoom();
    }
}
void UpdateRoom() {
    studentFile.open("MAINROOMS.txt",ios::out);
    for (int i = 0;i < 50 ; i++) {
        studentFile << i << "|" << room[i].StudentID1 << "|" << room[i].StudentID2 << "\n";
    }
    studentFile.close();
}
void assignRoom() {
    clearStage();
    clearInputBuffer();
    int roomID;
    drawBox(boxX,boxY,boxWidth,7,"Assign Room");
    gotoxy(boxX+3,boxY+2);
    generateColors(10);
    cout << "Enter Room To Assign (1-50) : ";
    generateColors(INPUT_WHITE);
    cin >> roomID;
    if (roomID >=1 && roomID <= 50) {
        roomID--;
        int stID;
        gotoxy(boxX+3,boxY+4);
        generateColors(10);
        cout << "Enter Student ID : ";
        generateColors(INPUT_WHITE);
        cin >> stID;
        const int copy = stID;
        stID = searchStudent(stID);
        if (stID != -1 && students[stID].roomID == 0 ) {
            if (room[roomID].StudentID1==0) {
                room[roomID].StudentID1 = (copy);
                students[stID].roomID = (roomID+1);
                gotoxy(boxX+6,boxY+6);
                printColoredWord("Room Assigned!",10);
            }else if (room[roomID].StudentID2==0) {
                room[roomID].StudentID2 = (copy);
                students[stID].roomID = (roomID+1);
                gotoxy(boxX+6,boxY+6);
                printColoredWord("Room Assigned!",10);
            }else {
                gotoxy(boxX+6,boxY+6);
                printColoredWord("Room Is FUll",WARNING_RED);
            }
        }else {
            gotoxy(boxX+1,boxY+6);
            printColoredWord("Invalid Student ID OR Room Has Already Assigned",WARNING_RED);
        }
    }else {
        gotoxy(boxX+6,boxY+6);
        printColoredWord("Invalid Room ID",WARNING_RED);
    }
    addData();
    UpdateRoom();
    getch();
}
void viewRoomSupport(int l,int k) {
    int Y = 14;
    for (int i = 0; i< 5 ; i++) {
        Y+=2;
        gotoxy(3,Y);
        for (int j = 0 ; j < 5 ; j++) {
            generateColors(8);
            cout <<"    " << "ROOM NO : ";printColoredWord(to_string(l+1),14);cout <<left<< "          |";
            l++;
        }
        Y ++;
        gotoxy(3,Y);
        for (int j = 0 ; j < 5 ; j++) {
            generateColors(11);
            cout <<"  STD 1 : "+to_string(room[k].StudentID1)+" : "+"STD 2 : "+to_string(room[k].StudentID2)+"   |";
            k++;
        }
    }

}
void viewRooms() {
    clearStage();
    drawBox(2,boxY,WIDTH-7,25,"View Rooms");
    viewRoomSupport(0,0);
    gotoxy(2,boxY-2);
    printColoredWord("PRESS LEFT OR RIGHT ARROW TO VIEW NEXT PAGE OR PRESS ESCAPE KEY TO EXIT",15);
    gotoxy(135,boxY-2);
    printColoredWord("PAGE 1 / 2",14);
    int choice = 0;
    while (true) {
        if (GetAsyncKeyState(VK_RIGHT)) {
            if (choice == 0) {
                choice = 1;
                gotoxy(135,boxY-2);
                printColoredWord("PAGE 2 / 2",14);
                viewRoomSupport(25,25);
            }
        }
        if (GetAsyncKeyState(VK_LEFT)) {
            if (choice == 1) {
                choice = 0;
                gotoxy(135,boxY-2);
                printColoredWord("PAGE 1 / 2",14);
                viewRoomSupport(0,0);
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
        Sleep(1000);
    }
}
void editRoom() {
    clearStage();
    clearInputBuffer();
    drawBox(boxX,boxY,boxWidth,13,"Edit Room");
    gotoxy(boxX+3,boxY+2);
    generateColors(10);
    cout << "Enter Room ID(1-50) : ";
    generateColors(INPUT_WHITE);
    int roomID;
    cin >> roomID;
    if (roomID>=1 && roomID <= 50) {
        gotoxy(boxX+1,boxY+4);
        generateColors(15);
        cout << "RoomID\tStudent 1 \t Student 2"<<endl;
        gotoxy(boxX+1,boxY+5);
        cout << roomID<< "\t";
        cout << room[roomID-1].StudentID1 << "\t";
        cout << room[roomID-1].StudentID2 << "\t";
        int st1,st2;
        gotoxy(boxX+1,boxY+7);
        generateColors(10);
        cout << "Enter Student 1 ID : ";
        generateColors(INPUT_WHITE);
        cin >> st1;
        int index = searchStudent(st1);
        if (index != -1 ) {
            room[students[index].roomID-1].StudentID1 = 0;
            students[index].roomID = 0;
            room[roomID-1].StudentID1 = (st1);
            gotoxy(boxX+1,boxY+9);
            generateColors(10);
            cout << "Enter Student 2 ID : ";
            generateColors(INPUT_WHITE);
            cin >> st2;
            index = searchStudent(st2);
            if (index != -1) {
                room[students[index].roomID-1].StudentID2 = 0;
                students[index].roomID = 0;
                room[roomID-1].StudentID2 = (st2);
            }else {
                gotoxy(boxX+5,boxY+11);
                printColoredWord("Invalid Student ID",WARNING_RED);
            }
        }else {
            gotoxy(boxX+5,boxY+11);
            printColoredWord("Invalid Student ID",WARNING_RED);
        }
    }else {
        gotoxy(boxX+5,boxY+11);
        printColoredWord("Invalid Room ID",WARNING_RED);
    }
    UpdateRoom();
    clearInputBuffer();
    getch();
}
void getFeesChoice() {
    int choice = 0;
    clearStage();
    string s[] =  {" [1] Assign Fees"," [2] Mark Fee Paid"," [3] View Fee Status"," [4] View All Unpaid Students"," [5] Back To Main Menu"};
    mainPrint(choice,s,5,"Fees Menu");
    if (choice == 0) {
        assignFees();
    }else if (choice == 1) {
        markPaid();
    }else if ( choice == 2) {
        viewFeeStatus();
    }else if (choice == 3) {
        unpaidList();
    }
}
void assignFees() {
    clearStage();
    printHeading();
    int ID;
    clearInputBuffer();
    drawBox(boxX,boxY,boxWidth,9,"ADD STUDENT DETAILS");
    int j = 3;
    generateColors(10);
    const string s[] = {"Student ID : ","Assign Fees : "};
    for ( const string& i : s){
        gotoxy(boxX+3,boxY+j);
        cout << i;
        j += 2;
    }
    generateColors(INPUT_WHITE);
    gotoxy(boxX+17,boxY+3);
    cin >> ID;
    ID = searchStudent(ID);
    if (ID != -1) {
        gotoxy(boxX+17,boxY+5);
        int fees;
        do {
            cin >> fees;
            students[ID].fees = fees;
        }while (fees <= 10);
        gotoxy(boxX+6,boxY+8);
        slowPrint("Fees Assigned Successfully!",5);
    }else {
        gotoxy(boxX+6,boxY+7);
        generateColors(WARNING_RED);
        cout << "INVALID STUDENT ID.";
        gotoxy(boxX+17,boxY+8);
        cout << "RETURNING TO MAIN MENU";
    }
    addData();
    getch();
}
void markPaid() {
    int ID;
    clearStage();
    clearInputBuffer();
    drawBox(boxX,boxY,boxWidth,12,"Update Fees Status");
    gotoxy(boxX+3,boxY+2);
    generateColors(10);
    cout << "Student ID : ";
    generateColors(INPUT_WHITE);
    cin >> ID;
    ID = searchStudent(ID);
    if (ID != -1) {
        gotoxy(boxX+3,boxY+4);
        printColoredWord("Name : ",10);
        printColoredWord(students[ID].name,INPUT_WHITE);
        gotoxy(boxX+3,boxY+6);
        printColoredWord("Fees Due : ",10);
        if (students[ID].fees == 0) {
            printColoredWord("Not Yet Assigned",WARNING_RED);
        }else {
            printColoredWord(to_string(students[ID].fees),INPUT_WHITE);
            gotoxy(boxX+10,boxY+7);
            printColoredWord("Mark Fees Paid ? :  ",12);
            gotoxy(boxX+12,boxY+8);
            string s[] = {"YES","No"};
            printColoredWord(s[0],498);
            gotoxy(boxX+20,boxY+8);
            printColoredWord(s[1],10);
            int choice = 0;
            while (true) {
                if (GetAsyncKeyState(VK_RIGHT)) {
                    gotoxy(boxX+12,boxY+8);
                    printColoredWord(s[0],10);
                    gotoxy(boxX+20,boxY+8);
                    printColoredWord(s[1],498);
                    choice = 1;
                }
                if (GetAsyncKeyState(VK_LEFT)) {
                    gotoxy(boxX+12,boxY+8);
                    printColoredWord(s[0],498);
                    gotoxy(boxX+20,boxY+8);
                    printColoredWord(s[1],10);
                    choice = 0;
                }
                if (GetAsyncKeyState('F')) {
                    break;
                }
            }
            if (choice == 0) {
                students[ID].feesPaid = true;
                gotoxy(boxX+15,boxY+9);
                generateColors(10);
                slowPrint("Marked Fees Paid ! ",5);
            }
            else if (choice == 1) {
                students[ID].feesPaid = false;
                gotoxy(boxX+15,boxY+9);
                generateColors(WARNING_RED);
                slowPrint("Updating Failed",5);
            }
        }
    }else {
        generateColors(WARNING_RED);
        gotoxy(boxX+12,boxY+9);
        slowPrint("Invalid Student ID",5);
        gotoxy(boxX+7,boxY+10);
        slowPrint("Returning To Option Menus",5);
    }
    addData();
    clearInputBuffer();
    getch();
}
void viewFeeStatus() {
    int ID;
    clearStage();
    drawBox(boxX,boxY,boxWidth,4,"SEARCH");
    gotoxy(boxX+3,boxY+2);
    generateColors(10);
    clearInputBuffer();
    cout << "Enter Student ID : ";
    generateColors(INPUT_WHITE);
    cin >> ID;
    ID = searchStudent(ID);
    if (ID != -1) {
        clearStage();
        drawBox(20,boxY,WIDTH-60,4,"SEARCH RESULT");
        gotoxy(23,14);
        generateColors(10);
        cout << left <<setw(5)<< "ID" << setw(20)<< "NAME" << setw(20)<< "PHONE"<<setw(10)<<"FEE"<<setw(15)<<"Fees Status"<<setw(20);
        gotoxy(23,15);
        for (int j = 0 ; j <WIDTH-80;j++ )
            cout << "=";
        gotoxy(23,16);
        cout << left << setw(5) << students[ID].id
             << setw(20) << students[ID].name
             << setw(20) << students[ID].studentPhone
             << setw(10) << students[ID].fees
             << setw(15) << (students[ID].feesPaid?"Paid":"Not Paid")
             << endl;
        getch();
    }else {
        gotoxy(60,15);
        printColoredWord("No Student Found!",WARNING_RED);
        getch();
    }
}
void unpaidList() {
    clearStage();
    clearInputBuffer();
    generateColors(10);
    int unpaidCount = 0;
    for (int i = 0 ; i < studentsCount ; i++) {
        if (students[i].feesPaid == false) {
            unpaidCount++;
        }
    }
    drawBox(20,boxY,WIDTH-60,unpaidCount + 3,"UNPAID LIST");
    gotoxy(23,14);
    generateColors(10);
    cout << left <<setw(5)<< "ID" << setw(20)<< "NAME" << setw(20)<< "PHONE"<<setw(10)<<"FEE"<<setw(15)<<"Fees Status"<<setw(20);
    gotoxy(23,15);
    for (int j=38 ; j <WIDTH-70;j++ )
        cout << "=";
    int currentY=16;
    for (int i = 0; i < studentsCount ; i++) {
        if (students[i].feesPaid == false) {
            gotoxy(23,currentY);
            cout << left << setw(5) << students[i].id
                 << setw(20) << students[i].name
                 << setw(20) << students[i].studentPhone
                 << setw(10) << students[i].fees;
                 printColoredWord("Unpaid",WARNING_RED);
            currentY++;
        }
    }
    getch();
}
void generateColors(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}
void printColoredWord(string text, int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1. Get the current console attributes (the default color)
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD savedAttributes = consoleInfo.wAttributes;

    // 2. Set the custom color (Light Red, in this case)
    SetConsoleTextAttribute(hConsole, colorCode);

    // 3. Print the text (Crucially, NO endl here)
    cout << text;

    // 4. Reset the color back to the saved default
    SetConsoleTextAttribute(hConsole, savedAttributes);
}
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}