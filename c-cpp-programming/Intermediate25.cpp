// Intermediate25.cpp
// Accepts a string and displays it in reverse order.
// Created by Wyatt Bilodeau on 12/02/2025

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string text;

    cout << "Enter a string: ";
    getline(cin, text);

    string reversed = "";  // will hold reversed string

    // reverse using a loop
    for (int i = text.length() - 1; i >= 0; i--)
    {
        reversed += text[i];
    }

    cout << "Reversed: " << reversed << endl;

    return 0;
}