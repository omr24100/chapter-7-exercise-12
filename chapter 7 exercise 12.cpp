// chapter 7 exercise 12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
File Name:Chapter 7 exercise 12
Programmer: Olivia Ruiz
Date: 5/1/25
Requirements: Gradebook book application that gives the user the option to add
students, add grades, display the student name and the final grade as well. Make sure you can add more grades into the code. 
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric> // for accumulate
#include <limits>  // for input validation

using namespace std;

class Gradebook {
private:
    map<string, vector<double>> studentGrades;

public:
    void addStudent(const string& name) {
        if (studentGrades.find(name) == studentGrades.end()) {
            studentGrades[name] = {};
            cout << "Student '" << name << "' added.\n";
        } else {
            cout << "Student already exists.\n";
        }
    }

    void addGrade(const string& name, double grade) {
        if (studentGrades.find(name) != studentGrades.end()) {
            studentGrades[name].push_back(grade);
            cout << "Grade added for " << name << ".\n";
        } else {
            cout << "Student not found.\n";
        }
    }

    void changeGrade(const string& name, int index, double newGrade) {
        if (studentGrades.find(name) != studentGrades.end()) {
            if (index >= 0 && index < studentGrades[name].size()) {
                studentGrades[name][index] = newGrade;
                cout << "Grade updated.\n";
            } else {
                cout << "Invalid grade index.\n";
            }
        } else {
            cout << "Student not found.\n";
        }
    }

    void displayGrades() const {
        if (studentGrades.empty()) {
            cout << "No students to display.\n";
            return;
        }

        for (const auto& pair : studentGrades) {
            const string& name = pair.first;
            const vector<double>& grades = pair.second;
            cout << "Student: " << name << " | Grades: ";
            for (double g : grades) {
                cout << g << " ";
            }
            double avg = grades.empty() ? 0 : accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
            cout << "| Final Grade: " << avg << "\n";
        }
    }
};

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Gradebook gb;
    int choice;

    do {
        cout << "\nGradebook Menu:\n";
        cout << "1. Add Student\n";
        cout << "2. Add Grade\n";
        cout << "3. Change Grade\n";
        cout << "4. Display Grades\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Try again.\n";
            continue;
        }

        string name;
        switch (choice) {
            case 1:
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                gb.addStudent(name);
                break;
            case 2: {
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                double grade;
                cout << "Enter grade: ";
                cin >> grade;
                if (cin.fail()) {
                    clearInput();
                    cout << "Invalid grade.\n";
                } else {
                    gb.addGrade(name, grade);
                }
                break;
            }
            case 3: {
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                int index;
                double newGrade;
                cout << "Enter grade index (starting at 0): ";
                cin >> index;
                cout << "Enter new grade: ";
                cin >> newGrade;
                if (cin.fail()) {
                    clearInput();
                    cout << "Invalid input.\n";
                } else {
                    gb.changeGrade(name, index, newGrade);
                }
                break;
            }
            case 4:
                gb.displayGrades();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
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
