#include <bits/stdc++.h>
using namespace std;

class IntervalMerger {
    vector<pair<int, int>> intervals;

public:
    void addInterval(int start, int end) {
        intervals.push_back({start, end});
        sort(intervals.begin(), intervals.end());
        vector<pair<int, int>> merged;
        for (auto &[s, e] : intervals) {
            if (!merged.empty() && merged.back().second >= s) 
                merged.back().second = max(merged.back().second, e);
            else 
                merged.push_back({s, e});
        }
        intervals = merged;
        cout << "Interval [" << start << ", " << end << "] added and merged if necessary.\n";
    }

    void getIntervals() {
        if (intervals.empty()) {
            cout << "No intervals present.\n";
            return;
        }
        cout << "Merged Intervals: ";
        for (auto &[s, e] : intervals) cout << "[" << s << ", " << e << "] ";
        cout << endl;
    }
};

int main() {
    IntervalMerger merger;
    int choice, start, end;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Interval\n";
        cout << "2. Get Intervals\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter start and end of the interval: ";
                cin >> start >> end;
                if (start > end) {
                    cout << "Invalid interval! Start should be <= End.\n";
                } else {
                    merger.addInterval(start, end);
                }
                break;
            case 2:
                merger.getIntervals();
                break;
            case 3:
                cout << "Program Closed.\n";
                return 0;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    }
}
