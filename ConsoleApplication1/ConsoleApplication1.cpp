#include <iostream>
#include <string.h>
#include "LL.h"
#include <fstream>
using namespace std;

class Course {
public:
    string code;
    int credit, section;
    Course() {}
    Course(string c, int cr, int se) :code(c), credit(cr), section(se) {}
    friend istream& operator>>(istream& is, Course& c) {
        is >> c.code >> c.credit >> c.section;
        return is;
    }
    friend ostream& operator<<(ostream& os, Course& c) {
        os << c.code << " " << c.credit << " " << c.section << endl;
        return os;
    }
    bool operator==(const Course& other) const {
        return code == other.code;  
    }
};

struct Student {
    string name, surname;
    int id, tcredit = 0;
    double cgpa;
    LL<Course> course;
};

int main() {
    int cr = 0, sec;
    string comm, cc, cname;
    ifstream std("student.txt");
    Student student;

    std >> student.name >> student.surname >> student.id >> student.cgpa;

    while (!std.eof()) {
        cin >> cname >> cr >> sec;
        Course obj(cname, cr, sec);
        student.course.insertLast(obj);
        student.tcredit += cr;
    }    

    do {
        cout << "Enter Add | Drop | Change | List | Quit: ";
        cin >> comm;

        if (comm == "List") {
            cout << "Name: " << student.name << " " << student.surname << " ID: " << student.id << " CGPA: " << student.cgpa << " Total credit: " << student.tcredit << endl;
            cout << "Registered Courses:" << endl;
            cout << student.course;
        }

        if (comm == "Add") {
            cout << "Enter Couse code, credit and section to be added: ";
            cin >> cname >> cr >> sec;
            Course obj(cname, cr, sec);

            if (student.course.search(obj)) {
                cout << "You cant add same course." << endl;
            }
            else {
                if(student.cgpa<2.1 && (student.tcredit+cr)<25) {
                    student.course.insertLast(obj);
                    cout << obj.code << " " << obj.credit << " " << obj.section << " has been added." << endl;
                }
                else if ((student.tcredit+cr) < 35) {
                    student.course.insertLast(obj);
                    cout << obj.code << " " << obj.credit << " " << obj.section << " has been added." << endl;
                }
            }
        }

        if (comm == "Change") {
            cout << "Enter course code and new section: ";
            cin >> cname >> sec;
            Course obj(cname, 0, sec);
            if (student.course.search(obj)) {
                node<Course>* p = student.course.search(obj);
                p->info.section = sec;
            }
        }

        if (comm == "Drop") {
            cout << "Enter course code to be deleted: ";
            cin >> cname;
            Course obj(cname, 0, 0);
            student.course.deleteNode(obj);
            cout << cname << " has been deleted.";
        }

    } while (comm != "Quit");
}
