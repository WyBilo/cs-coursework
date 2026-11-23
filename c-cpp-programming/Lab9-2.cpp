// Lab9-2.cpp - displays two monthly car payments
// Created/revised by Wyatt Bilodeau on 11/20/2025

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// function prototype
double getPayment(int amount, double monthlyRate, int months);

// ----------------- main -----------------
int main()
{
    int carPrice = 0;
    int rebate = 0;
    double creditRate = 0.0;   // annual rate (percent, e.g. 7.5)
    double dealerRate = 0.0;   // annual rate (percent, e.g. 6.9)
    int term = 0;              // term in years
    double creditPayment = 0.0;
    double dealerPayment = 0.0;

    cout << "Car price (after any trade-in): ";
    cin >> carPrice;

    cout << "Rebate: ";
    cin >> rebate;

    cout << "Credit union annual rate (percent): ";
    cin >> creditRate;

    cout << "Dealer annual rate (percent): ";
    cin >> dealerRate;

    cout << "Term in years: ";
    cin >> term;

    // convert annual percent rate to monthly decimal rate
    double creditMonthlyRate = (creditRate ) / 12.0;
    double dealerMonthlyRate = (dealerRate ) / 12.0;
    int months = term * 12;

    // call function to calculate payments
    creditPayment = getPayment(carPrice - rebate,
                            creditMonthlyRate, months);
    dealerPayment = getPayment(carPrice,
                            dealerMonthlyRate, months);

    // display payments
    cout << fixed << setprecision(2) << endl;
    cout << "Credit union payment: $" << creditPayment << endl;
    cout << "Dealer payment:       $" << dealerPayment << endl;

    return 0;
}

// ----------------- getPayment -----------------
// amount      : loan amount (principal)
// monthlyRate : monthly interest rate (e.g. 0.005 for 0.5% per month)
// months      : total number of monthly payments
double getPayment(int amount, double monthlyRate, int months)
{
    if (months <= 0)
        return 0.0;

    // handle zero interest as a simple division
    if (monthlyRate == 0.0)
        return static_cast<double>(amount) / months;

    // standard loan payment formula:
    // payment = P * r * (1 + r)^n / ((1 + r)^n - 1)
    double factor = pow(1.0 + monthlyRate, months);
    double payment = amount * monthlyRate * factor / (factor - 1.0);
    return payment;
}