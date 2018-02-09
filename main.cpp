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
        << "\n"
        << flush; // flushes the underlying stream
}

void test_cursors() {
    using namespace scape;
    std::cout << screen::save;
    std::cout << save_cursor << hide_cursor;

    std::cout << screen::clear;

    std::cout << move_to{ 10, 5 } << "hi there!";

    std::cout
        << blue
        << up << left_by{10} << "***********"
        << down << left << "*"
        << down << left_by{11} << "***********"
        << left_by{12} << up_by{1} << right << "*";

    std::cout << down_by{ 4 } << right_by{3} << reset_colour;
    std::cout << "press enter to continue..." << std::endl;

    getchar();

    std::cout << show_cursor << restore_cursor;
    std::cout << screen::restore;
}

int main( int argc, char* argv[] ) {

    std::string cmd;
    if( argc == 2 )
        cmd = argv[1];

    if( cmd == "cursors" ) {
        test_cursors();
    }
    else if( cmd == "colours" ) {
        using namespace scape;
        auto size = screen::dimensions();
        std::cout << "terminal size: " << size.width << "x" << size.height;

        if( size.source == screen::size::queried )
            std::cout << " (queried)";
        else
            std::cout << " (guessed)";
        std::cout << "\n\n";

        test_colours();
    }
    else {
        std::cout << "\npass colours or cursors to run specific tests\n\n";
        return 1;
    }
}
