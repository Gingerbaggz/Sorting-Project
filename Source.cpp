#include <iostream> // For std::cout, std::cin
#include <vector> // For std::vector
#include <cstdlib> // For rand()
#include <chrono> // For std::chrono
#include <algorithm> // For std::sort

// Function to generate a vector of random integers
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    for (int& val : arr) {
        val = rand() % 100000;  // Random number between 0 and 99,999
    }
    return arr;
}

// Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
        }
    }
}

// Quick Sort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high], i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) std::swap(arr[++i], arr[j]);
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// C++ Built-in Sort
void cppSort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}

// Measure sorting time and print results
void measureSortTime(std::vector<int>& arr, void (*sortFunc)(std::vector<int>&), const std::string& sortName) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << sortName << " took: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " ms\n";
}
// Measure quick sort time and print results
void measureQuickSortTime(std::vector<int>& arr, const std::string& sortName) {
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);  // Pass low and high for quickSort
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << sortName << " took: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << " ms\n";
}

int main() {
    std::vector<int> sizes = { 100, 1000, 10000, 100000 };  // Array sizes to test

    for (int size : sizes) {
        std::cout << "\nSorting array of size " << size << ":\n";

        // Generate random array
        std::vector<int> arr = generateRandomArray(size);

        // Measure time for each sorting algorithm
        std::vector<int> bubbleArr = arr;
        measureSortTime(bubbleArr, bubbleSort, "Bubble Sort");

		// Quick Sort
        std::vector<int> quickArr = arr;
        measureQuickSortTime(quickArr, "Quick Sort");

		// C++ Built-in Sort
        std::vector<int> cppArr = arr;
        measureSortTime(cppArr, cppSort, "C++ Built-in Sort");
    }

    return 0;
}
