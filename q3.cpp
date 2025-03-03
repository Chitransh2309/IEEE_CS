#include <iostream>
#include <unordered_map>
#include <queue>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class ExpiringCache {
private:
    struct CacheEntry {
        string key;
        time_point<steady_clock> expiry;
        bool operator>(const CacheEntry &other) const {
            return expiry > other.expiry;
        }
    };

    unordered_map<string, pair<string, time_point<steady_clock>>> cache;
    priority_queue<CacheEntry, vector<CacheEntry>, greater<CacheEntry>> expiryHeap;

    void removeExpiredKeys() {
        while (!expiryHeap.empty()) {
            auto [key, expiry] = expiryHeap.top();
            if (steady_clock::now() < expiry) break;
            expiryHeap.pop();
            if (cache.find(key) != cache.end() && cache[key].second <= steady_clock::now()) {
                cache.erase(key);
            }
        }
    }

public:
    void set(const string &key, const string &value, int expiryTimeMs) {
        time_point<steady_clock> expiry = steady_clock::now() + milliseconds(expiryTimeMs);
        cache[key] = {value, expiry};
        expiryHeap.push({key, expiry});
        cout << "Key \"" << key << "\" set successfully.\n";
    }

    string get(const string &key) {
        removeExpiredKeys();

        auto it = cache.find(key);
        if (it == cache.end()) return "Key not found or expired.";

        if (it->second.second <= steady_clock::now()) {
            cache.erase(it);
            return "Key not found or expired.";
        }
        return "Value: " + it->second.first;
    }
};

int main() {
    ExpiringCache cache;
    int choice;
    string key, value;
    int expiryMs;

    while (true) {
        cout << "\n--- Expiring Cache Menu ---\n";
        cout << "1. Set Key\n";
        cout << "2. Get Key\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                cout << "Enter expiry time (ms): ";
                cin >> expiryMs;
                cache.set(key, value, expiryMs);
                break;
            case 2:
                cout << "Enter key: ";
                cin >> key;
                cout << cache.get(key) << endl;
                break;
            case 3:
                cout << "Program Closed.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
