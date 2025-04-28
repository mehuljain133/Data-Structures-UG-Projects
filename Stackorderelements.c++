/* WAP to reverse the order of the elements in the stack using additional stack.
WAP to reverse the order of the elements in the stack using additional Queue */

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class StackReversal {
public:
    // Method 1: Reverse stack using an additional stack
    static void reverseUsingStack(stack<int>& s) {
        stack<int> tempStack;

        // Move elements from original stack to temporary stack
        while (!s.empty()) {
            tempStack.push(s.top());
            s.pop();
        }

        // Move elements back from tempStack to original stack
        while (!tempStack.empty()) {
            s.push(tempStack.top());
            tempStack.pop();
        }
    }

    // Method 2: Reverse stack using an additional queue
    static void reverseUsingQueue(stack<int>& s) {
        queue<int> tempQueue;

        // Move elements from stack to queue
        while (!s.empty()) {
            tempQueue.push(s.top());
            s.pop();
        }

        // Move elements back from queue to stack
        while (!tempQueue.empty()) {
            s.push(tempQueue.front());
            tempQueue.pop();
        }
    }

    // Utility function to print stack elements
    static void printStack(stack<int>& s) {
        stack<int> tempStack = s;
        while (!tempStack.empty()) {
            cout << tempStack.top() << " ";
            tempStack.pop();
        }
        cout << endl;
    }
};

int main() {
    // Create a stack and push elements onto it
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    // Print original stack
    cout << "Original Stack: ";
    StackReversal::printStack(s);

    // Reverse using additional stack
    StackReversal::reverseUsingStack(s);
    cout << "Stack after reverse using stack: ";
    StackReversal::printStack(s);

    // Recreate the stack for the next operation
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    // Reverse using additional queue
    StackReversal::reverseUsingQueue(s);
    cout << "Stack after reverse using queue: ";
    StackReversal::printStack(s);

    return 0;
}
