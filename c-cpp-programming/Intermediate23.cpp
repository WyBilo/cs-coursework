#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int temperatures[7][2]; 
    double totalHigh = 0, totalLow = 0;

    cout << "Enter the highest and lowest temperatures for 7 days.\n";

    for (int i = 0; i < 7; i++) {
        cout << "Day " << i + 1 << " highest: ";
        cin >> temperatures[i][0];

        cout << "Day " << i + 1 << " lowest: ";
        cin >> temperatures[i][1];

        totalHigh += temperatures[i][0];
        totalLow += temperatures[i][1];
    }

    double avgHigh = totalHigh / 7.0;
    double avgLow = totalLow / 7.0;

    cout << fixed << setprecision(1);
    cout << "\nAverage high temperature: " << avgHigh << endl;
    cout << "Average low temperature: " << avgLow << endl;

    return 0;
}