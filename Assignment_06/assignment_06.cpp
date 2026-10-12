#include <iostream>
using namespace std;

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int weight[100], value[100];

    cout << "Enter truck capacity: ";
    cin >> W;

    cout << "Enter weight and utility value of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }

    int dp[101][1001] = {0};

    // Dynamic Programming
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weight[i - 1] <= w) {
                int include = value[i - 1] + dp[i - 1][w - weight[i - 1]];
                int exclude = dp[i - 1][w];

                if (include > exclude)
                    dp[i][w] = include;
                else
                    dp[i][w] = exclude;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum Utility Value: " << dp[n][W] << endl;

    // Find selected items
    cout << "Selected Items:\n";
    int w = W;

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Item " << i
                 << " (Weight: " << weight[i - 1]
                 << " kg, Utility: " << value[i - 1] << ")\n";

            w = w - weight[i - 1];
        }
    }

    return 0;
}