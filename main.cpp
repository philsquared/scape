#include "scape.h"

#include <iostream>

void test_colours() {

    using namespace scape;

    std::cout
        << "Normal colours:\n  "
        << scape::green << "Green text, "
        << blue << "blue text, "
        << red << "red text, "
        << colours::grey << "grey text, "
        << yellow << "yellow text,\n  "
        << magenta << "magenta text, "
        << cyan << "cyan text, "
        << reset_colour << "reset_colour"
        << std::endl;
    std::cout
        << "\nbright colours:\n  "
        << bright_red << "bright red text, "
        << bright_green << "bright green text, "
        << bright_blue << "bright blue text, "
        << bright_cyan << "bright cyan text,\n  "
        << bright_yellow << "bright yellow text, "
        << bright_magenta << "bright magenta text, "
        << white << "white text"
        << scape::endl;

    std::cout
        << "\nbackgrounds:\n  "
        << bright_red.on_black << " bright red on black, "
        << green.on_grey << " green on dark grey, "
        << black.on_green << " black on green," << scape::endl << "  "
        << bright_yellow.on_blue << " bright yellow on blue, "
        << white.on_red << " white on red, "
        << white.on_magenta << " white on magenta, "
        << blue.on_yellow << " blue on yellow "
        << scape::endl;

    std::cout
        << "\nstyles:\n  "
        << underline << "underlined"
        << no_underline << " not underlined"
        << scape::endl;
}

void test_cursors() {
    using namespace scape;
    std::cout << screen::clear;

    std::cout << move_to{ 10, 5 } << "hi there!";
    std::cout << move_to{ 0, 7 } << std::endl;

}

int main() {

//    std::cout << screen::save;

    test_colours();
    //test_cursors();

//    std::cout << screen::restore;
    return 0;
}
