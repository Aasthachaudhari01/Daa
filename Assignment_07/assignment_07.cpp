
#include <iostream>
using namespace std;

const int MAX = 100;

int main() {
    int n, e, rooms, totalStudents;
    int head[MAX], to[MAX * MAX], next[MAX * MAX];
    int color[MAX], students[MAX];
    int edgeCount = 0;

    for (int i = 0; i < MAX; i++)
        head[i] = -1;

    cout << "Enter number of courses: ";
    cin >> n;

    if (n < 1 || n > MAX) {
        cout << "Invalid number of courses.\n";
        return 0;
    }

    cout << "Enter number of conflicting course pairs: ";
    cin >> e;

    if (e < 0 || e > n * (n - 1) / 2) {
        cout << "Invalid number of conflicting pairs.\n";
        return 0;
    }

    cout << "Enter conflicting course pairs (0-based indexing):\n";

    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
            cout << "Invalid course pair.\n";
            return 0;
        }

        to[edgeCount] = v;
        next[edgeCount] = head[u];
        head[u] = edgeCount++;

        to[edgeCount] = u;
        next[edgeCount] = head[v];
        head[v] = edgeCount++;
    }

    cout << "Enter number of students enrolled in each course:\n";

    for (int i = 0; i < n; i++) {
        cout << "Course " << i << ": ";
        cin >> students[i];
    }

    cout << "Enter total number of classrooms: ";
    cin >> rooms;

    cout << "Enter total available seats in all classrooms: ";
    cin >> totalStudents;

    for (int i = 0; i < n; i++)
        color[i] = -1;

    int maxColor = -1;

    // Greedy Graph Coloring
    for (int i = 0; i < n; i++) {
        bool available[MAX];

        for (int c = 0; c < n; c++)
            available[c] = true;

        for (int j = head[i]; j != -1; j = next[j]) {
            int neighbor = to[j];

            if (color[neighbor] != -1)
                available[color[neighbor]] = false;
        }

        int c = 0;
        while (c < n && !available[c])
            c++;

        color[i] = c;

        if (c > maxColor)
            maxColor = c;
    }

    int slots = maxColor + 1;

    cout << "\n========== EXAM TIMETABLE ==========\n";

    for (int s = 0; s < slots; s++) {
        int courseCount = 0;
        int studentCount = 0;

        cout << "\nExam Slot " << s + 1 << ":\n";

        for (int i = 0; i < n; i++) {
            if (color[i] == s) {
                cout << "Course " << i
                     << " | Students: " << students[i] << endl;

                courseCount++;
                studentCount += students[i];
            }
        }

        cout << "Total Exams: " << courseCount << endl;
        cout << "Total Students: " << studentCount << endl;
    }

    cout << "\n========== RESOURCE SUMMARY ==========\n";
    cout << "Total Courses: " << n << endl;
    cout << "Total Exam Slots Required: " << slots << endl;
    cout << "Total Classrooms Available: " << rooms << endl;
    cout << "Total Classroom Seating Capacity: "
         << totalStudents << endl;

    int total = 0;

    for (int i = 0; i < n; i++)
        total += students[i];

    cout << "Total Course Enrollments: " << total << endl;

    if (total > totalStudents)
        cout << "Seating Capacity: Insufficient\n";

    cout << "=====================================\n";

    return 0;
}
