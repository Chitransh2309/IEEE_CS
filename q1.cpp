#include <iostream>
#include <stack>
using namespace std;

class MinMaxStack {
private:
    stack<int> stk;      
    
    stack<int> minStack;   
    
    stack<int> maxStack;  

public:
  
    void push(int x) {
        stk.push(x);

    
        if (minStack.empty() || x <= minStack.top()) {
            minStack.push(x);
        } else {
            minStack.push(minStack.top());
        }

      
        if (maxStack.empty() || x >= maxStack.top()) {
            maxStack.push(x);
        } else {
            maxStack.push(maxStack.top());
        }
    }

    
    void pop() {
        if (!stk.empty()) {
            stk.pop();
            minStack.pop();
            maxStack.pop();
        }
    }

    int top() {
        return stk.empty() ? -1 : stk.top();
    }

  
    int getMin() {
        return minStack.empty() ? -1 : minStack.top();
    }

    int getMax() {
        return maxStack.empty() ? -1 : maxStack.top();
    }

    bool isEmpty() {
        return stk.empty();
    }
};


int main() {
    MinMaxStack s;
    int choice, value;

    do {
        cout << "\n--- MinMax Stack Menu ---\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Top\n";
        cout << "4. Get Min\n";
        cout << "5. Get Max\n";
        cout << "6. Check if Empty\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> value;
                s.push(value);
                cout << value << " pushed onto the stack.\n";
                break;

            case 2:
                if (!s.isEmpty()) {
                    cout << "Popped element: " << s.top() << endl;
                    s.pop();
                } else {
                    cout << "Stack is empty. Cannot pop.\n";
                }
                break;

            case 3:
                if (!s.isEmpty()) {
                    cout << "Top element: " << s.top() << endl;
                } else {
                    cout << "Stack is empty.\n";
                }
                break;

            case 4:
                if (!s.isEmpty()) {
                    cout << "Minimum element: " << s.getMin() << endl;
                } else {
                    cout << "Stack is empty.\n";
                }
                break;

            case 5:
                if (!s.isEmpty()) {
                    cout << "Maximum element: " << s.getMax() << endl;
                } else {
                    cout << "Stack is empty.\n";
                }
                break;

            case 6:
                cout << (s.isEmpty() ? "Stack is empty." : "Stack is not empty.") << endl;
                break;

            case 7:
                cout << "Program Closed.\n";
                break;

            default:
                cout << "Invalid choice! Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);

    return 0;
}
