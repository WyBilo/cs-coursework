// Introductory11.cpp
// Mountain Coffee total due calculator
// Inputs: pounds (int), price per pound (double), tax flag Y/N (char)
// Output: total amount owed, fixed with 2 decimals

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int pounds;
    double price;
    char taxFlag;

    cout << "Enter number of pounds: ";
    cin >> pounds;

    cout << "Enter price per pound: ";
    cin >> price;

    cout << "Charge 3.5% sales tax? (Y/N): ";
    cin >> taxFlag;

    double subtotal = pounds * price;
    const double taxRate = 0.035;
    bool chargeTax = (taxFlag == 'Y' || taxFlag == 'y');
    double tax = chargeTax ? subtotal * taxRate : 0.0;
    double total = subtotal + tax;

    cout << fixed << setprecision(2);
    cout << "Total amount owed: $" << total << endl;

    return 0;
}