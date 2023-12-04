
#include "color.h"
#include "color_second_header.h"

const char * str_color[] = {
  "Black" ,
  "Blue" ,
  "Green" ,
  "Red" ,
  "White" ,
  "Gold" ,
  "Pearl" ,
  "Aquamarine" ,
  "Octarine" ,
  "Chestnut" 
};

const char * str_short_color[] = {
  "K",
  "B",
  "G",
  "R",
  "W",
  "D",
  "P",
  "A",
  "O",
  "C" 
};

const char* prefix_color[MAX_COLORS] ={
  BLKB,
  BLU,
  GRN,
  RED,
  CRESET,
  CRESET,
  CRESET,
  CRESET,
  CRESET,
  CRESET
};

const char* color_to_string(enum color_t c)
{
  return  str_color[c];
  
}

const char* color_prefix(enum color_t c)
{
  return prefix_color[c];
}
const char* color_to_short_string(enum color_t c)
{
  return str_short_color[c];
}
  
  
