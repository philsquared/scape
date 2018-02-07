#ifndef SCAPE_H_INCLUDED
#define SCAPE_H_INCLUDED

#include <iosfwd>

// This is going to be stitched into a single header library, along the lines of Catch2
namespace scape {

    namespace detail {

        enum class foreground_colours {
            black, red, green, yellow, blue, magenta, cyan, grey,
            bright_red, bright_green, bright_yellow, bright_blue, bright_magenta, bright_cyan, white,
            reset
        };
        enum class background_colours {
            on_black, on_red, on_green, on_yellow, on_blue, on_magenta, on_cyan, on_grey
        };

        class bg_manip {
            foreground_colours foreground;
            background_colours background;
        public:
            bg_manip( foreground_colours fg, background_colours bg ) : foreground( fg ), background( bg ) {}
            friend auto operator << ( std::ostream& os, bg_manip const& col ) -> std::ostream&;
        };

        class fg_manip {
            foreground_colours foreground;
        public:
            fg_manip( foreground_colours fg );
            bg_manip on_black, on_red, on_green, on_yellow, on_blue, on_magenta, on_cyan, on_grey;
            friend auto operator << ( std::ostream& os, fg_manip const& col ) -> std::ostream&;
        };

    } // namespace detail

    namespace colours {
        // "Normal" colours
        extern detail::fg_manip black, red, green, yellow, blue, magenta, cyan, grey;

        // "Bright" colours
        extern detail::fg_manip bright_red, bright_green, bright_yellow, bright_blue, bright_magenta, bright_cyan, white;

        // Special codes
        extern detail::fg_manip reset_colour;
    }
    namespace colors {
        using namespace colours; // you decide on the spelling
    }

    // !TBD move this into a separate header?
    namespace cursor {
        struct move_to { int x, y; };
        struct up_by { int amount; };
        struct down_by { int amount; };
        struct left_by { int amount; };
        struct right_by { int amount; };

        auto operator << ( std::ostream& os, move_to const& coords ) -> std::ostream&;
        auto operator << ( std::ostream& os, up_by const& by ) -> std::ostream&;
        auto operator << ( std::ostream& os, down_by const& by ) -> std::ostream&;
        auto operator << ( std::ostream& os, left_by const& by ) -> std::ostream&;
        auto operator << ( std::ostream& os, right_by const& by ) -> std::ostream&;

        auto up( std::ostream& os ) -> std::ostream&;
        auto down( std::ostream& os ) -> std::ostream&;
        auto left( std::ostream& os ) -> std::ostream&;
        auto right( std::ostream& os ) -> std::ostream&;

        auto hide_cursor( std::ostream& os ) -> std::ostream&;
        auto show_cursor( std::ostream& os ) -> std::ostream&;

        auto save_cursor( std::ostream& os ) -> std::ostream&;
        auto restore_cursor( std::ostream& os ) -> std::ostream&;
    }

    // !TBD move this into a separate header?
    namespace screen {
        auto clear ( std::ostream& os ) -> std::ostream&;
        auto home ( std::ostream& os ) -> std::ostream&;

        auto save ( std::ostream& os ) -> std::ostream&;
        auto restore ( std::ostream& os ) -> std::ostream&;

        struct size{
            enum source{ guessed, queried };
            source source;
            int width, height;
        };
        auto dimensions() -> size;
    }

    auto underline( std::ostream& os ) -> std::ostream&;
    auto no_underline( std::ostream& os ) -> std::ostream&;

    auto flush( std::ostream& os ) -> std::ostream&;

    // Reset all text attributes
    auto reset( std::ostream& os ) -> std::ostream&;

    // Sends std::endl but also resets all text attributes
    auto endl( std::ostream& os ) -> std::ostream&;

    using namespace cursor;
    using namespace colours;
}

#endif //SCAPE_H_INCLUDED
