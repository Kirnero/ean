#include <iostream>
#include "../include/interval.h"
#include "../include/brain.h"

int main() {
    int stopien =4;
    Interval<mpreal> x; x.a=1, x.b=1; // Initial guess
    Interval<mpreal> interval_function[a_length]; // ex. a={1,2,3} -> x^2 + 2x + 3
    Interval<mpreal> interval_derivative_function[a_length];
    
    interval_function[0].a = 1, interval_function[0].b=1;
    interval_function[1].a = -4, interval_function[1].b=-4;
    interval_function[2].a = 2, interval_function[2].b=2;
    interval_function[3].a = 2, interval_function[3].b=2;
    interval_derivative(interval_function,interval_derivative_function);

    // Print derivative
    cout << "Derivative:"<<endl;for (int iterative = 0; iterative < stopien; iterative=iterative+1) cout << iterative << ": x = [" << interval_derivative_function[iterative].a << ", " << interval_derivative_function[iterative].b << "]" << endl;
    
    x = interval_root_Newton(x, interval_function, interval_derivative_function, stopien);

    cout << "Approximate root: " << "x = [" << x.a << ", " << x.b << "]" << endl;
    return 0;
}