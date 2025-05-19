#ifndef BRAIN_H
#define BRAIN_H

#include "interval.h"

using namespace std;
using namespace interval_arithmetic;
using namespace mpfr;

#define a_length 63
#define cout_precision 100

void interval_derivative(
    const Interval<mpreal> function[a_length],
    Interval<mpreal> derivative_function[a_length]
);

Interval<mpreal> interval_function_value(
    Interval<mpreal> x,
    Interval<mpreal> a[a_length],
    int stopien
);

Interval<mpreal> interval_root_Newton(
    Interval<mpreal> initial_guess,
    Interval<mpreal> function[a_length],
    Interval<mpreal> derivative_function[a_length],
    int stopien
);

void derivative(
    mpreal function[a_length],
    mpreal derivative_function[a_length]
);

mpreal function_value(
    mpreal x,
    mpreal a[a_length],
    int stopien
);

mpreal root_Newton(
    mpreal initial_guess,
    mpreal function[a_length],
    mpreal derivative_function[a_length],
    int stopien
);

#endif