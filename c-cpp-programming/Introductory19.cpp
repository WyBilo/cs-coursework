// Introductory19.cpp 
// Allows a teacher to enter midterm and final scores for multiple students.
// Each exam is worth 200 points. Displays letter grade based on total points.
// Created by Wyatt Bilodeau on 11/11/2025

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double midterm = 0.0;
    double finalExam = 0.0;
    double totalPoints = 0.0;
    char moreStudents = 'Y';

    while (moreStudents == 'Y' || moreStudents == 'y')
    {
        cout << "Enter midterm score (0-200): ";
        cin >> midterm;

        cout << "Enter final exam score (0-200): ";
        cin >> finalExam;

        totalPoints = midterm + finalExam;

        cout << "Total Points: " << totalPoints << endl;

        if (totalPoints >= 360)
            cout << "Grade: A" << endl;
        else if (totalPoints >= 320)
            cout << "Grade: B" << endl;
        else if (totalPoints >= 280)
            cout << "Grade: C" << endl;
        else if (totalPoints >= 240)
            cout << "Grade: D" << endl;
        else
            cout << "Grade: F" << endl;

        cout << endl << "Enter scores for another student? (Y/N): ";
        cin >> moreStudents;
        cout << endl;
    }

    cout << "Program complete." << endl;
    return 0;
}