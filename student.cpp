#include <iostream>
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
    cin >> marks;
}

void Student::display() {
    cout << "Roll No: " << rollNo
         << ", Name: " << name
         << ", Branch: " << branch
         << ", Marks: " << marks << endl;
}

int Student::getRollNo() {
    return rollNo;
}

float Student::getMarks() {
    return marks;
}
