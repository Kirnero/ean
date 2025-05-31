#ifndef GUI_H
#define GUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <string>
#include "../include/brain.h"
using namespace std;

#pragma once
extern Fl_Input* input1;
extern Fl_Input* input2;
extern Fl_Input* input3;
extern Fl_Input* input4;
extern Fl_Input* input_prec;
extern Fl_Box* output;
extern Fl_Box* log_box;
extern Fl_Box* current_function;
extern Fl_Choice* choice;
extern Fl_Button* stopien_btn;
extern Fl_Button* wyznacznik_btn;
extern Fl_Button* wyznacznik_interval_btn;
extern Fl_Button* wynik_btn;
extern Fl_Button* prec_btn;
extern int current_choice; // 0 - real; 1 - point-interval; 2 - real interval
extern int output_prec;

struct CallbackDataReal {
    int* stopien;
    int* collected_data;
    mpreal* function;
    mpreal* wynik;
};

struct CallbackDataInterval {
    int* stopien;
    int* collected_data;
    Interval<mpreal>* function;
    Interval<mpreal>* wynik;
};

struct CallbackData {
    CallbackDataReal* callback_data_real;
    CallbackDataInterval* callback_data_interval;
};

void on_choice_change(Fl_Widget* w, void* data);

void get_stopien(Fl_Widget* w, void* stopien);
void get_output_prec(Fl_Widget* w, void*);

void get_data_real(Fl_Widget* w, void* callback_data);
void get_data_interval_point(Fl_Widget* w, void* callback_data);
void get_data_interval(Fl_Widget* w, void* callback_data);

void print_saved_function_real(void* callback_data);
void print_saved_function_interval(void* callback_data);

#endif