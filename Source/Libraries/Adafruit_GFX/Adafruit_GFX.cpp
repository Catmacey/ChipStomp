/*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).

Adafruit invests time and resources providing this open source code, please
support Adafruit & open-source hardware by purchasing products from Adafruit!
 
Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

// Modified by Matt Casey to use proportional fonts.
// Fonts are in TheDotFactory format.
// https://github.com/pavius/The-Dot-Factory/tree/master/TheDotFactory


#include "Adafruit_GFX.h"
//#include "glcdfont.c"

#include "LiberationSans10.c"
//#include "LiberationMono11.c"
//#include "DejazVuSans12.c"

#ifdef __AVR__
 #include <avr/pgmspace.h>
#else
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif

Adafruit_GFX::Adafruit_GFX(int16_t w, int16_t h):
  WIDTH(w), HEIGHT(h)
{
  _width    = WIDTH;
  _height   = HEIGHT;
  rotation  = 0;
  cursor_y  = cursor_x    = 0;
  textsize  = 1;
  textcolor = textbgcolor = 0xFFFF;
  wrap      = true;
  currentFont = &liberationSans_10ptFontInfo;
}

// Draw a circle outline
void Adafruit_GFX::drawCircle(int16_t x0, int16_t y0, int16_t r,
    uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void Adafruit_GFX::drawCircleHelper( int16_t x0, int16_t y0,
               int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    } 
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}

void Adafruit_GFX::fillCircle(int16_t x0, int16_t y0, int16_t r,
			      uint16_t color) {
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects
void Adafruit_GFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
    uint8_t cornername, int16_t delta, uint16_t color) {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

// Bresenham's algorithm - thx wikpedia
void Adafruit_GFX::drawLine(int16_t x0, int16_t y0,
			    int16_t x1, int16_t y1,
			    uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

// Draw a rectangle
void Adafruit_GFX::drawRect(int16_t x, int16_t y,
			    int16_t w, int16_t h,
			    uint16_t color) {
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y+h-1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x+w-1, y, h, color);
}

void Adafruit_GFX::drawFastVLine(int16_t x, int16_t y,
				 int16_t h, uint16_t color) {
  // Update in subclasses if desired!
  drawLine(x, y, x, y+h-1, color);
}

void Adafruit_GFX::drawFastHLine(int16_t x, int16_t y,
				 int16_t w, uint16_t color) {
  // Update in subclasses if desired!
  drawLine(x, y, x+w-1, y, color);
}

void Adafruit_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
			    uint16_t color) {
  // Update in subclasses if desired!
  for (int16_t i=x; i<x+w; i++) {
    drawFastVLine(i, y, h, color);
  }
}

void Adafruit_GFX::fillScreen(uint16_t color) {
  fillRect(0, 0, _width, _height, color);
}

// Draw a rounded rectangle
void Adafruit_GFX::drawRoundRect(int16_t x, int16_t y, int16_t w,
  int16_t h, int16_t r, uint16_t color) {
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r, color); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
  drawFastVLine(x    , y+r  , h-2*r, color); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

// Fill a rounded rectangle
void Adafruit_GFX::fillRoundRect(int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r, uint16_t color) {
  // smarter version
  fillRect(x+r, y, w-2*r, h, color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

// Draw a triangle
void Adafruit_GFX::drawTriangle(int16_t x0, int16_t y0,
				int16_t x1, int16_t y1,
				int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void Adafruit_GFX::fillTriangle ( int16_t x0, int16_t y0,
				  int16_t x1, int16_t y1,
				  int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}

void Adafruit_GFX::drawBitmap(int16_t x, int16_t y,
			      const uint8_t *bitmap, int16_t w, int16_t h,
			      uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        drawPixel(x+i, y+j, color);
      }
    }
  }
}

#if ARDUINO >= 100
size_t Adafruit_GFX::write(uint8_t c) {
#else
void Adafruit_GFX::write(uint8_t c) {
#endif
  // Need a method to set the font
  uint8_t width;
  if (c == '\n') {
    //cursor_y += Font.CharacterHeight;
    cursor_y += currentFont->CharacterHeight;
    cursor_x  = 0;
  } else if (c == '\r') {
    // skip em
  } else if (c == '\t') {
    // Width of two spaces
    width = getFontWidth(' ') * 2;
    cursor_x += width;  
  } else {
    width = drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor);
    cursor_x += width;
    if (wrap && (cursor_x > (_width - width))) {
      cursor_y += currentFont->CharacterHeight;
      cursor_x = 0;
    }
  }
#if ARDUINO >= 100
  return 1;
#endif
}

// Draws a single character packed using The Dot Factory with bitlayout "columnMajor"
uint8_t Adafruit_GFX::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg) {
  const FONT_CHAR_INFO *CharInfo;
  const uint8_t *ColPtr;
  uint8_t CharIndex, row, col, MyCharWidth, MyCharHeight, yoffset, dots, strip, rows_in_byte, StripsPerColumn = 0;

  if ((c < currentFont->StartCharacter) || (c > currentFont->EndCharacter)){
    return 0;
  }

  CharIndex = c - currentFont->StartCharacter; //Character index
  CharInfo = currentFont->Descriptors; //Point to start of descriptors
  CharInfo += CharIndex; //Point to current char info

  ColPtr = currentFont->Bitmaps; //Point to start of bitmaps
  ColPtr += CharInfo->Offset; //Point to start of characters bitmap

  MyCharWidth = CharInfo->Charwidth; //Store Char width (variable)
  MyCharHeight = currentFont->CharacterHeight;
  StripsPerColumn = (MyCharHeight + 8 - 1) / 8; // Fast ceiling()
  /*
  Serial.print("drawChar:\"");
  Serial.print(c);
  Serial.print("\"");
  Serial.print(" ASCII:");
  Serial.print(c, DEC);
  Serial.print(" IDX:");
  Serial.print(CharIndex, DEC);
  Serial.print(" W:");
  Serial.print(MyCharWidth, DEC);
  Serial.print(" OFF:");
  Serial.println(CharInfo->Offset, DEC);
  */
  if(MyCharHeight < 8){
    rows_in_byte = MyCharHeight;
  }else{
    rows_in_byte = 8;
  }
  yoffset = 0;

  // bitmaps are store in rows of columns
  for(strip=0; strip<StripsPerColumn; strip++){
    rows_in_byte = MyCharHeight - yoffset;
    if(rows_in_byte > 8){
      rows_in_byte = 8;
    }
    for(col=0; col<MyCharWidth; col++){
      dots = *(ColPtr++);
      for(row=0; row<rows_in_byte; row++){
        if(dots & 0x01){
          drawPixel(x+col, y+yoffset+row, color);
          //Serial.print("#");
        }else if (bg != color) {
          drawPixel(x+col, y+yoffset+row, bg);
          //Serial.print(" ");
        }
        //Serial.print(" col:");
        //Serial.print(col, DEC);
        //Serial.print(", row:");
        //Serial.print(row, DEC);
        //Serial.println();
        // Shift the dots
        dots >>= 1;
      }
    }
    yoffset += 8;
  }

  return MyCharWidth + 2;
} 


void Adafruit_GFX::setCursor(int16_t x, int16_t y) {
  cursor_x = x;
  cursor_y = y;
}

void Adafruit_GFX::setTextSize(uint8_t s) {
  textsize = (s > 0) ? s : 1;
}

void Adafruit_GFX::setTextColor(uint16_t c) {
  // For 'transparent' background, we'll set the bg 
  // to the same as fg instead of using a flag
  textcolor = textbgcolor = c;
}

void Adafruit_GFX::setTextColor(uint16_t c, uint16_t b) {
  textcolor   = c;
  textbgcolor = b; 
}

uint8_t Adafruit_GFX::getFontHeight() {
  return currentFont->CharacterHeight;
}

uint8_t Adafruit_GFX::getFontWidth(unsigned char c) {
  // Gets width of given char  
  const FONT_CHAR_INFO *CharInfo;
  uint8_t CharIndex;

  if ((c < currentFont->StartCharacter) || (c > currentFont->EndCharacter)){
    return 0;
  }
  CharIndex = c - currentFont->StartCharacter; //Character index
  CharInfo = currentFont->Descriptors; //Point to start of descriptors
  CharInfo += CharIndex; //Point to current char info

  return CharInfo->Charwidth; //Return width of char
}

uint8_t Adafruit_GFX::getFontWidth() {
  // Gets nominal width of charset using an "M" as representative
  return getFontWidth('M');
}

void Adafruit_GFX::setTextWrap(boolean w) {
  wrap = w;
}

uint8_t Adafruit_GFX::getRotation(void) const {
  return rotation;
}

void Adafruit_GFX::setRotation(uint8_t x) {
  rotation = (x & 3);
  switch(rotation) {
   case 0:
   case 2:
    _width  = WIDTH;
    _height = HEIGHT;
    break;
   case 1:
   case 3:
    _width  = HEIGHT;
    _height = WIDTH;
    break;
  }
}

// Return the size of the display (per current rotation)
int16_t Adafruit_GFX::width(void) const {
  return _width;
}
 
int16_t Adafruit_GFX::height(void) const {
  return _height;
}

void Adafruit_GFX::invertDisplay(boolean i) {
  // Do nothing, must be subclassed if supported
}

