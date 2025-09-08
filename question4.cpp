#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// Define TaylorTerm struct
struct TaylorTerm {
    int order;
    double coeff;
    double value;
};

void print_taylor_term(int index, int order, double coeff, double value) {
    cout << "Term[" << index << "]: "
         << "order=" << order << ", "
         << "coeff=" << coeff << ", "
         << "value=" << value << "\n";
}

void print_taylor_result(const char* function_name, double x,
                         int terms, double approximation) {
    cout << "Approximation of " << function_name
         << "(x) at x=" << x
         << " with " << terms << " terms: "
         << approximation << "\n";
}

// Function to calculate factorial (could use memoization for speed)
double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Error opening " << argv[1] << endl;
        return 1;
    }

    double x;
    int terms;
    input >> x >> terms;

    if (terms <= 0) {
        cerr << "Number of terms must be positive\n";
        return 1;
    }

    // Create array of TaylorTerm dynamically (C++11 or later)
    TaylorTerm* series = new TaylorTerm[terms];

    double approximation = 0.0;

    // Calculate terms for exp(x): term k = x^k / k!
    for (int k = 0; k < terms; ++k) {
        double coeff = 1.0 / factorial(k);
        double value = coeff * pow(x, k);

        series[k].order = k;
        series[k].coeff = coeff;
        series[k].value = value;

        approximation += value;

        print_taylor_term(k, k, coeff, value);
    }

    print_taylor_result("exp", x, terms, approximation);

    delete[] series;
    return 0;
}
