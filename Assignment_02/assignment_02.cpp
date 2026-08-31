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

// Parses one CSV line respecting quoted fields (commas inside quotes are not delimiters)
void parseCSVLine(const string &line, string fields[], int numFields) {
    int fieldIndex = 0;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size() && fieldIndex < numFields; i++) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            fields[fieldIndex++] = current;
            current.clear();
        } else {
            current += c;
        }
    }
    if (fieldIndex < numFields) fields[fieldIndex] = current;
}

int partition(Movie arr[], int low, int high, int key) {
    double pivot;
    if (key == 1) pivot = arr[high].rating;
    else if (key == 2) pivot = arr[high].year;
    else pivot = arr[high].votes;

    int i = low - 1;

    for (int j = low; j < high; j++) {
        double val;
        if (key == 1) val = arr[j].rating;
        else if (key == 2) val = arr[j].year;
        else val = arr[j].votes;

        if (val > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Movie arr[], int low, int high, int key) {
    if (low < high) {
        int pi = partition(arr, low, high, key);
        quickSort(arr, low, pi - 1, key);
        quickSort(arr, pi + 1, high, key);
    }
}

int main() {
    ifstream file("movie.csv");
    if (!file.is_open()) {
        cout << "Error: Cannot open movie.csv" << endl;
        return 1;
    }

    const int MAX_MOVIES = 10000;
    Movie* movies = new Movie[MAX_MOVIES];
    int n = 0;
    string line;

    getline(file, line); // skip header

    while (getline(file, line) && n < MAX_MOVIES) {
        string fields[6];
        parseCSVLine(line, fields, 6);

        try {
            movies[n].title = fields[1];
            movies[n].year = stoi(fields[2]);
            movies[n].rating = stod(fields[4]);
            movies[n].votes = stol(fields[5]);
            n++;
        } catch (...) {
            continue; 
        }
    }
    file.close();

    cout << "Loaded " << n << " movies.\n";
    cout << "Sort by: 1-Rating  2-Year  3-Votes : ";
    int key;
    cin >> key;

    quickSort(movies, 0, n - 1, key);

    int topN;
    cout << "How many top results to show: ";
    cin >> topN;
    if (topN > n) topN = n;

    cout << "\nTop " << topN << " Movies:\n";
    for (int i = 0; i < topN; i++) {
        cout << (i + 1) << ". " << movies[i].title
             << " | " << movies[i].year
             << " | Rating: " << movies[i].rating
             << " | Votes: " << movies[i].votes << endl;
    }

    delete[] movies;
    return 0;
}