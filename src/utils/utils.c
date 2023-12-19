#include "utils.h"

size_t str_len_special(const char* string) 
{
    size_t size = 0;
    int in_color_code = 0;

    while (*string != '\0') 
	{
        if (*string == '\e')
		{ // Checks if the character is the beginning of an ANSI color sequence (escape sequence)
            in_color_code = 1;
        } else if (*string == 'm' && in_color_code) 
		{ 
			// Checks the end of the color sequence
            in_color_code = 0;
        } else if (!in_color_code) 
		{ 
			// Increments the size if not in a color sequence
            ++size;
        }

        ++string;
    }

    return size;
}