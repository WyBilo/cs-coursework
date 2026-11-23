#include <iostream>
using namespace std;

int main()
{
    // Declare variables
    double beginningBalance, totalDeposits, totalWithdrawals, endingBalance;

    // Input
    cout << "Enter beginning balance: ";
    cin >> beginningBalance;

    cout << "Enter total deposits: ";
    cin >> totalDeposits;

    cout << "Enter total withdrawals: ";
    cin >> totalWithdrawals;

    // Processing
    endingBalance = beginningBalance + totalDeposits - totalWithdrawals;

    // Output
    cout << "Ending Balance: $" << endingBalance << endl;

    return 0;
}
