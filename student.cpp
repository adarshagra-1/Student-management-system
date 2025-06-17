#include <iostream>
#include <ctime>
#include "student.h"
using namespace std;

void Student::input() {
    cout << "Enter Roll No: ";
    cin >> rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Branch: ";
    getline(cin, branch);
    cout << "Enter Marks: ";
    while (!(cin >> marks) || marks < 0 || marks > 100) {
        cout << "Invalid marks. Enter again (0-100): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    time_t now = time(0);
    createdAt = ctime(&now);
    createdAt.pop_back();
}

void Student::display() {
    cout << "Roll No: " << rollNo
         << ", Name: " << name
         << ", Branch: " << branch
         << ", Marks: " << marks
         << ", Created At: " << createdAt << endl;
}

int Student::getRollNo() {
    return rollNo;
}

float Student::getMarks() {
    return marks;
}
