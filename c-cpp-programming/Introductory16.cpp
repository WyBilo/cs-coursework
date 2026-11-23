// Introductory16.cpp
// Displays a table of numbers 10 through 13,
// along with their squares and cubes.
// Created by Wyatt Bilodeau

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "Number   Square   Cube" << endl;
    cout << "-----------------------" << endl;

    for (int n = 10; n <= 13; n++)
    {
        int square = n * n;
        int cube = n * n * n;

        cout << left << setw(8) << n
            << setw(9) << square
            << cube << endl;
    }

    return 0;
}