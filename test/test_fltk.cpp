/**
 * @author      : alex (alex@mac.local)
 * @file        : test_fltk
 * @created     : Sâmbătă Feb 24, 2024 07:37:58 EET
 */

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Window.H>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

class MyButton : public Fl_Button {
 public:
  MyButton(int x, int y, int w, int h, const char* label)
      : Fl_Button(x, y, w, h, label) {}

  int handle(int event) {
    if (event == FL_PUSH) {
      printf("Button was clicked\n");
      return 1;
    }
    return Fl_Button::handle(event);
  }
};

class MyWindow : public Fl_Window {
 public:
  MyWindow(int w, int h, const char* title) : Fl_Window(w, h, title) {
    begin();
    box = new Fl_Box(20, 40, 300, 100, "Hello, World!");
    button = new Fl_Button(20, 160, 300, 40, "Click me");
    input = new Fl_Input(20, 220, 300, 40, "Type here:");
    output = new Fl_Output(20, 280, 300, 40, "Output:");
    text_display = new Fl_Text_Display(20, 340, 300, 100, "Text:");
    text_buffer = new Fl_Text_Buffer();
    text_display->buffer(text_buffer);
    end();
    button->callback(button_cb, this);
    input->callback(input_cb, this);
  }

  static void button_cb(Fl_Widget* widget, void* data) {
    MyWindow* window = (MyWindow*)data;
    window->button_cb();
  }

  void button_cb() { box->label("Button was clicked"); }

  static void input_cb(Fl_Widget* widget, void* data) {
    MyWindow* window = (MyWindow*)data;
    window->input_cb();
  }

  void input_cb() {
    output->value(input->value());
    text_buffer->text(input->value());
  }

 private:
  Fl_Box* box;
  Fl_Button* button;
  Fl_Input* input;
  Fl_Output* output;
  Fl_Text_Display* text_display;
  Fl_Text_Buffer* text_buffer;
  MyButton* mybutton;
};

struct Route {
  const char* label;
  const unsigned int distance;
};

void print(const auto& a) {
  for (const auto e : a) std::cout << e << ' ';
  std::cout << '\n';
}

int main(int argc, char** argv) {
#if 0 

  std::vector<Route> routes = {
      {"Bucharest", 0},   {"Ploiesti", 60},    {"Brasov", 160},
      {"Sibiu", 280},     {"Cluj", 480},       {"Oradea", 600},
      {"Timisoara", 800}, {"Arad", 920},       {"Deva", 1020},
      {"Lugoj", 1120},    {"Mehadia", 1220},   {"Drobeta", 1320},
      {"Craiova", 1420},  {"Pitesti", 1520},   {"Rm. Valcea", 1620},
      {"Sibiu", 1720},    {"Bucharest", 1820},
  };

  /* random_shuffle(routes.begin(), routes.end()); */
  /* for_each(routes.begin(), routes.end(), [](const Route& route) { */
  /*   printf("%s: %d\n", route.label, route.distance); */
  /* }); */

  srand(time(NULL));
  std::srand(unsigned(std::time(0)));
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  std::vector<int> distances;
  distances = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  shuffle(distances.begin(), distances.end(), std::default_random_engine(seed));

  std::cout << "shuffled elements:";
  for (int& x : distances) std::cout << ' ' << x;
  std::cout << '\n';

  random_shuffle(distances.begin(), distances.end());
  /* shuffle(distances.begin(), distances.end(), */
  /* std::default_random_engine(time(NULL))); */

  for_each(distances.begin(), distances.end(),
           [](int distance) { printf("%d\n", distance); });

  /* std::thread t([]() { */
  /*   std::this_thread::sleep_for(std::chrono::seconds(5)); */
  /*   printf("Thread finished\n"); */
  /* }); */

  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it = distances.begin(); it != distances.end();
       ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

#endif

  struct Review {
    const char* title;
    int rating;
  };

  std::vector<Review> review1 = {
      {"The Godfather", 5},
      {"The Shawshank Redemption", 5},
      {"The Dark Knight", 5},
      {"The Godfather: Part II", 5},
      {"12 Angry Boys", 5},
      {"Schindler's List", 5},
      {"The Lord of the Rings: The Return of the King", 5},
      {"Pulp Fiction", 5},
      {"The Good, the Bad and the Ugly", 5},
      {"The Lord of the Rings: The Fellowship of the Ring", 5},
      {"Fight Club", 5},
      {"Forrest Gump", 5},
      {"Inception", 5},
      {"The Lord of the Rings: The Two Towers", 5},
      {"The Matrix", 5},
      {"Goodfellas", 5},
      {"Star Wars: Episode V - The Empire Strikes Back", 5},
  };

  std::random_device rd;
  std::mt19937 g(rd());
  srand(time(NULL));

  shuffle(review1.begin(), review1.end(),
          std::default_random_engine(time(NULL)));

  for_each(review1.begin(), review1.end(), [](const Review& review) {
    printf("%s: %d\n", review.title, review.rating);
  });

  MyWindow window(340, 460, "FLTK Example");
  window.show(argc, argv);
  return Fl::run();
}
