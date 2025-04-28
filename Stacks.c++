/* Stacks: Array and linked representation of stacks, comparison of the operations on stacks in the
two representations, implementing multiple stacks in an array; applications of stacks: prefix,
infix and postfix expressions, utility and conversion of these expressions from one to another;
applications of stacks to recursion: developing recursive solutions to simple problems,
advantages and limitations of recursion */

#include <iostream>
#include <stack>
#include <string>
#include <cctype>  // for isdigit
using namespace std;

// 1. Array-based Stack
class ArrayStack {
private:
    int* arr;
    int top;
    int capacity;

public:
    ArrayStack(int size) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    ~ArrayStack() {
        delete[] arr;
    }

    void push(int val) {
        if (top == capacity - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = val;
    }

    void pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }

    int peek() {
        if (top == -1) {
            cout << "Stack Empty\n";
            return -1;
        }
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }

    void display() {
        cout << "Array Stack: ";
        for (int i = 0; i <= top; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

// 2. Linked-list-based Stack
struct StackNode {
    int data;
    StackNode* next;
    StackNode(int val) : data(val), next(nullptr) {}
};

class LinkedStack {
private:
    StackNode* top;

public:
    LinkedStack() : top(nullptr) {}

    void push(int val) {
        StackNode* newNode = new StackNode(val);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) {
            cout << "Stack Underflow\n";
            return;
        }
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }

    int peek() {
        if (!top) {
            cout << "Stack Empty\n";
            return -1;
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void display() {
        cout << "Linked Stack: ";
        StackNode* temp = top;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// 3. Multiple Stacks in One Array
class MultiStack {
private:
    int* arr;
    int* top;
    int* next;
    int n, k, free;

public:
    MultiStack(int n, int k) {
        this->n = n;
        this->k = k;
        arr = new int[n];
        top = new int[k];
        next = new int[n];

        for (int i = 0; i < k; i++) top[i] = -1;
        for (int i = 0; i < n - 1; i++) next[i] = i + 1;
        next[n - 1] = -1;
        free = 0;
    }

    void push(int val, int sn) {
        if (free == -1) {
            cout << "Stack Overflow\n";
            return;
        }

        int i = free;
        free = next[i];
        next[i] = top[sn];
        top[sn] = i;
        arr[i] = val;
    }

    void pop(int sn) {
        if (top[sn] == -1) {
            cout << "Stack Underflow\n";
            return;
        }

        int i = top[sn];
        top[sn] = next[i];
        next[i] = free;
        free = i;
    }

    int peek(int sn) {
        if (top[sn] == -1) {
            cout << "Stack Empty\n";
            return -1;
        }
        return arr[top[sn]];
    }
};

// 4. Stack Applications
// Helper for operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Infix to Postfix Conversion
string infixToPostfix(string exp) {
    stack<char> s;
    string output;
    for (char ch : exp) {
        if (isalnum(ch)) {
            output += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                output += s.top();
                s.pop();
            }
            if (!s.empty()) s.pop(); // pop '('
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                output += s.top();
                s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.empty()) {
        output += s.top();
        s.pop();
    }
    return output;
}

// Postfix Evaluation
int evaluatePostfix(string exp) {
    stack<int> s;
    for (char ch : exp) {
        if (isdigit(ch))
            s.push(ch - '0');
        else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();
            switch (ch) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.top();
}

// 5. Recursion Example - Factorial
int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

void explainRecursion() {
    cout << "Advantages of Recursion:\n";
    cout << "- Simplifies code for problems with repetitive sub-problems (like tree traversals).\n";
    cout << "- Useful for Divide and Conquer algorithms.\n\n";
    cout << "Limitations of Recursion:\n";
    cout << "- Can lead to stack overflow if too deep.\n";
    cout << "- Overhead of function calls makes it slower compared to iteration in some cases.\n";
}

void compareStacks() {
    cout << "Comparison of Array Stack vs Linked Stack:\n";
    cout << "Array Stack:\n- Faster (contiguous memory)\n- Fixed size (unless resized)\n\n";
    cout << "Linked Stack:\n- Dynamic size\n- Slightly slower (due to pointer overhead)\n";
}

int main() {
    // Array Stack
    ArrayStack astack(5);
    astack.push(10);
    astack.push(20);
    astack.display();
    astack.pop();
    astack.display();
    cout << "ArrayStack peek: " << astack.peek() << "\n\n";

    // Linked Stack
    LinkedStack lstack;
    lstack.push(100);
    lstack.push(200);
    lstack.display();
    lstack.pop();
    lstack.display();
    cout << "LinkedStack peek: " << lstack.peek() << "\n\n";

    // Multi Stack
    MultiStack ms(10, 3);
    ms.push(15, 0);
    ms.push(45, 2);
    ms.push(17, 1);
    cout << "Top of Stack 0: " << ms.peek(0) << endl;
    cout << "Top of Stack 1: " << ms.peek(1) << endl;
    cout << "Top of Stack 2: " << ms.peek(2) << "\n\n";

    // Expression Handling
    string infix = "(1+2)*(3+4)";
    string postfix = infixToPostfix(infix);
    cout << "Infix Expression: " << infix << endl;
    cout << "Postfix Expression: " << postfix << endl;
    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << "\n\n";

    // Recursion Example
    cout << "Factorial of 5: " << factorial(5) << "\n\n";

    // Recursion Explanation
    explainRecursion();

    // Stack Comparison
    compareStacks();

    return 0;
}
