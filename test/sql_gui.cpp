/**
 * @author      : alex (alex@mac.local)
 * @file        : sql_gui
 * @created     : Sâmbătă Mar 30, 2024 20:46:01 EET
 */

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Window.H>

extern "C" {
extern void *main_x(void *);
extern char *txt;
}

void cb(Fl_Widget *w, void *data) {
  Fl_Input *input = (Fl_Input *)data;
  Fl_Output *output = (Fl_Output *)data;
  const char *text = input->value();
  main_x((void *)text);
  output->value(txt);
}

int main(void) {
  Fl_Window *window = new Fl_Window(340, 180, "Simple SQL GUI");
  Fl_Input *input = new Fl_Input(20, 40, 300, 30, "SQL command:");
  Fl_Button *button = new Fl_Button(20, 80, 300, 30, "Execute");
  Fl_Output *output = new Fl_Output(20, 120, 300, 30, "Output:");

  button->callback(cb, input);

  window->end();
  window->show();

  return Fl::run();
}
