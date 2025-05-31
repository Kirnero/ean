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
    int collected_data = 0; // NEXT place to fill

    Interval<mpreal> interval_function[a_length]; // ex. a={1,2,3} -> x^2 + 2x + 3
    Interval<mpreal> interval_wynik[a_length];
    int bisection_counter[a_length];

    mpreal::set_default_prec(cout_precision);
    cout.precision(cout_precision);
    mpreal function[a_length];
    mpreal wynik[a_length];

    interval_initialize(stopien, interval_function);
    //for(int i = 0; i<stopien; i++) cout << "Root nr." << i+1 << " / " << stopien << " : [" << interval_wynik[i].a << " ; " << interval_wynik[i].b << "]" << endl;
    initialize(stopien, function);
    //for(int i = 0; i<stopien; i++) cout << wynik[i] << endl;
    

    CallbackDataReal* cbr = new CallbackDataReal{&stopien, &collected_data, function, wynik};
    CallbackDataInterval* cbi = new CallbackDataInterval{&stopien, &collected_data, interval_function, interval_wynik};
    CallbackData* cb = new CallbackData{cbr, cbi};
    
    Fl_Window* win = new Fl_Window(1200, 800, "Pierwiastki wielomianu metodą Newtona / bisekcji");
    win->begin();
    win->position(100,100);

    choice = new Fl_Choice(120, 20, 150, 25, "Typ danych");
    choice->add("Rzeczywiste|Przedziałowe punktowe|Przedziałowe");
    choice->value(0);
    choice->callback(on_choice_change, static_cast<void*>(cb));

    log_box = new Fl_Box(400, 20, 600, 20, "");

    input_prec = new Fl_Input(120, 50, 50, 25, "Dokładność");
    prec_btn = new Fl_Button(300, 50, 80, 30, "Zapisz");
    prec_btn->callback(get_output_prec);

    input1 = new Fl_Input(120, 90, 150, 25, "Stopien:");
    stopien_btn = new Fl_Button(300, 90, 80, 30, "Zapisz");
    stopien_btn->callback(get_stopien, &stopien);

    input2 = new Fl_Input(120, 120, 150, 25, "Wykładnik:");
    wyznacznik_btn = new Fl_Button(300, 120, 80, 30, "Zapisz");
    wyznacznik_btn->callback(get_data_real, static_cast<void*>(cbr));

    input3 = new Fl_Input(120, 120, 150, 25, "Lewa strona:"); input3->hide();
    input4 = new Fl_Input(120, 150, 150, 25, "Prawa strona:"); input4->hide();
    wyznacznik_interval_btn = new Fl_Button(300, 150, 80, 30, "Zapisz"); wyznacznik_interval_btn->hide();
    wyznacznik_interval_btn->callback(get_data_interval, static_cast<void*>(cbi));
    

    current_function = new Fl_Box(400, 50, 600, 600);
    current_function->align(FL_ALIGN_TOP | FL_ALIGN_INSIDE);
    current_function->box(FL_NO_BOX);

    print_saved_function_real(static_cast<void*>(cbr));
    //print_saved_function_interval(static_cast<void*>(cbi));
    interval_all_roots_Newton(interval_wynik, interval_function, stopien, bisection_counter),
    all_roots_Newton(wynik, function, stopien);

    wynik_btn = new Fl_Button(120, 200, 80, 30, "Calculate");
    //btn->callback(on_calculate);
    output = new Fl_Box(10, 240, 380, 20, "Wynik");

    win->end();
    win->show();
    return Fl::run();
}