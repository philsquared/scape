#include "scape.h"

#include <ostream>

// !TBD ANSI terminals only, for now
namespace scape {

    namespace detail {

        namespace {
            const std::string esc_prefix = "\e[";

            inline auto fg_colour( foreground_colours col ) -> char const* {
                switch( col ) {
                    case foreground_colours::black: return "0;30";
                    case foreground_colours::red: return "0;31";
                    case foreground_colours::green: return "0;32";
                    case foreground_colours::yellow: return "0;33";
                    case foreground_colours::blue: return "0;34";
                    case foreground_colours::magenta: return "0;35";
                    case foreground_colours::cyan: return "0;36";
                    case foreground_colours::grey: return "0;37";

                    case foreground_colours::bright_red: return "1;31";
                    case foreground_colours::bright_green: return "1;32";
                    case foreground_colours::bright_yellow: return "1;33";
                    case foreground_colours::bright_blue: return "1;34";
                    case foreground_colours::bright_magenta: return "1;35";
                    case foreground_colours::bright_cyan: return "1;36";
                    case foreground_colours::white: return "1;37";

                    case foreground_colours::reset: return "0;39";

                    default: return nullptr;
                }
            }
            inline auto bg_colour( background_colours col ) -> char const* {
                switch( col ) {
                    case background_colours::on_black: return "40";
                    case background_colours::on_red: return "41";
                    case background_colours::on_green: return "42";
                    case background_colours::on_yellow: return "43";
                    case background_colours::on_blue: return "44";
                    case background_colours::on_magenta: return "45";
                    case background_colours::on_cyan: return "46";
                    case background_colours::on_grey: return "47";

                    default: return nullptr;
                }
            }
        } // anon namespace

        auto operator << ( std::ostream& os, bg_manip const& col ) -> std::ostream& {
            auto fg = fg_colour( col.foreground );
            auto bg = bg_colour( col.background );
            if( fg && bg )
                return os << esc_prefix << fg << ";" << bg << "m";
            else if( fg )
                return os << esc_prefix << fg << "m";
            else if( bg )
                return os << esc_prefix << "0;" << bg << "m";
            return os;
        }

        auto operator << ( std::ostream& os, fg_manip const& col ) -> std::ostream& {
            if( auto fg = fg_colour( col.foreground ) )
                return os << esc_prefix << fg << "m";
            return os;
        }

        fg_manip::fg_manip( foreground_colours fg )
        :   foreground( fg ),
            on_black( fg, background_colours::on_black ),
            on_red( fg, background_colours::on_red ),
            on_green( fg, background_colours::on_green ),
            on_yellow( fg, background_colours::on_yellow ),
            on_blue( fg, background_colours::on_blue ),
            on_magenta( fg, background_colours::on_magenta ),
            on_cyan( fg, background_colours::on_cyan ),
            on_grey( fg, background_colours::on_grey )
        {}
    }

    namespace cursor {

        auto operator << ( std::ostream& os, move_to const& coords ) -> std::ostream& {
            return os << detail::esc_prefix << coords.y << ";" << coords.x << "H";
        }
        auto operator << ( std::ostream& os, up_by const& by ) -> std::ostream& {
            return os << detail::esc_prefix << by.amount << "A";
        }
        auto operator << ( std::ostream& os, down_by const& by ) -> std::ostream& {
            return os << detail::esc_prefix << by.amount << "B";
        }
        auto operator << ( std::ostream& os, left_by const& by ) -> std::ostream& {
            return os << detail::esc_prefix << by.amount << "D";
        }
        auto operator << ( std::ostream& os, right_by const& by ) -> std::ostream& {
            return os << detail::esc_prefix << by.amount << "C";
        }

        auto up( std::ostream& os ) -> std::ostream& { return os << detail::esc_prefix << "1A"; }
        auto down( std::ostream& os ) -> std::ostream& { return os << detail::esc_prefix << "1B"; }
        auto left( std::ostream& os ) -> std::ostream& { return os << detail::esc_prefix << "1D"; }
        auto right( std::ostream& os ) -> std::ostream& { return os << detail::esc_prefix << "1C"; }
    }

    namespace colours {
        detail::fg_manip black( detail::foreground_colours::black );
        detail::fg_manip red( detail::foreground_colours::red );
        detail::fg_manip green( detail::foreground_colours::green );
        detail::fg_manip yellow( detail::foreground_colours::yellow );
        detail::fg_manip blue( detail::foreground_colours::blue );
        detail::fg_manip magenta( detail::foreground_colours::magenta );
        detail::fg_manip cyan( detail::foreground_colours::cyan );
        detail::fg_manip grey( detail::foreground_colours::grey );
        detail::fg_manip bright_red( detail::foreground_colours::bright_red );
        detail::fg_manip bright_green( detail::foreground_colours::bright_green );
        detail::fg_manip bright_yellow( detail::foreground_colours::bright_yellow );
        detail::fg_manip bright_blue( detail::foreground_colours::bright_blue );
        detail::fg_manip bright_magenta( detail::foreground_colours::bright_magenta );
        detail::fg_manip bright_cyan( detail::foreground_colours::bright_cyan );
        detail::fg_manip white( detail::foreground_colours::white );

        detail::fg_manip reset_colour( detail::foreground_colours::reset );
    }

    namespace screen {
        auto home ( std::ostream& os ) -> std::ostream& {
            return os << detail::esc_prefix << "H";
        }
        auto clear ( std::ostream& os ) -> std::ostream& {
            return os << detail::esc_prefix << "2J" << home;
        }

        // ** save/ restore don't seem to work
//        auto save ( std::ostream& os ) -> std::ostream& {
//            return os << detail::esc_prefix << "s"; // !TBD "47h" (save screen) doesn't seem to work? - neither does s for restore cursor
//        }
//        auto restor ( std::ostream& os ) -> std::ostream& {
//            return os << detail::esc_prefix << "u"; // 47l
//        }
    }

    auto underline( std::ostream& os ) -> std::ostream&{ return os << detail::esc_prefix << ";4m"; }
    auto no_underline( std::ostream& os ) -> std::ostream&{ return os << detail::esc_prefix << ";24m"; }
    auto reset( std::ostream& os ) -> std::ostream& { return os << detail::esc_prefix << ";0m"; }
    auto endl ( std::ostream& os ) -> std::ostream& { return os << reset << std::endl; }


} // namespace scape
