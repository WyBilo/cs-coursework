/*
    Name: Wyatt Bilodeau
    Course: COM 301
    Lab 3: Comparing Sort Algorithms

    Description:
    This program compares the running time of four generic sorting algorithms:
    selection sort, merge sort, quick sort, and heap sort.

    As per the instructions, the program is non-interactive. It generates random arrays of different sizes,
    copies the same original array for each sorting method, times each algorithm,
    checks that the result is sorted, and prints the average running time in
    milliseconds.
*/

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using namespace std;
using namespace std::chrono;

// ------------------------- Utility Functions -------------------------

template <typename T>
bool isSorted(const T arr[], int size) {
    for (int i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

template <typename T>
void copyArray(const T source[], T destination[], int size) {
    for (int i = 0; i < size; ++i) {
        destination[i] = source[i];
    }
}

void generateRandomArray(int arr[], int size) {
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<int> distribution(1, 1000000);

    for (int i = 0; i < size; ++i) {
        arr[i] = distribution(generator);
    }
}

// ------------------------- Selection Sort -------------------------

template <typename T>
void selectionSort(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;

        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// ------------------------- Merge Sort -------------------------

template <typename T>
void insertionSortRange(T arr[], int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        T current = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > current) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = current;
    }
}

template <typename T>
void merge(T arr[], T temp[], int left, int middle, int right) {
    int leftIndex = left;
    int rightIndex = middle + 1;
    int tempIndex = left;

    while (leftIndex <= middle && rightIndex <= right) {
        if (arr[leftIndex] <= arr[rightIndex]) {
            temp[tempIndex++] = arr[leftIndex++];
        } else {
            temp[tempIndex++] = arr[rightIndex++];
        }
    }

    while (leftIndex <= middle) {
        temp[tempIndex++] = arr[leftIndex++];
    }

    while (rightIndex <= right) {
        temp[tempIndex++] = arr[rightIndex++];
    }

    for (int i = left; i <= right; ++i) {
        arr[i] = temp[i];
    }
}

template <typename T>
void mergeSortRecursive(T arr[], T temp[], int left, int right) {
    const int INSERTION_SORT_CUTOFF = 16;

    if (right - left + 1 <= INSERTION_SORT_CUTOFF) {
        insertionSortRange(arr, left, right);
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortRecursive(arr, temp, left, middle);
    mergeSortRecursive(arr, temp, middle + 1, right);

    // If the two halves are already in order, skip the merge step.
    if (arr[middle] <= arr[middle + 1]) {
        return;
    }

    merge(arr, temp, left, middle, right);
}

template <typename T>
void mergeSort(T arr[], int size) {
    if (size <= 1) {
        return;
    }

    T* temp = new T[size];
    mergeSortRecursive(arr, temp, 0, size - 1);
    delete[] temp;
}

// ------------------------- Quick Sort -------------------------

template <typename T>
T medianOfThree(T arr[], int left, int right) {
    int middle = left + (right - left) / 2;

    if (arr[middle] < arr[left]) {
        swap(arr[left], arr[middle]);
    }
    if (arr[right] < arr[left]) {
        swap(arr[left], arr[right]);
    }
    if (arr[right] < arr[middle]) {
        swap(arr[middle], arr[right]);
    }

    // Place the pivot at right - 1.
    swap(arr[middle], arr[right - 1]);
    return arr[right - 1];
}

template <typename T>
void quickSortRecursive(T arr[], int left, int right) {
    const int INSERTION_SORT_CUTOFF = 16;

    if (left + INSERTION_SORT_CUTOFF <= right) {
        T pivot = medianOfThree(arr, left, right);

        int i = left;
        int j = right - 1;

        while (true) {
            while (arr[++i] < pivot) {}
            while (pivot < arr[--j]) {}

            if (i < j) {
                swap(arr[i], arr[j]);
            } else {
                break;
            }
        }

        // Restore pivot to its final position.
        swap(arr[i], arr[right - 1]);

        quickSortRecursive(arr, left, i - 1);
        quickSortRecursive(arr, i + 1, right);
    } else {
        insertionSortRange(arr, left, right);
    }
}

template <typename T>
void quickSort(T arr[], int size) {
    if (size <= 1) {
        return;
    }

    quickSortRecursive(arr, 0, size - 1);
}

// ------------------------- Heap Sort -------------------------

template <typename T>
void percolateDown(T arr[], int index, int size) {
    T temp = arr[index];
    int child;

    while (index * 2 + 1 < size) {
        child = index * 2 + 1;

        if (child + 1 < size && arr[child] < arr[child + 1]) {
            ++child;
        }

        if (temp < arr[child]) {
            arr[index] = arr[child];
        } else {
            break;
        }

        index = child;
    }

    arr[index] = temp;
}

template <typename T>
void heapSort(T arr[], int size) {
    // Build the heap.
    for (int i = size / 2 - 1; i >= 0; --i) {
        percolateDown(arr, i, size);
    }

    // Repeatedly remove the largest item from the heap.
    for (int i = size - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        percolateDown(arr, 0, i);
    }
}

// ------------------------- Timing Function -------------------------

template <typename T>
double timeSort(void (*sortFunction)(T[], int), const T original[], int size, int runs) {
    double totalMilliseconds = 0.0;

    for (int run = 0; run < runs; ++run) {
        T* testArray = new T[size];
        copyArray(original, testArray, size);

        auto start = high_resolution_clock::now();
        sortFunction(testArray, size);
        auto stop = high_resolution_clock::now();

        if (!isSorted(testArray, size)) {
            cerr << "ERROR: A sorting method failed to sort the array correctly." << endl;
            delete[] testArray;
            return -1.0;
        }

        duration<double, milli> elapsed = stop - start;
        totalMilliseconds += elapsed.count();

        delete[] testArray;
    }

    return totalMilliseconds / runs;
}

// ------------------------- Main Program -------------------------

int main() {
    const int RUNS_PER_SIZE = 5;

    // These sizes can be adjusted if a computer cannot handle the largest values.
    const int numberOfSizes = 7;
    int sizes[numberOfSizes] = {1000, 2500, 5000, 10000, 25000, 50000, 100000};

    cout << fixed << setprecision(3);
    cout << "COM 301 Lab 3: Comparing Sort Algorithms" << endl;
    cout << "Average time in milliseconds over " << RUNS_PER_SIZE << " runs" << endl << endl;

    cout << left << setw(12) << "Size"
        << right << setw(18) << "Selection"
        << setw(18) << "Merge"
        << setw(18) << "Quick"
        << setw(18) << "Heap" << endl;

    cout << string(84, '-') << endl;

    for (int i = 0; i < numberOfSizes; ++i) {
        int size = sizes[i];
        int* originalArray = new int[size];
        generateRandomArray(originalArray, size);

        double selectionTime = timeSort(selectionSort<int>, originalArray, size, RUNS_PER_SIZE);
        double mergeTime = timeSort(mergeSort<int>, originalArray, size, RUNS_PER_SIZE);
        double quickTime = timeSort(quickSort<int>, originalArray, size, RUNS_PER_SIZE);
        double heapTime = timeSort(heapSort<int>, originalArray, size, RUNS_PER_SIZE);

        cout << left << setw(12) << size
            << right << setw(18) << selectionTime
            << setw(18) << mergeTime
            << setw(18) << quickTime
            << setw(18) << heapTime << endl;

        delete[] originalArray;
    }

    cout << endl;
    cout << "Note: Copy the table values into the Lab 3 report and create graphs from them." << endl;

    return 0;
}
