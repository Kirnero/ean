#include <iostream>
#include "../include/interval.h"
#include "../include/brain.h"
#include "../include/gui.h"

void initialize(
    int &stopien,
    mpreal function[a_length]
){
    stopien = 3;

    function[0]=1,
    function[1]=-4,
    function[2]=2,
    function[3]=2;
}

void interval_initialize(
    int &stopien,
    Interval<mpreal> interval_function[a_length]
){
    stopien = 3;

    interval_function[0].a = 0.98, interval_function[0].b=1.02;
    interval_function[1].a = -4.02, interval_function[1].b=-3.98;
    interval_function[2].a = 1.98, interval_function[2].b=2.02;
    interval_function[3].a = 1.98, interval_function[3].b=2.02;
}

int main() {
    int stopien;
    bool interval_input = true;

    Interval<mpreal> interval_function[a_length]; // ex. a={1,2,3} -> x^2 + 2x + 3
    Interval<mpreal> interval_wynik[a_length];

    mpreal::set_default_prec(256);
    cout.precision(cout_precision);
    mpreal function[a_length];
    mpreal wynik[a_length];


    if(interval_input){
        interval_initialize(stopien, interval_function);
        interval_all_roots_Newton(interval_wynik, interval_function, stopien);
        for(int i = 0; i<stopien; i++){
            cout << "Root nr." << i+1 << " / " << stopien << " : [" << interval_wynik[i].a << " ; " << interval_wynik[i].b << "]" << endl;
        }

    }
    else{
        initialize(stopien, function);
        all_roots_Newton(wynik, function, stopien);
        for(int i = 0; i<stopien; i++){
            cout << wynik[i] << endl;
        }

    }
    
    Fl_Window* win = new Fl_Window(400, 200, "Hello");
    win->begin();
    win->position(100,100);
    
    Fl_Choice* choice = new Fl_Choice(120, 20, 150, 25, "Typ danych");
    choice->add("Rzeczywiste punktowe|Rzeczywiste przedziałowe punktowe|Rzeczywiste przedziałowe");
    choice->value(0);
    choice->callback(on_choice_change);

    input1 = new Fl_Input(120, 60, 150, 25, "Value A:");
    input2 = new Fl_Input(120, 90, 150, 25, "Value B:");
    Fl_Button* btn = new Fl_Button(120, 130, 80, 30, "Calculate");
    btn->callback(on_calculate);
    output = new Fl_Box(10, 170, 380, 20, "Wynik");

    win->end();
    win->show();
    return Fl::run();
}