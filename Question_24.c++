#include <iostream>
#include <stack>

using namespace std;

// Function to calculate factorial using stack
unsigned long long factorial(int n) {
    stack<unsigned long long> s;
    unsigned long long fact = 1;

    // Push numbers from 1 to n onto stack
    for (int i = 1; i <= n; ++i) {
        s.push(i);
    }

    // Multiply numbers from stack to calculate factorial
    while (!s.empty()) {
        fact *= s.top();
        s.pop();
    }

    return fact;
}

// Function to generate Fibonacci series using stack
void fibonacci(int n) {
    stack<unsigned long long> s;
    unsigned long long first = 0, second = 1;

    // Push first two Fibonacci numbers onto stack
    s.push(second);
    s.push(first);

    cout << "Fibonacci series up to " << n << " terms: ";

    // Generate Fibonacci series using stack
    for (int i = 0; i < n; ++i) {
        unsigned long long next = first + second;
        cout << first << " ";
        first = second;
        second = next;
        s.push(next);
    }
    cout << endl;
}

int main() {
    int num;

    // Calculate factorial
    cout << "Enter a number to calculate factorial: ";
    cin >> num;
    cout << "Factorial of " << num << " is: " << factorial(num) << endl;

    // Generate Fibonacci series
    cout << "Enter the number of terms in Fibonacci series: ";
    cin >> num;
    fibonacci(num);

    return 0;
}
