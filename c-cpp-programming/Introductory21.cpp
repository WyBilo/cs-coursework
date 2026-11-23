// Introductory21.cpp
// Allows user to enter a city, state, and ZIP code,
// then displays them using string concatenation.
// Program ends when sentinel value is entered.
// Created by Wyatt Bilodeau on 12/02/2025

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string city;
    string state;
    string zip;

    cout << "Enter city name (type QUIT to stop): ";
    getline(cin, city);

    while (city != "QUIT")
    {
        cout << "Enter state name: ";
        getline(cin, state);

        cout << "Enter ZIP code: ";
        getline(cin, zip);

        // string concatenation
        string fullLine = city + ", " + state + "  " + zip;

        cout << "\nFormatted: " << fullLine << endl << endl;

        // prompt again
        cout << "Enter city name (type QUIT to stop): ";
        getline(cin, city);
    }

    cout << "Program ended." << endl;
    return 0;
}