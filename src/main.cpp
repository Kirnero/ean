#include <iostream>
#include "../include/interval.h"
#include "../include/brain.h"

void initialize(
    int &stopien,
    mpreal &x,
    mpreal function[a_length],
    mpreal derivative_function[a_length]
){

    stopien = 4;
    x=1;

    function[0]=1,
    function[1]=-4,
    function[2]=2,
    function[3]=2;

    derivative(function, derivative_function);
    // Print derivative
    cout << "Derivative:"<<endl;
    for (int iterative = 0; iterative < stopien; iterative=iterative+1)
        cout << iterative << ": x = " << derivative_function[iterative] << endl;
}

void interval_initialize(
    int &stopien,
    Interval<mpreal> &x,
    Interval<mpreal> interval_function[a_length],
    Interval<mpreal> interval_derivative_function[a_length]
){
    stopien = 3;
    x.a=1, x.b=1; // Initial guess for testing

    interval_function[0].a = 1, interval_function[0].b=1;
    interval_function[1].a = -4, interval_function[1].b=-4;
    interval_function[2].a = 2, interval_function[2].b=2;
    interval_function[3].a = 2, interval_function[3].b=2;

    interval_derivative(interval_function,interval_derivative_function);
    // Print interval derivative
    cout << "Derivative:"<<endl;
    for (int iterative = 0; iterative < stopien; iterative=iterative+1)
        cout << iterative << ": x = [" << interval_derivative_function[iterative].a
        << ", " << interval_derivative_function[iterative].b << "]" << endl;
}

int main() {
    int stopien;
    bool interval_input = false;

    Interval<mpreal> interval_initial_guess; // Initial guess for testing
    Interval<mpreal> interval_function[a_length]; // ex. a={1,2,3} -> x^2 + 2x + 3
    Interval<mpreal> interval_derivative_function[a_length];

    cout.precision(cout_precision);
    mpreal initial_guess;
    mpreal function[a_length];
    mpreal derivative_function[a_length];

    if(interval_input){
        interval_initialize(stopien, interval_initial_guess, interval_function, interval_derivative_function);
    }
    else{
        initialize(stopien, initial_guess, function, derivative_function);
    }
    
    mpreal wynik;
    while(stopien!=0){
        wynik = root_Newton(initial_guess,function,derivative_function,stopien);
        synthetic_division(wynik,function,stopien, function);
        derivative(function,derivative_function);
        stopien--;
        cout << stopien << ": " << wynik << endl;
    }
    
    return 0;
}