#include "../include/gui.h"

Fl_Input* input1;
Fl_Input* input2;
Fl_Input* input3;
Fl_Input* input4;
Fl_Input* input_prec;
Fl_Box* output;
Fl_Box* current_function;
Fl_Box* log_box;
Fl_Choice* choice;
Fl_Button* stopien_btn;
Fl_Button* wyznacznik_btn;
Fl_Button* wyznacznik_interval_btn;
Fl_Button* wynik_btn;
Fl_Button* prec_btn;
int current_choice=0; // 0 - real; 1 - point-interval; 2 - real interval
string output_str;
string function_str;
int output_prec=5;

void initialize(
    void* data
){
    CallbackDataReal* cb = static_cast<CallbackDataReal*>(data);

    mpreal* wynik = static_cast<mpreal*>(cb->function);
    int* stopien_ptr = static_cast<int*>(cb->stopien);
    int* collected_data_ptr = static_cast<int*>(cb->collected_data);

    *stopien_ptr = 3;

    wynik[0]=1,
    wynik[1]=-4,
    wynik[2]=2,
    wynik[3]=2;
}

void interval_initialize_point(
    void* data
){
    CallbackDataInterval* cb = static_cast<CallbackDataInterval*>(data);

    Interval<mpreal>* interval_function = static_cast<Interval<mpreal>*>(cb->function);
    int* stopien_ptr = static_cast<int*>(cb->stopien);
    int* collected_data_ptr = static_cast<int*>(cb->collected_data);

    *stopien_ptr = 3;

    interval_function[0].a = 1, interval_function[0].b=1;
    interval_function[1].a = -4, interval_function[1].b=-4;
    interval_function[2].a = 2, interval_function[2].b=2;
    interval_function[3].a = 2, interval_function[3].b=2;
}

void interval_initialize(
    void* data
){
    CallbackDataInterval* cb = static_cast<CallbackDataInterval*>(data);

    Interval<mpreal>* interval_function = static_cast<Interval<mpreal>*>(cb->function);
    int* stopien_ptr = static_cast<int*>(cb->stopien);
    int* collected_data_ptr = static_cast<int*>(cb->collected_data);

    *stopien_ptr = 3;

    interval_function[0].a = 0.98, interval_function[0].b=1.02;
    interval_function[1].a = -4.02, interval_function[1].b=-3.98;
    interval_function[2].a = 1.98, interval_function[2].b=2.02;
    interval_function[3].a = 1.98, interval_function[3].b=2.02;
}

void on_choice_change(Fl_Widget* w, void* data) {
    CallbackData* cb = static_cast<CallbackData*>(data);

    CallbackDataReal* cbr = static_cast<CallbackDataReal*>(cb->callback_data_real);
    CallbackDataInterval* cbi = static_cast<CallbackDataInterval*>(cb->callback_data_interval);
    int* collected_data_real = static_cast<int*>(cbr->collected_data);
    int* collected_data_interval = static_cast<int*>(cbi->collected_data);

    current_choice = choice->value();
    
    if(current_choice==0){
        (*collected_data_real)=0;
        wyznacznik_btn->callback(get_data_real, static_cast<void*>(cbr));
        input3->hide();
        input4->hide();
        wyznacznik_interval_btn->hide();

        input2->show();
        wyznacznik_btn->show();

        wynik_btn->callback(wynik_real, static_cast<void*>(cbr));

        initialize(static_cast<void*>(cbr));
        print_saved_function_real(static_cast<void*>(cbr));
    }
    else if(current_choice==1){
        (*collected_data_interval)=0;
        wyznacznik_btn->callback(get_data_interval_point, static_cast<void*>(cbi));
        input3->hide();
        input4->hide();
        wyznacznik_interval_btn->hide();

        input2->show();
        wyznacznik_btn->show();

        wynik_btn->callback(wynik_interval, static_cast<void*>(cbi));

        interval_initialize_point(static_cast<void*>(cbi));
        print_saved_function_interval(static_cast<void*>(cbi));
    }
    else if(current_choice==2){
        (*collected_data_interval)=0;
        wyznacznik_btn->callback(get_data_interval, static_cast<void*>(cbi));
        input3->show();
        input4->show();
        wyznacznik_interval_btn->show();

        input2->hide();
        wyznacznik_btn->hide();

        wynik_btn->callback(wynik_interval, static_cast<void*>(cbi));

        interval_initialize(static_cast<void*>(cbi));
        print_saved_function_interval(static_cast<void*>(cbi));
    }
    log_box->label("Zmiana typu danych, wyczyszczono wprowadzone dane i ustawiono domyślne");
    log_box->redraw();
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
        log_box->label("Error: Wartość stopnia wielomianu musi być liczbą naturalną mniejszą od a_length");
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

    if((*collected_data_ptr)==0){
        for(int i = 0; i<a_length; i++){
            wynik[i]=0;
        }
    }

    wynik[*collected_data_ptr] = data;
    (*collected_data_ptr)++;
    print_saved_function_real(callback_data);
    log_box->label("Sukces: Pomyślnie zapisano wykładnik funkcji");
    log_box->redraw();
}

void get_data_interval_point(Fl_Widget* w, void* callback_data){
    CallbackDataInterval* cb = static_cast<CallbackDataInterval*>(callback_data);

    Interval<mpreal>* wynik = static_cast<Interval<mpreal>*>(cb->function);
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
        log_box->label("Error: Wartość granic przediału wykładnika musi być liczbą rzeczywistą");
        log_box->redraw();
        return;
    }

    if((*collected_data_ptr)==0){
        for(int i = 0; i<a_length; i++){
            wynik[i].a=0;
            wynik[i].b=0;
        }
    }

    wynik[*collected_data_ptr].a = data;
    wynik[*collected_data_ptr].b = data;
    (*collected_data_ptr)++;
    print_saved_function_interval(callback_data);
    log_box->label("Sukces: Pomyślnie zapisano wykładnik funkcji");
    log_box->redraw();
}

void get_data_interval(Fl_Widget* w, void* callback_data){
    CallbackDataInterval* cb = static_cast<CallbackDataInterval*>(callback_data);

    Interval<mpreal>* wynik = static_cast<Interval<mpreal>*>(cb->function);
    int* stopien_ptr = static_cast<int*>(cb->stopien);
    int* collected_data_ptr = static_cast<int*>(cb->collected_data);

    if(*stopien_ptr<*collected_data_ptr){
        log_box->label("Error: Podano więcej wyznaczników funkcji niż wynosi stopien");
        log_box->redraw();
        return;
    }
    
    string data = input3->value();
    string data2 = input4->value();

    try {
        std::stod(data);  // if this throws, input is invalid
        std::stod(data2);
    } catch (...) {
        log_box->label("Error: Wartość granic przediału wykładnika musi być liczbą rzeczywistą");
        log_box->redraw();
        return;
    }

    if((*collected_data_ptr)==0){
        for(int i = 0; i<a_length; i++){
            wynik[i].a=0;
            wynik[i].b=0;
        }
    }

    wynik[*collected_data_ptr].a = data;
    wynik[*collected_data_ptr].b = data2;
    (*collected_data_ptr)++;
    print_saved_function_interval(callback_data);
    log_box->label("Sukces: Pomyślnie zapisano wykładnik funkcji");
    log_box->redraw();
}

void print_saved_function_real(void* callback_data) {
    CallbackDataReal* cbr = static_cast<CallbackDataReal*>(callback_data);
    mpreal* function_ptr = static_cast<mpreal*>(cbr->function);
    int* stopien_ptr = static_cast<int*>(cbr->stopien);
    int* collected_data_ptr = static_cast<int*>(cbr->collected_data);

    std::ostringstream oss;
    if(*stopien_ptr - *collected_data_ptr >=0) oss << "Teraz zapisujesz x_(" << *stopien_ptr - *collected_data_ptr << ")";
    else oss << "Zapisano już całą funkcję";
    oss << "\nDotychczasowo zapisane dane:";
    
    for (int i = 0; i <= *stopien_ptr; i++) {
        oss << "\nx_(" << *stopien_ptr - i << ") : " << function_ptr[i];
    }
    function_str = oss.str();

    oss.str("");
    oss.clear();

    current_function->label(function_str.c_str());
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
    function_str = oss.str();

    oss.str("");
    oss.clear();

    current_function->copy_label(function_str.c_str());
    current_function->redraw();
}

void wynik_real(Fl_Widget* w, void* callback_data) {
    CallbackDataReal* cbr = static_cast<CallbackDataReal*>(callback_data);
    mpreal* wynik = static_cast<mpreal*>(cbr->wynik);
    mpreal* function = static_cast<mpreal*>(cbr->function);
    int* stopien_ptr = static_cast<int*>(cbr->stopien);

    std::ostringstream oss;
    int count = all_roots_Newton(wynik, function, *stopien_ptr);
    if(count==-1){
        log_box->label("Podana funkcja nie posiada pierwiastków");
        log_box->redraw();
    }
    oss << "Pierwiastki zapisanej funkcji:";
    
    for (int i = 0; i < count; i++) {
        oss << "\nRoot nr. " << i+1 << " : " << wynik[i].toString(output_prec);
    }
    output_str = oss.str();

    oss.str("");
    oss.clear();

    output->label(output_str.c_str());
    output->redraw();
}

void wynik_interval(Fl_Widget* w, void* callback_data) {
    CallbackDataInterval* cbr = static_cast<CallbackDataInterval*>(callback_data);
    Interval<mpreal>* wynik = static_cast<Interval<mpreal>*>(cbr->wynik);
    Interval<mpreal>* function = static_cast<Interval<mpreal>*>(cbr->function);
    int* stopien_ptr = static_cast<int*>(cbr->stopien);
    int* bisection_counter = static_cast<int*>(cbr->bisection_counter);

    std::ostringstream oss;

    int count = interval_all_roots_Newton(wynik, function, *stopien_ptr, bisection_counter);
    if(count==-1){
        log_box->label("Podana funkcja nie posiada pierwiastków");
        log_box->redraw();
    }
    oss << "Pierwiastki zapisanej funkcji:";
    
    for (int i = 0; i < count; i++) {
        oss << "\nRoot nr. " << i+1 << " : [" << wynik[i].a.toString(output_prec) << " ; " << wynik[i].b.toString(output_prec) << "]";
        oss << "    LB: " << bisection_counter[i];
    }
    output_str = oss.str();

    oss.str("");
    oss.clear();

    output->label(output_str.c_str());
    output->redraw();
}