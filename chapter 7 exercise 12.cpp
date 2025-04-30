// chapter 7 exercise 12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
File Name:Chapter 7 exercise 12
Programmer: Olivia Ruiz
Requirements: Gradebook book application that gives the user the option to add
students, add grades, display the student name and the final grade as well. 
*/

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_GRADE = 100;
const int MIN_GRADE = 0;

struct Student {
    string name;
    vector<int> grades;
};


void addStudent(vector<Student>& students);
void addGrades(vector<Student>& students);
void displayStudents(const vector<Student>& students);
double calculateAverageExcludingLowest(const vector<int>& grades);
char letterGrade(double average);

int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n--- Grade Book Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Add Grades\n";
        cout << "3. Display Students and Grades\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (choice) {
        case 1:
            addStudent(students);
            break;
        case 2:
            addGrades(students);
            break;
        case 3:
            displayStudents(students);
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

void addStudent(vector<Student>& students) {
    if (students.size() >= MAX_STUDENTS) {
        cout << "Cannot add more students. Maximum limit reached.\n";
        return;
    }

    string name;
    cout << "Enter student name (or type 'done' to stop): ";
    getline(cin, name);

    while (name != "done" && students.size() < MAX_STUDENTS) {
        Student newStudent;
        newStudent.name = name;
        students.push_back(newStudent);

        if (students.size() >= MAX_STUDENTS) {
            cout << "Maximum number of students reached.\n";
            break;
        }

        cout << "Enter student name (or type 'done' to stop): ";
        getline(cin, name);
    }
}

void addGrades(vector<Student>& students) {
    if (students.empty()) {
        cout << "No students available. Add students first.\n";
        return;
    }

    for (size_t i = 0; i < students.size(); ++i) {
        cout << "\nEnter grades for " << students[i].name << " (-1 to stop):\n";
        int grade;
        while (true) {
            cout << "Grade: ";
            cin >> grade;

            if (grade == -1) break;
            if (grade >= MIN_GRADE && grade <= MAX_GRADE) {
                students[i].grades.push_back(grade);
            }
            else {
                cout << "Invalid grade. Enter a value between 0 and 100.\n";
            }
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to display.\n";
        return;
    }

    for (const auto& student : students) {
        cout << "\nStudent: " << student.name << "\nGrades: ";

        if (student.grades.empty()) {
            cout << "No grades entered.\n";
            continue;
        }

        for (int grade : student.grades) {
            cout << grade << " ";
        }

        double average = calculateAverageExcludingLowest(student.grades);
        cout << "\nFinal Average (lowest grade dropped): " << average;
        cout << "\nLetter Grade: " << letterGrade(average) << "\n";
    }
}

double calculateAverageExcludingLowest(const vector<int>& grades) {
    if (grades.empty()) return 0.0;
    if (grades.size() == 1) return grades[0];

    int sum = 0;
    int lowest = grades[0];

    for (int grade : grades) {
        sum += grade;
        if (grade < lowest) {
            lowest = grade;
        }
    }

    return static_cast<double>(sum - lowest) / (grades.size() - 1);
}

char letterGrade(double average) {
    if (average >= 90) return 'A';
    if (average >= 80) return 'B';
    if (average >= 70) return 'C';
    if (average >= 60) return 'D';
    return 'F';
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
