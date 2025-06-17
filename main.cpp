#include <iostream>
#include <fstream>
#include <cstdio>  // for remove, rename
#include <vector>
#include <algorithm>
#include "student.h"

using namespace std;

bool login() {
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "1234") {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid credentials!\n";
        return false;
    }
}

void addStudent() {
    Student s;
    ofstream fout("students.txt", ios::app | ios::binary);
    s.input();
    fout.write((char*)&s, sizeof(s));
    fout.close();
    cout << "Student added!\n";
}

void displayStudents() {
    Student s;
    ifstream fin("students.txt", ios::in | ios::binary);
    while (fin.read((char*)&s, sizeof(s))) {
        s.display();
    }
    fin.close();
}

void searchStudent() {
    int targetRollNo;
    cout << "Enter Roll No to search: ";
    cin >> targetRollNo;

    Student s;
    bool found = false;
    ifstream fin("students.txt", ios::in | ios::binary);
    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == targetRollNo) {
            cout << "Student found:\n";
            s.display();
            found = true;
            break;
        }
    }
    fin.close();
    if (!found)
        cout << "Student not found!\n";
}

void deleteStudent() {
    int targetRollNo;
    cout << "Enter Roll No to delete: ";
    cin >> targetRollNo;

    Student s;
    ifstream fin("students.txt", ios::in | ios::binary);
    ofstream fout("temp.txt", ios::out | ios::binary);

    bool found = false;
    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() != targetRollNo) {
            fout.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    fin.close();
    fout.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student deleted!\n";
    else
        cout << "Student not found!\n";
}

void editStudent() {
    int targetRollNo;
    cout << "Enter Roll No to edit: ";
    cin >> targetRollNo;

    fstream file("students.txt", ios::in | ios::out | ios::binary);

    Student s;
    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == targetRollNo) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            found = true;
            cout << "Student record updated!\n";
            break;
        }
    }

    file.close();
    if (!found)
        cout << "Student not found!\n";
}

void countStudents() {
    Student s;
    ifstream fin("students.txt", ios::in | ios::binary);
    int count = 0;

    while (fin.read((char*)&s, sizeof(s))) {
        count++;
    }

    fin.close();
    cout << "Total number of students: " << count << endl;
}

void sortByMarks() {
    Student s;
    vector<Student> students;

    ifstream fin("students.txt", ios::in | ios::binary);
    while (fin.read((char*)&s, sizeof(s))) {
        students.push_back(s);
    }
    fin.close();

    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.getMarks() > b.getMarks();
    });

    cout << "Students sorted by marks (highest first):\n";
    for (auto &stu : students) {
        stu.display();
    }
}

int main() {
    if (!login()) {
        return 0;
    }

    int choice;
    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Edit Student\n";
        cout << "6. Count Students\n";
        cout << "7. Sort by Marks\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: editStudent(); break;
            case 6: countStudents(); break;
            case 7: sortByMarks(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice\n";
        }
    } while (choice != 0);

    return 0;
}
