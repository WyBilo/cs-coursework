//Lab7-2.cpp - Displays the number of years required
//for a company's sales to reach at least $150,000
//using a 5.5% annual growth rate. Also displays
//the sales at that time.
//Created/revised by Wyatt Bilodeau on 11/11/2025

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    const double GROWTH_RATE = 0.055; //5.5% growth rate
    double sales = 0.0;          //initial sales
    double annualIncrease = 0.0; //amount of annual increase
    int years = 0;               //number of years required

    cout << "Current year's sales: ";
    cin >> sales;

    while (sales < 150000.0)
    {
        annualIncrease = sales * GROWTH_RATE;
        sales += annualIncrease;
        years += 1;
    }

    cout << fixed << setprecision(0);
    cout << "Sales " << years << " years from now: $"
        << sales << endl;

    return 0;
}