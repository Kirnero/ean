#include "../include/gui.h"

Fl_Input* input1;
Fl_Input* input2;
Fl_Input* input_prec;
Fl_Box* output;
Fl_Box* current_function;
Fl_Box* log_box;
Fl_Choice* choice;
Fl_Button* stopien_btn;
Fl_Button* wyznacznik_btn;
Fl_Button* wynik_btn;
Fl_Button* prec_btn;
int current_choice=0; // 0 - real; 1 - point-interval; 2 - real interval
//Basically no functional differnce between 1 and 2
string output_str;
int output_prec=5;



void on_choice_change(Fl_Widget* w, void* data) {
    CallbackData* cb = static_cast<CallbackData*>(data);

    CallbackDataReal* cbr = static_cast<CallbackDataReal*>(cb->callback_data_real);
    CallbackDataInterval* cbi = static_cast<CallbackDataInterval*>(cb->callback_data_interval);

    current_choice = choice->value();
    
    if(current_choice==0){
        wyznacznik_btn->callback(get_data_real, static_cast<void*>(cbr));
    }
    else{
        wyznacznik_btn->callback(get_data_interval, static_cast<void*>(cbi));
    }
    
}

void get_output_prec(Fl_Widget* w, void*){
    string canditate = input_prec->value();
    try {
        int test = stoi(canditate);  // if this throws, input is invalid
        if(test<0 || test>=cout_precision) throw 2;
    } catch (...) {
        log_box->label("Error: Wartość dokładności wyników musi być liczbą naturalną");
        log_box->redraw();
        return;
    }
    output_prec = stoi(canditate);
    log_box->label("Sukces: Pomyślnie zapisano dokładnność wyników");
    log_box->redraw();
}

void get_stopien(Fl_Widget* w, void* stopien){
    string canditate = input1->value();
    int* stopien_ptr = static_cast<int*>(stopien);
    try {
        int test = stoi(canditate);  // if this throws, input is invalid
        if(test<0 || test>=a_length) throw 2;
    } catch (...) {
        log_box->label("Error: Wartość stopnia wielomianu musi być liczbą naturalną");
        log_box->redraw();
        return;
    }
    *stopien_ptr = stoi(canditate);
    log_box->label("Sukces: Pomyślnie zapisano zmienną 'stopien'");
    log_box->redraw();
}

void get_data_real(Fl_Widget* w, void* callback_data) {
    CallbackDataReal* cb = static_cast<CallbackDataReal*>(callback_data);

    mpreal* wynik = static_cast<mpreal*>(cb->function);
    int* stopien_ptr = static_cast<int*>(cb->stopien);
    int* collected_data_ptr = static_cast<int*>(cb->collected_data);

    if(*stopien_ptr<*collected_data_ptr){
        log_box->label("Error: Podano więcej wyznaczników funkcji niż wynosi stopien");
        log_box->redraw();
        return;
    }
    
    string data = input2->value();

    try {
        std::stod(data);  // if this throws, input is invalid
    } catch (...) {
        log_box->label("Error: Wartość wykładnika musi być liczbą rzeczywistą");
        log_box->redraw();
        return;
    }

    wynik[*collected_data_ptr] = data;
    (*collected_data_ptr)++;
    print_saved_function_real(callback_data);
    log_box->label("Sukces: Pomyślnie zapisano wykładnik funkcji");
    log_box->redraw();
}

void get_data_interval(Fl_Widget* w, void* callback_data){
    cout << "Sukces" << endl;

}

void print_saved_function_real(void* callback_data) {
    CallbackDataReal* cbr = static_cast<CallbackDataReal*>(callback_data);
    mpreal* function_ptr = static_cast<mpreal*>(cbr->function);
    int* stopien_ptr = static_cast<int*>(cbr->stopien);
    int* collected_data_ptr = static_cast<int*>(cbr->collected_data);

    std::ostringstream oss;
    oss << "Dotychczasowo zapisane dane:";
    for (int i = 0; i <= *stopien_ptr; i++) {
        oss << "\nx_(" << *stopien_ptr - i << ") : " << function_ptr[i];
    }
    output_str = oss.str();

    oss.str("");
    oss.clear();

    current_function->label(output_str.c_str());
    current_function->redraw();
}

void print_saved_function_interval(void* callback_data) {
    CallbackDataInterval* cbr = static_cast<CallbackDataInterval*>(callback_data);
    Interval<mpreal>* function_ptr = static_cast<Interval<mpreal>*>(cbr->function);
    int* stopien_ptr = static_cast<int*>(cbr->stopien);
    int* collected_data_ptr = static_cast<int*>(cbr->collected_data);

    std::ostringstream oss;
    oss << "Dotychczasowo zapisane dane:";
    for (int i = 0; i <= *stopien_ptr; i++) {
        oss << "\nx_(" << *stopien_ptr - i << ") : [" << function_ptr[i].a << " ; " << function_ptr[i].b << "]";
    }
    output_str = oss.str();

    oss.str("");
    oss.clear();

    current_function->copy_label(output_str.c_str());
    current_function->redraw();
}