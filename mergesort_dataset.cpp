#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void merge(double arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    double L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(double arr[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    ifstream file("Social_Media_Engagement.csv");

    if (!file.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return 1;
    }

    string line, cell;
    double engagement[2000];
    int n = 0;

   
    getline(file, line);

    while (getline(file, line)) {

        if (n >= 2000) {
            cout << "Array limit reached!" << endl;
            break;
        }

        stringstream ss(line);

       
        while (getline(ss, cell, ',')) {
        }

        if (cell.empty())
            continue;

        engagement[n++] = stod(cell);
    }

    file.close();

    if (n == 0) {
        cout << "No valid engagement values found." << endl;
        return 0;
    }

    mergeSort(engagement, 0, n - 1);

    cout << "Sorted Engagement Values:\n";
    for (int i = 0; i < n; i++) {
        cout << engagement[i] << " ";
    }

    cout << endl;

    return 0;
}
