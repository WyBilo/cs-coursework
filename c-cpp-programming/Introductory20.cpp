// Introductory20.cpp
// Displays shipping charge based on a 3-character region code.
// Code must be: A## or B##
// Sentinel: enter "XXX" to stop.
// Created by Wyatt Bilodeau on 12/02/2025

#include <iostream>
#include <string>
using namespace std;

// Function to check whether region code is valid
bool isValidRegion(string code)
{
    if (code.length() != 3)
        return false;

    // first char must be A or B
    if (code[0] != 'A' && code[0] != 'B')
        return false;

    // next two must be digits
    if (!isdigit(code[1]) || !isdigit(code[2]))
        return false;

    return true;
}

int main()
{
    string region;

    cout << "Enter region code (XXX to stop): ";
    cin >> region;

    while (region != "XXX")
    {
        if (isValidRegion(region))
        {
            if (region[0] == 'A')
                cout << "Shipping charge: $25" << endl;
            else // region[0] == 'B'
                cout << "Shipping charge: $30" << endl;
        }
        else
        {
            cout << "Invalid region code." << endl;
        }

        cout << "\nEnter region code (XXX to stop): ";
        cin >> region;
    }

    cout << "Program ended." << endl;
    return 0;
}