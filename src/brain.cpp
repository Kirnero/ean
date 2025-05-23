#include "../include/brain.h"

mpreal width(Interval<mpreal> x){
    return x.b - x.a;
}

Interval<mpreal> intersect(Interval<mpreal> a, Interval<mpreal> b) {
    Interval<mpreal> new_interval;
    new_interval.a = max(a.a, b.a);
    new_interval.b = min(a.b, b.b);
    if (new_interval.a > new_interval.b) {
        throw std::runtime_error("Empty intersection — no root in this interval");
    }
    
    return new_interval;
}

void interval_derivative(
    const Interval<mpreal> function[a_length],
    Interval<mpreal> derivative_function[a_length]
){
    for(int i = 1; i<a_length;i++){
        derivative_function[i]=function[i-1]*i;
    }
    derivative_function[0].a = 0, derivative_function[0].b=0;
}

void interval_synthetic_division( // 0 ~ stopien-2 -> quotient
    Interval<mpreal> root,
    Interval<mpreal> function[a_length],
    int stopien,
    Interval<mpreal> destination[a_length]
){
    destination[0] = function[0];
    for(int i = 1; i <= stopien-1; i++){
        destination[i] = destination[i-1] * root + function[i];
    }
    destination[stopien].a = 0, destination[stopien].b=0,
    destination[stopien+1].a = 0, destination[stopien+1].b=0;
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

Interval<mpreal> midpoint_bisection(
    Interval<mpreal> x,
    Interval<mpreal> function[a_length],
    int stopien
){
    Interval<mpreal> left;
    Interval<mpreal> right;
    mpreal midpoint = (x.a + x.b)/2;
    left.a=x.a, left.b=midpoint;
    right.a=midpoint, right.b=x.b;

    Interval<mpreal> f_left = interval_function_value(left, function, stopien);
    Interval<mpreal> f_right = interval_function_value(right, function, stopien);

    if(f_left.a * f_left.b <= 0){
        return left;
    }
    else{
        return right;
    }
}

Interval<mpreal> interval_root_Newton(
    Interval<mpreal> initial_guess,
    Interval<mpreal> function[a_length],
    Interval<mpreal> derivative_function[a_length],
    int stopien
){
    Interval<mpreal> fx; //value of function
    Interval<mpreal> dfx; //value of derivative
    Interval<mpreal> next_guess;
    Interval<mpreal> midpoint;
    mpreal epsilon = 1e-14;
    //cout << epsilon << endl;
    cout.precision(cout_precision);
    //cout << "Initial guess : [" << initial_guess.a << " ; " << initial_guess.b << "]" << endl;
    int iterative = 1; // How many iterations it takes

    while(width(initial_guess) > epsilon) {
        midpoint.a = (initial_guess.a+initial_guess.b)/2; midpoint.b=midpoint.a;
        fx = interval_function_value(midpoint, function, stopien);
        dfx = interval_function_value(initial_guess, derivative_function,stopien);

        if(fx.a==0 && fx.b==0){ // End if f(x)=0 is found
            cout << "End" << endl;
            break;}
        if (dfx.a < 0 && dfx.b > 0) { // Avoid division by zero
            cout << "Error: dividing by zero in function: interval_root_Newton";
            break;}
        next_guess = midpoint - fx / dfx;
        next_guess = intersect(initial_guess, next_guess);

        if(width(next_guess) < width(initial_guess)){
            initial_guess = next_guess;
        }
        else{ // Newton did it worse, doing bisection instead
            //cout << iterative;
            initial_guess = midpoint_bisection(initial_guess, function, stopien);
        }
        //cout << "\n" << iterative << " : [" << initial_guess.a << " ; " << initial_guess.b << "]" << endl;
        iterative++;
        //cout << width(initial_guess) << endl;
    }
    //cout << iterative << endl;
    return initial_guess;
}

Interval<mpreal> interval_get_initial_guess(
    Interval<mpreal> function[a_length],
    int stopien
){
    Interval<mpreal> guess; guess.a=1, guess.b=1;
    mpreal eps=1e-2;
    for (mpreal x = 0; x < 10; x += eps) {
        Interval<mpreal> left, right;
        left.a = x; left.b = x;
        right.a = x+eps; right.b = x+eps;
        Interval<mpreal> f_left = interval_function_value(left, function, stopien);
        Interval<mpreal> f_right = interval_function_value(right, function, stopien);
        if (f_left.a * f_right.b <= 0) {
            // Zmiana znaku lub zero w przedziale [x, x+eps], nie powinno byc zera ale nadal
            guess.a = x; guess.b = x+eps;
            // Użyj guess jako initial_guess
            return guess;
        }
        right.a = -x; right.b = -x;
        left.a = -x-eps; left.b = -x-eps;
        f_left = interval_function_value(left, function, stopien);
        f_right = interval_function_value(right, function, stopien);
        if (f_left.a * f_right.b <= 0) {
            // Zmiana znaku lub zero w przedziale [-x-eps, -x], nie powinno byc zera ale nadal
            guess.a = -x-eps; guess.b = -x;
            // Użyj guess jako initial_guess
            return guess;
        }
    }
    return guess;
}

void interval_all_roots_Newton(
    Interval<mpreal> destination[a_length],
    Interval<mpreal> function[a_length],
    int stopien
){
    Interval<mpreal> initial_guess;
    Interval<mpreal> derivative_function[a_length]; interval_derivative(function, derivative_function);
    int stopien_copy = stopien;

    for(int i = 0; i < stopien_copy; i++){
        initial_guess = interval_get_initial_guess(function, stopien);
        destination[i] = interval_root_Newton(initial_guess, function, derivative_function, stopien);
        interval_synthetic_division(destination[i], function, stopien, function);
        interval_derivative(function, derivative_function);
        stopien--;
        //cout << "Root nr. " << i+1 << " / " << stopien_copy << " : [" << destination[i].a << " ; " << destination[i].b << "]" << endl;
    }
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