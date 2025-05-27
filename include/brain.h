#ifndef BRAIN_H
#define BRAIN_H

#include "interval.h"

using namespace std;
using namespace interval_arithmetic;
using namespace mpfr;

#define a_length 63
#define cout_precision 100
#define max_root 1e20
#define max_iterations 200

void interval_derivative(
    const Interval<mpreal> function[a_length],
    Interval<mpreal> derivative_function[a_length]
);

void interval_synthetic_division( // 0 ~ stopien-2 -> quotient
    Interval<mpreal> root,
    Interval<mpreal> function[a_length],
    int stopien,
    Interval<mpreal> destination[a_length]
);

Interval<mpreal> interval_function_value(
    Interval<mpreal> x,
    Interval<mpreal> function[a_length],
    int stopien
);

Interval<mpreal> interval_root_Newton(
    Interval<mpreal> initial_guess,
    Interval<mpreal> function[a_length],
    Interval<mpreal> derivative_function[a_length],
    int stopien,
    int &bisection_counter
);

Interval<mpreal> interval_get_initial_guess(
    Interval<mpreal> function[a_length],
    int stopien,
    mpreal start
);

void interval_all_roots_Newton(
    Interval<mpreal> destination[a_length],
    Interval<mpreal> function[a_length],
    int stopien,
    int bisection_counter[a_length]
);

//Intervals///////////
//////////////////////
/////// Real numbers

void derivative(
    mpreal function[a_length],
    mpreal derivative_function[a_length]
);

void synthetic_division(
    mpreal root,
    mpreal function[a_length],
    int stopien,
    mpreal destination[a_length]
);

mpreal function_value(
    mpreal x,
    mpreal function[a_length],
    int stopien
);

mpreal root_Newton(
    mpreal initial_guess,
    mpreal function[a_length],
    mpreal derivative_function[a_length],
    int stopien
);

void all_roots_Newton(
    mpreal destination[a_length],
    mpreal function[a_length],
    int stopien
);

#endif