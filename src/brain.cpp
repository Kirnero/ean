#include "../include/brain.h"


void interval_derivative(const Interval<mpreal> function[a_length], Interval<mpreal> derivative_function[a_length]){
    for(int i = 1; i<a_length;i++){
        derivative_function[i]=function[i-1]*i;
    }
    derivative_function[0].a = 0, derivative_function[0].b=0;
}


Interval<mpreal> interval_function_value(Interval<mpreal> x, Interval<mpreal> function[a_length], int stopien) {
    Interval<mpreal> wynik=function[0];
    for(int i = 1; i<stopien; i++){
        wynik = wynik * x;
        wynik = wynik + function[i];
    }
    return wynik;
}

Interval<mpreal> interval_root_Newton(
Interval<mpreal> initial_guess,
Interval<mpreal> function[a_length],
Interval<mpreal> derivative_function[a_length],
int stopien)
{
    Interval<mpreal> fx; //value of function
    Interval<mpreal> dfx; //value of derivative
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