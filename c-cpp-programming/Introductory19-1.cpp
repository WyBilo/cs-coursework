// Introductory19.cpp
// Saves a company's payroll amounts in a sequential access file.
// Uses a negative number as the sentinel value.
// Created/revised by Wyatt Bilodeau on 12/06/2025

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    double payrollAmount = 0.0;
    ofstream outFile;

    // Open file in append mode
    outFile.open("Introductory19.txt", ios::app);

    if (!outFile.is_open())
    {
        cout << "Introductory19.txt could not be opened." << endl;
        return 0;
    }

    cout << fixed << setprecision(2);

    cout << "Enter payroll amount (negative number to stop): ";
    cin >> payrollAmount;

    while (payrollAmount >= 0)
    {
        // write to file with two decimal places
        outFile << fixed << setprecision(2) << payrollAmount << endl;

        cout << "Enter payroll amount (negative number to stop): ";
        cin >> payrollAmount;
    }

    outFile.close();

    cout << "Payroll amounts saved to Introductory19.txt" << endl;

    return 0;
}