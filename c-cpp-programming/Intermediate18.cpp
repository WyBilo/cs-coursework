// Intermediate18.cpp
// Calculates Khalid's raises for the next three years
// Uses rates 3%, 4%, and 5%
// Program stops when salary entered <= 0
// Created by Wyatt Bilodeau

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double salary;

    const double RATE1 = 0.03;
    const double RATE2 = 0.04;
    const double RATE3 = 0.05;

    cout << fixed << setprecision(2);

    cout << "Enter annual salary (0 or negative to stop): ";
    cin >> salary;

    while (salary > 0)
    {
        double raise1 = salary * RATE1;
        salary += raise1;

        double raise2 = salary * RATE2;
        salary += raise2;

        double raise3 = salary * RATE3;
        salary += raise3;

        cout << "Raise Year 1: $" << raise1 << endl;
        cout << "Raise Year 2: $" << raise2 << endl;
        cout << "Raise Year 3: $" << raise3 << endl;
        cout << "Salary after 3rd raise: $" << salary << endl << endl;

        cout << "Enter annual salary (0 or negative to stop): ";
        cin >> salary;
    }

    cout << "Program ended." << endl;
    return 0;
}