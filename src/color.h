#ifndef __COLOR_H__
#define __COLOR_H__

/** The number of colors in play. Can be less than the total number of
    colors defined in this file. */
#ifndef NUM_COLORS
  #define NUM_COLORS 5
#endif

/** Enum defining the possible colors in the world */
enum color_t {
  BLACK      = 0,
  BLUE       = 1,
  GREEN      = 2,
  RED        = 3,
  WHITE      = 4,
  GOLD       = 5,
  PEARL      = 6,
  AQUAMARINE = 7,
  OCTARINE   = 8,
  CHESTNUT   = 9,
  MAX_COLORS = 10, // The maximal number of colors possible
};

/** Return a string describing the color `c` */
const char* color_to_string(enum color_t c);

/** Return a short string (using at most one character) describing the
    color `c`. For a more pleasant display, ANSI color codes
    (https://en.wikipedia.org/wiki/ANSI_escape_code) may be used. */
const char* color_to_short_string(enum color_t c);

#endif // __COLOR_H__
