/* WAP to scan a polynomial using linked list and add two polynomial. */

#include <iostream>
using namespace std;

// Node structure for Polynomial
template <typename T>
struct PolyNode {
    T coefficient;
    int exponent;
    PolyNode* next;
    PolyNode(T coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};

template <typename T>
class Polynomial {
private:
    PolyNode<T>* head;

public:
    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        PolyNode<T>* temp = head;
        while (temp != nullptr) {
            PolyNode<T>* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }

    // Function to insert a new term in the polynomial
    void insertTerm(T coefficient, int exponent) {
        PolyNode<T>* newTerm = new PolyNode<T>(coefficient, exponent);
        if (head == nullptr || head->exponent < exponent) {
            newTerm->next = head;
            head = newTerm;
            return;
        }

        PolyNode<T>* temp = head;
        while (temp->next != nullptr && temp->next->exponent > exponent) {
            temp = temp->next;
        }

        if (temp->next != nullptr && temp->next->exponent == exponent) {
            temp->next->coefficient += coefficient;
            delete newTerm; // If the exponent is the same, just update the coefficient
        } else {
            newTerm->next = temp->next;
            temp->next = newTerm;
        }
    }

    // Function to scan and insert a polynomial
    void scanPolynomial() {
        int n;
        cout << "Enter the number of terms in the polynomial: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            T coeff;
            int exp;
            cout << "Enter coefficient and exponent of term " << i + 1 << ": ";
            cin >> coeff >> exp;
            insertTerm(coeff, exp);
        }
    }

    // Function to add two polynomials
    Polynomial<T> addPolynomials(const Polynomial<T>& poly2) {
        Polynomial<T> result;
        PolyNode<T>* ptr1 = head;
        PolyNode<T>* ptr2 = poly2.head;

        // Traverse through both polynomials
        while (ptr1 != nullptr || ptr2 != nullptr) {
            if (ptr1 == nullptr) {
                result.insertTerm(ptr2->coefficient, ptr2->exponent);
                ptr2 = ptr2->next;
            } else if (ptr2 == nullptr) {
                result.insertTerm(ptr1->coefficient, ptr1->exponent);
                ptr1 = ptr1->next;
            } else if (ptr1->exponent == ptr2->exponent) {
                result.insertTerm(ptr1->coefficient + ptr2->coefficient, ptr1->exponent);
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            } else if (ptr1->exponent > ptr2->exponent) {
                result.insertTerm(ptr1->coefficient, ptr1->exponent);
                ptr1 = ptr1->next;
            } else {
                result.insertTerm(ptr2->coefficient, ptr2->exponent);
                ptr2 = ptr2->next;
            }
        }

        return result;
    }

    // Function to display the polynomial
    void display() {
        if (head == nullptr) {
            cout << "Polynomial is empty.\n";
            return;
        }

        PolyNode<T>* temp = head;
        while (temp != nullptr) {
            if (temp->coefficient > 0 && temp != head) {
                cout << "+";
            }
            cout << temp->coefficient << "x^" << temp->exponent << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Main function to test polynomial addition
int main() {
    Polynomial<int> poly1, poly2, result;

    cout << "Enter the first polynomial:\n";
    poly1.scanPolynomial();

    cout << "Enter the second polynomial:\n";
    poly2.scanPolynomial();

    cout << "\nFirst Polynomial: ";
    poly1.display();

    cout << "Second Polynomial: ";
    poly2.display();

    // Add polynomials
    result = poly1.addPolynomials(poly2);

    cout << "\nResultant Polynomial after addition: ";
    result.display();

    return 0;
}
