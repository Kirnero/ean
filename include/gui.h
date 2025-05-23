#ifndef GUI_H
#define GUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <string>
using namespace std;

#pragma once
extern Fl_Input* input1;
extern Fl_Input* input2;
extern Fl_Box* output;
extern int current_choice; // 0 - real; 1 - point-interval; 2 - real interval

void on_choice_change(
    Fl_Widget* w,
    void*
);

void on_calculate(
    Fl_Widget*,
    void*
);

#endif