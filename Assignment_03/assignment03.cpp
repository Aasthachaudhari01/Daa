
#include <iostream>
#include <algorithm>
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

    // Sort items by ratio in descending order
    sort(item, item + n, [](Item a, Item b) {
        return a.ratio > b.ratio;
    });

    double totalValue = 0;

    // Select items
    for (int i = 0; i < n && W > 0; i++) {
        if (item[i].wt <= W) {
            W = W - item[i].wt;
            totalValue = totalValue + item[i].val;
        } else {
            totalValue = totalValue + item[i].ratio * W;
            W = 0;
        }
    }

    cout << "Maximum Utility = " << totalValue << endl;

    return 0;
}
