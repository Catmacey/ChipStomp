// The dot factory typedefs

#ifndef __TheDotFactory_H
#define __TheDotFactory_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

////////////////////////////////////////////////////////////////////////////////
typedef struct _font_char_info{
   uint8_t Charwidth;
   uint16_t Offset;
}FONT_CHAR_INFO;
////////////////////////////////////////////////////////////////////////////////
typedef struct _font_info{
   uint8_t CharacterHeight;
   char StartCharacter;
   char EndCharacter;
   const char *FontName;
   const FONT_CHAR_INFO *Descriptors;
   const uint8_t *Bitmaps;
}FONT_INFO;
//////////////////////////////////////////////////////////////////////////////// 
#endif