// Introductory20.cpp
// Saves prices in a sequential access file.
// Uses a negative number as the sentinel value.
// Saves values in fixed-point with two decimal places.
// Created by Wyatt Bilodeau on 12/06/2025

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    double price = 0.0;
    ofstream outFile;

    // Open file in append mode
    outFile.open("Introductory20.txt", ios::app);

    if (!outFile.is_open())
    {
        cout << "Introductory20.txt could not be opened." << endl;
        return 0;
    }

    cout << fixed << setprecision(2);

    cout << "Enter a price (negative number to stop): ";
    cin >> price;

    while (price >= 0)
    {
        // Write price to file with two decimal places
        outFile << fixed << setprecision(2) << price << endl;

        cout << "Enter a price (negative number to stop): ";
        cin >> price;
    }

    outFile.close();

    cout << "Prices saved to Introductory20.txt" << endl;

    return 0;
}