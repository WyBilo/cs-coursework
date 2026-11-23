#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int partition(vector<int>& a, int left, int right) {
    int pivot = a[right];
    int i = left;

    for (int j = left; j < right; j++) {
        if (a[j] <= pivot) {
            swap(a[i], a[j]);
            i++;
        }
    }

    swap(a[i], a[right]);
    return i;
}

int quickSelect(vector<int>& a, int left, int right, int k) {
    if (left == right) {
        return a[left];
    }

    int pivotIndex = partition(a, left, right);

    if (k == pivotIndex) {
        return a[k];
    } 
    else if (k < pivotIndex) {
        return quickSelect(a, left, pivotIndex - 1, k);
    } 
    else {
        return quickSelect(a, pivotIndex + 1, right, k);
    }
}

int main() {
    vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5};

    int k;
    cout << "Enter k: ";
    cin >> k;

    if (k < 1 || k > numbers.size()) {
        cout << "Invalid k value." << endl;
        return 1;
    }

    int result = quickSelect(numbers, 0, numbers.size() - 1, k - 1);

    cout << "The " << k << "th smallest element is: " << result << endl;

    return 0;
}