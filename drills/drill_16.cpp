#include "./GUI/GUI.h"

#include <iostream>

using namespace Graph_lib;

struct Lines_window : Graph_lib::Window {
    Lines_window(Point xy, int w, int h, const string& title);
private:

    Open_polyline lines;

    Button next_button;
    Button quit_button;
    In_box next_x;
    In_box next_y;
    Out_box xy_out;
    Menu color_menu;
    Button color_button;
    Menu style_menu;
    Button style_button;

    void change_c(Color c) { lines.set_color(c); }
    void change_s(Line_style s) { lines.set_style(s); }

    void hide_color() { color_menu.hide(); color_button.show(); }
    void hide_style() { style_menu.hide(); style_button.show(); }

    void red_pressed() { change_c(Color::red); hide_color(); }
    void magenta_pressed() { change_c(Color::magenta); hide_color(); }
    void black_pressed() { change_c(Color::black); hide_color(); }
    void yellow_pressed() { change_c(Color::yellow); hide_color(); }
    void blue_pressed() { change_c(Color::blue); hide_color(); }
   
    
    void solid_pressed() { change_s(Line_style::solid); hide_style(); }
    void dot_pressed() { change_s(Line_style::dot); hide_style(); }
    void dash_pressed() { change_s(Line_style::dash); hide_style(); }
    void dashdot_pressed() { change_s(Line_style::dashdot); hide_style(); }
    void dashdotdot_pressed() { change_s(Line_style::dashdotdot); hide_style(); }

    void color_pressed() { color_button.hide(); color_menu.show(); }
    void style_pressed() { style_button.hide(); style_menu.show(); }
    void next();
    void quit();

};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    : Window{xy, w, h, title},
    next_button{Point{x_max() - 150, 0}, 70, 20, "Next point",
        [](Address, Address pw) { reference_to<Lines_window>(pw).next(); }},
    quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit",
        [](Address, Address pw) { reference_to<Lines_window>(pw).quit(); }},
    next_x{Point{x_max() - 310, 0}, 50, 20, "next x:"},
    next_y{Point{x_max() - 210, 0}, 50, 20, "next y:"},
    xy_out{Point{100, 0}, 100, 20, "current (x,y):"},
    color_menu{Point{x_max() - 90, 30}, 80, 20, Menu::vertical, "Color"},
    color_button{Point{x_max() - 90, 30}, 80, 20, "Color menu",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).color_pressed();
        }
    },
    style_menu{Point{10, 30}, 100, 20, Menu::vertical, "Style"},
    style_button{Point{10, 30}, 100, 20, "Style menu",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).style_pressed();
        }
    }
{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    xy_out.put("no point");
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "red",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).red_pressed();
        }
    });
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "magenta",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).magenta_pressed();
        }
    });
     color_menu.attach(new Button{Point{0, 0}, 0, 0, "black",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).black_pressed();
        }
    });
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "yellow",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).yellow_pressed();
        }
    });
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "blue",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).blue_pressed();
        }
    });
   
    style_menu.attach(new Button{Point{0, 0}, 0, 0, "solid",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).solid_pressed();
        }
    });
    style_menu.attach(new Button{Point{0, 0}, 0, 0, "dot",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).dot_pressed();
        }
    });
    style_menu.attach(new Button{Point{0, 0}, 0, 0, "dash",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).dash_pressed();
        }
    });
    style_menu.attach(new Button{Point{0, 0}, 0, 0, "dashdot",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).dashdot_pressed();
        }
    });
        style_menu.attach(new Button{Point{0, 0}, 0, 0, "dashdotdot",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).dashdotdot_pressed();
        }
    });
    attach(color_menu);
    attach(style_menu);
    color_menu.hide();
    style_menu.hide();
    attach(color_button);
    attach(style_button);
    attach(lines);
}

void Lines_window::quit()
{
    hide();     // curious FLTK idiom to delete window
}

void Lines_window::next()
{
    int x = next_x.get_int();
    int y = next_y.get_int();

    lines.add(Point{x, y});

    ostringstream ss;
    ss << '(' << x << ',' << y << ')';
    xy_out.put(ss.str());

    redraw();
}

int main()
try {
    Lines_window win {Point{100, 100}, 600, 400, "lines"};
    return gui_main();
}
catch(exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "Unknown exception\n";
    return 2;
}
/*
g++ -w -Wall -std=c++11 GUI/Graph.cpp GUI/Window.cpp GUI/GUI.cpp GUI/Simple_window.cpp drill_16.cpp `fltk-config --ldflags --use-images` -o a.out
*/
