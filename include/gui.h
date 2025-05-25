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
extern Fl_Box* output;
extern Fl_Box* log_box;
extern Fl_Box* current_function;
extern int current_choice; // 0 - real; 1 - point-interval; 2 - real interval

struct CallbackDataReal {
    int* stopien;
    int* collected_data;
    mpreal* function;
};

void on_choice_change(
    Fl_Widget* w,
    void*
);

void on_calculate(
    Fl_Widget*,
    void*
);

void get_stopien(Fl_Widget* w, void* stopien);

void get_data_real(Fl_Widget* w, void* callback_data);

void print_saved_function_real(void* callback_data);

#endif