// Introductory16.cpp
// Displays gross pay for one or more employees.
// Uses a void function to calculate overtime pay.
// Sentinel: negative hours end the program.
// Created by Wyatt Bilodeau

#include <iostream>
#include <iomanip>
using namespace std;

// Function prototype
void calcOvertimePay(int hoursWorked, double rate, double &overtimePay);

int main()
{
    int hours;
    double rate;
    double grossPay;
    double overtimePay;

    cout << fixed << setprecision(2);

    cout << "Enter hours worked (negative to stop): ";
    cin >> hours;

    while (hours >= 0)
    {
        cout << "Enter hourly pay rate: ";
        cin >> rate;

        // Reset overtime pay
        overtimePay = 0.0;

        // Calculate overtime pay using the function
        calcOvertimePay(hours, rate, overtimePay);

        // Regular pay
        int regularHours = (hours > 37) ? 37 : hours;
        double regularPay = regularHours * rate;

        // Total gross pay
        grossPay = regularPay + overtimePay;

        cout << "Gross pay: $" << grossPay << endl << endl;

        // Prompt again
        cout << "Enter hours worked (negative to stop): ";
        cin >> hours;
    }

    cout << "Program ended." << endl;
    return 0;
}

// ------------------------------------------------------
// calcOvertimePay
// Calculates overtime pay for an employee. 
// hoursWorked: total hours the employee worked
// rate: pay rate
// overtimePay: returned by reference
// ------------------------------------------------------
void calcOvertimePay(int hoursWorked, double rate, double &overtimePay)
{
    overtimePay = 0.0;

    // Time and a half for hours 38–50
    if (hoursWorked > 37)
    {
        int timeAndHalfHours = min(hoursWorked, 50) - 37;
        overtimePay += timeAndHalfHours * (rate * 1.5);
    }

    // Double time for hours over 50
    if (hoursWorked > 50)
    {
        int doubleTimeHours = hoursWorked - 50;
        overtimePay += doubleTimeHours * (rate * 2.0);
    }
}