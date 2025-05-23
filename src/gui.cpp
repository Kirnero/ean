#include "../include/gui.h"

Fl_Input* input1;
Fl_Input* input2;
Fl_Box* output;
int current_choice=0; // 0 - real; 1 - point-interval; 2 - real interval
static string result;

void on_choice_change(Fl_Widget* w, void*) {
    Fl_Choice* choice = (Fl_Choice*)w;
    current_choice = choice->value();
    input1->label(current_choice == 0 ? "Value A:" : "Value X:");
    input2->label(current_choice == 1 ? "Value B:" : "Value Y:");
}

void on_calculate(Fl_Widget*, void*) {
    string a = input1->value();
    string b = input2->value();
    result = "You entered: " + a + ", " + b + " for choice " + std::to_string(current_choice);
    output->label(result.c_str());
    output->redraw();
}