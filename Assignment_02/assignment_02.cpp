
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Movie {
    string title;
    int year;
    double rating;
    long votes;
};

const int MAX = 100000;

int quick(Movie arr[], int low, int high, int key) {
    double pivot;

    if (key == 1)
        pivot = arr[high].rating;
    else if (key == 2)
        pivot = arr[high].year;
    else
        pivot = arr[high].votes;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        double value;

        if (key == 1)
            value = arr[j].rating;
        else if (key == 2)
            value = arr[j].year;
        else
            value = arr[j].votes;

        if (value > pivot) {
            i++;

            Movie temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Movie temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(Movie arr[], int low, int high, int key) {
    if (low < high) {
        int pi = quick(arr, low, high, key);

        quickSort(arr, low, pi - 1, key);
        quickSort(arr, pi + 1, high, key);
    }
}

int main() {
    ifstream file("movie.csv");

    if (!file.is_open()) {
        cout << "Cannot open movie.csv" << endl;
        return 1;
    }

    Movie movies[MAX];
    int n = 0;
    string line;

    getline(file, line); // Skip header

    while (getline(file, line) && n < MAX) {
        stringstream ss(line);
        string fields[6];

        for (int i = 0; i < 6; i++)
            getline(ss, fields[i], ',');

        movies[n].title = fields[1];
        movies[n].year = stoi(fields[2]);
        movies[n].rating = stod(fields[4]);
        movies[n].votes = stol(fields[5]);

        n++;
    }

    file.close();

    cout << "Loaded " << n << " movies." << endl;
    cout << "Sort by: 1-Rating  2-Year  3-Votes: ";

    int key;
    cin >> key;

    if (key < 1 || key > 3) {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    quickSort(movies, 0, n - 1, key);

    int topN;
    cout << "How many movies to display? ";
    cin >> topN;

    if (topN < 0)
        topN = 0;

    if (topN > n)
        topN = n;

    cout << "\nTop Movies:\n";

    for (int i = 0; i < topN; i++) {
        cout << i + 1 << ". " << movies[i].title
             << " | Year: " << movies[i].year
             << " | Rating: " << movies[i].rating
             << " | Votes: " << movies[i].votes << endl;
    }

    return 0;
}
