#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    string branch;
    float marks;
    string createdAt;

public:
    void input();
    void display();
    int getRollNo();
    float getMarks();
};

#endif
