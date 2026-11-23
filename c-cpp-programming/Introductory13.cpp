// Introductory13.cpp
// Karlton Learning seminar fee calculator
// Fee per person: 1-5 => 125, 6-20 => 100, 21+ => 75
// Input: number of registrants (int)
// Output: total amount owed, fixed with 2 decimals, or an error for invalid input

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int people;

    cout << "Enter number of registrants: ";
    cin >> people;

    if (people <= 0) {
        cout << "Error: number of registrants must be greater than 0." << endl;
        return 0;
    }

    double feePerPerson;

    if (people <= 5)
        feePerPerson = 125.0;
    else if (people <= 20)
        feePerPerson = 100.0;
    else
        feePerPerson = 75.0;

    double total = people * feePerPerson;

    cout << fixed << setprecision(2);
    cout << "Fee per person: $" << feePerPerson << endl;
    cout << "Total owed: $" << total << endl;

    return 0;
}