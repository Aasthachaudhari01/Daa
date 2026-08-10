#include <iostream>
using namespace std;

struct Item {
    int wt;
    int val;
    double ratio;
};

int main() {
    int n, W;
    Item item[100];

    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter boat capacity: ";
    cin >> W;

    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        cin >> item[i].wt;
    }

    cout << "Enter utility values of items: ";
    for (int i = 0; i < n; i++) {
        cin >> item[i].val;
        item[i].ratio = (double)item[i].val / item[i].wt;
    }

    // Sort items by utility/weight ratio
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (item[i].ratio < item[j].ratio) {
                Item temp = item[i];
                item[i] = item[j];
                item[j] = temp;
            }
        }
    }

    double totalValue = 0;

    // Select items
    for (int i = 0; i < n && W > 0; i++) {

        if (item[i].wt <= W) {
            W = W - item[i].wt;
            totalValue = totalValue + item[i].val;
        }
        else {
            totalValue = totalValue + item[i].ratio * W;
            W = 0;
        }
    }

    cout << "Maximum Utility = " << totalValue << endl;

    return 0;
}