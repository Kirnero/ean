#include <iostream>
#include "interval.h"
using namespace std;
using namespace mpfr;
using namespace interval_arithmetic;

#define a_length 63
#define cout_precision 100

void interval_derivative(const Interval<mpreal> a[a_length], Interval<mpreal> d[a_length]){
    for(int i = 1; i<a_length;i++){
        d[i]=a[i-1]*i;
    }
    d[0].a = 0, d[0].b=0;
}


Interval<mpreal> interval_function_value(Interval<mpreal> x, Interval<mpreal> a[a_length], int stopien) {
    Interval<mpreal> wynik=a[0];
    for(int i = 1; i<stopien; i++){
        wynik = wynik*x;
        wynik = wynik + a[i];
    }
    return wynik;
}

Interval<mpreal> interval_root_Newton(Interval<mpreal> initial_guess, Interval<mpreal> function[a_length], Interval<mpreal> derivative_function[a_length], int stopien){
    Interval<mpreal> fx;
    Interval<mpreal> dfx;
    cout.precision(cout_precision);
    for (int iterative = 0; iterative < 100; iterative=iterative+1) {
        fx = interval_function_value(initial_guess, function, stopien);
        dfx = interval_function_value(initial_guess, derivative_function,stopien);
        if(fx.a==0 && fx.b==0) { cout << "End" << endl; break;}
        cout << "Iteration " << iterative+1 << ":\nfx = [" << fx.a << ", " << fx.b << "]" << ";\ndfx = [" << dfx.a << ", " << dfx.b << "]" << endl;
        if (dfx.a < 0 && dfx.b > 0) {break; cout << "Error: dividing by zero in function: interval_root_Newton";} // Avoid division by zero
        initial_guess = initial_guess - fx / dfx;
        cout << "x = [" << initial_guess.a << ", " << initial_guess.b << "]" << endl;
    }
    return initial_guess;
}

void initialize(int stopien, bool czy_interval = 0){

}

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