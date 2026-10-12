#include <iostream>
using namespace std;

int main() {
    int n, e, rooms, totalStudents;
    int graph[100][100] = {0};
    int color[100], students[100];

    cout << "Enter number of courses: ";
    cin >> n;

    cout << "Enter number of conflicting course pairs: ";
    cin >> e;

    cout << "Enter conflicting course pairs (0-based indexing):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
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
    // Initialize colors
    for (int i = 0; i < n; i++) {
        color[i] = -1;
    }

    // Greedy Graph Coloring
    int maxColor = -1;

    for (int i = 0; i < n; i++) {
        int available[100] = {0};

        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1 && color[j] != -1) {
                available[color[j]] = 1;
            }
        }

        int c;
        for (c = 0; c < n; c++) {
            if (available[c] == 0)
                break;
        }

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
        if (slots >= rooms) {
        cout << " Insufficient Classrooms\n";
    }

    int total = 0;
    for (int i = 0; i < n; i++) {
        total += students[i];
    }

    cout << "Total Course Enrollments: " << total << endl;

    if (total >= totalStudents)
         cout << "Seating Capacity: Insufficient\n";

    cout << "=====================================\n";

    return 0;
}
                                                                                                                                      112,1         Bot

