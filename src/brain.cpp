#include "../include/brain.h"


void interval_derivative(
    const Interval<mpreal> function[a_length],
    Interval<mpreal> derivative_function[a_length]
){
    for(int i = 1; i<=a_length;i++){
        derivative_function[i]=function[i-1]*i;
    }
    derivative_function[0].a = 0, derivative_function[0].b=0;
}


Interval<mpreal> interval_function_value(
    Interval<mpreal> x,
    Interval<mpreal> function[a_length],
    int stopien
){
    Interval<mpreal> wynik=function[0];
    for(int i = 1; i<=stopien; i++){
        wynik = wynik * x;
        wynik = wynik + function[i];
    }
    return wynik;
}

Interval<mpreal> interval_root_Newton(
    Interval<mpreal> initial_guess,
    Interval<mpreal> function[a_length],
    Interval<mpreal> derivative_function[a_length],
    int stopien
){
    Interval<mpreal> fx; //value of function
    Interval<mpreal> dfx; //value of derivative
    cout.precision(cout_precision);
    for (int iterative = 0; iterative < 100; iterative=iterative+1) {
        fx = interval_function_value(initial_guess, function, stopien);
        dfx = interval_function_value(initial_guess, derivative_function,stopien);
        if(fx.a==0 && fx.b==0){ // End if f(x)=0 is found
            cout << "End" << endl;
            break;}
        if (dfx.a < 0 && dfx.b > 0) { // Avoid division by zero
            cout << "Error: dividing by zero in function: interval_root_Newton";
            break;}
        initial_guess = initial_guess - fx / dfx;
    }
    return initial_guess;
}

//Intervals///////////
//////////////////////
/////// Real numbers

void derivative(
    mpreal function[a_length],
    mpreal derivative_function[a_length]
){
    for(int i = 1; i < a_length; i++){
        derivative_function[i] = function[i-1] * i;
    }
    derivative_function[0] = 0;
}

void synthetic_division( // 0 ~ stopien-2 -> quotient
    mpreal root,
    mpreal function[a_length],
    int stopien,
    mpreal destination[a_length]
){
    destination[0] = function[0];
    for(int i = 1; i <= stopien-1; i++){
        destination[i] = destination[i-1] * root + function[i];
    }
    destination[stopien]=0, destination[stopien+1]=0;
}

mpreal function_value(
    mpreal x,
    mpreal function[a_length],
    int stopien
){
    mpreal wynik=function[0];
    for(int i = 1; i <= stopien; i++){
        wynik = wynik * x;
        wynik = wynik + function[i];
    }
    return wynik;
}

mpreal root_Newton(
    mpreal initial_guess,
    mpreal function[a_length],
    mpreal derivative_function[a_length],
    int stopien
){
    mpreal fx; //value of function
    mpreal dfx; //value of derivative
    for (int iterative = 0; iterative < 100; iterative=iterative+1) {
        fx = function_value(initial_guess, function, stopien);
        dfx = function_value(initial_guess, derivative_function,stopien);
        if(fx == 0){ // End if f(x)=0 is found
            cout << "Interrupt: got f(x) == 0" << endl;
            break;}
        if (dfx == 0) { // Avoid division by zero
            cout << "Error: dividing by zero in function: root_Newton";
            break;}
        initial_guess = initial_guess - fx / dfx;
    }
    //cout << initial_guess << endl;
    return initial_guess;
}

void all_roots_Newton(
    mpreal destination[a_length],
    mpreal function[a_length],
    int stopien
){
    mpreal initial_guess = 1;
    mpreal derivative_function[a_length]; derivative(function, derivative_function);
    int stopien_copy = stopien;

    for(int i = 0; i < stopien_copy; i++){
        destination[i] = root_Newton(initial_guess, function, derivative_function, stopien);
        synthetic_division(destination[i], function, stopien, function);
        derivative(function, derivative_function);
        stopien--;
        cout << "Root nr. " << i+1 << " / " << stopien_copy << " : " << destination[i] << endl;
    }
}