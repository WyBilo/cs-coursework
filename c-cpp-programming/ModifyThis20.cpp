//ModifyThis.cpp - displays the highest and lowest numbers in an array
//Created/revised by Wyatt Bilodeau on 11/29/2025

#include <iostream>
using namespace std;

//function prototypes
int getHighest(int numArray[], int numElements);
int getLowest(int numArray[], int numElements);

int main()
{
    int numbers[4] = {13, 2, 40, 25};

    cout << "The highest number in the array is "
        << getHighest(numbers, 4) << "." << endl;

    cout << "The lowest number in the array is "
        << getLowest(numbers, 4) << "." << endl;

    return 0;
}   //end of main function

//*****function definitions*****
int getHighest(int numArray[], int numElements)
{
    int high = numArray[0];

    for (int sub = 1; sub < numElements; sub += 1)
        if (numArray[sub] > high)
            high = numArray[sub];

    return high;
}

int getLowest(int numArray[], int numElements)
{
    int low = numArray[0];

    for (int sub = 1; sub < numElements; sub += 1)
        if (numArray[sub] < low)
            low = numArray[sub];

    return low;
}