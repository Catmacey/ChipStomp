/*********************************************************************
This is a library for monochrome OLED 128x64 with SH1106 driver.
The OLED has it's own built in DC/DC convertor which we use to provide the OLED drive voltage.

Only 4 SPI + Reset is supported.
	MOSI : Data
	CLK : Clock
	CS : Chip Select
	D/C : Data/Command
	RST : Reset

Built to run on Chipkit and use the DSPI library.

Adapted from the Adafruit SSD1306 driver.
The SSD1306 and SH1106 are very similar but have a few important differences.
Written to be compatible with the Adafruit_GFX library.
*********************************************************************/

#include "Adafruit_GFX.h"
#include "Catmacey_SH1106.h"

// the memory buffer for the LCD
static uint8_t buffer[SH1106_LCDHEIGHT * SH1106_LCDWIDTH / 8] = {};

// the most basic function, set a single pixel
void Catmacey_SH1106::drawPixel(int16_t x, int16_t y, uint16_t color) {
	if ((x < 0) || (x >= width()) || (y < 0) || (y >= height()))
		return;

	// check rotation, move pixel around if necessary
	switch (getRotation()) {
	case 1:
		swap(x, y);
		x = WIDTH - x - 1;
		break;
	case 2:
		x = WIDTH - x - 1;
		y = HEIGHT - y - 1;
		break;
	case 3:
		swap(x, y);
		y = HEIGHT - y - 1;
		break;
	}  

	// x is which column
	if (color == WHITE) 
		buffer[x+ (y/8)*SH1106_LCDWIDTH] |= (1 << (y&7));  
	else
		buffer[x+ (y/8)*SH1106_LCDWIDTH] &= ~(1 << (y&7)); 
}

// constructor for hardware SPI - we indicate DataCommand, ChipSelect, Reset 
Catmacey_SH1106::Catmacey_SH1106(
			int8_t DC
		, int8_t RST
		, int8_t CS
		, DSPI * SPI
		, const FONT_INFO * font_table[]
	) : Adafruit_GFX(
			SH1106_LCDWIDTH
		, SH1106_LCDHEIGHT
		, font_table
) {
	
	dc = DC;
	rst = RST;
	cs = CS;
	spi = SPI;  // This is the SPI Object provided by the DSPI Library
}

void Catmacey_SH1106::begin() {
	uint8_t idx = 0;

	// set pin directions
	pinMode(dc, OUTPUT);
	pinMode(cs, OUTPUT);
	csport      = portOutputRegister(digitalPinToPort(cs));
	cspinmask   = digitalPinToBitMask(cs);
	dcport      = portOutputRegister(digitalPinToPort(dc));
	dcpinmask   = digitalPinToBitMask(dc);

	// Setup reset pin direction (used by both SPI and I2C)  
	pinMode(rst, OUTPUT);
	digitalWrite(rst, HIGH);
	// VDD (3.3V) goes high at start, lets just chill for a ms
	delay(1);
	// bring reset low
	digitalWrite(rst, LOW);
	// wait 
	delay(1);
	// bring out of reset
	digitalWrite(rst, HIGH);
	// wait a spot
	delay(1);

	// Init sequence : Based on the exmaple provided in the datasheet
	sh1106_command(SH1106_DISPLAYOFF);

	sh1106_command(SH1106_SEGREMAPLR); // Set segment remap left to right
	//sh1106_command(0xA0); // Set segment remap right to left
	sh1106_command(SH1106_SETCOMPINS); // Common pads config
	sh1106_command(0x12);  // Default
	sh1106_command(SH1106_COMSCANDEC); // Scan direction vertical flip
	sh1106_command(SH1106_SETMULTIPLEX); // Set multiplex mode
	sh1106_command(0x3F); // Default
	sh1106_command(SH1106_SETDISPLAYCLOCKDIV); // Clock divider
	//sh1106_command(0x50); // Default
	sh1106_command(0xF0); // Fast
	//sh1106_command(0x0F); // Slow
	//sh1106_command(0x00); // Middle
	sh1106_command(SH1106_SETVCOMDETECT); // Set vcom
	sh1106_command(0x40);  // Default
	sh1106_command(SH1106_SETCONTRAST); // Set contrast mode
	sh1106_command(0x90); // Mid range contrast
	sh1106_command(0x33);  // Charge pump voltage 9.0v
	sh1106_command(SH1106_SETINTERNALDCDC);
	sh1106_command(SH1106_INTERNALDCDCON);
	delay(100); // Recommended delay for DCDC stabilization
	sh1106_command(SH1106_DISPLAYON);//--turn on oled panel
	delay(150);

	sh1106_command(SH1106_SETSTARTLINE); // Start line
	sh1106_command(SH1106_PAGEADDR); // Set page address
	sh1106_command(SH1106_SETLOWCOLUMN); // set lower column address
	sh1106_command(SH1106_SETHIGHCOLUMN); // set higher column address
	sh1106_command(SH1106_NORMALDISPLAY); // Normal display
	sh1106_command(SH1106_SETDISPLAYOFFSET); // Display offset
	sh1106_command(0x00); // no offset

	//sh1106_command(SH1106_SETPRECHARGE); // Set precharge mode
	//sh1106_command(0x22);  // Default
	
}


void Catmacey_SH1106::invertDisplay(uint8_t i) {
	if (i) {
		sh1106_command(SH1106_INVERTDISPLAY);
	} else {
		sh1106_command(SH1106_NORMALDISPLAY);
	}
}

void Catmacey_SH1106::setContrast(uint8_t contrast) {
	sh1106_command(SH1106_SETCONTRAST);
	sh1106_command(contrast);
}

void Catmacey_SH1106::sh1106_command(uint8_t c) { 
	// SPI
	*csport |= cspinmask;
	*dcport &= ~dcpinmask;
	*csport &= ~cspinmask;
	(void)spi->transfer(c);
	*csport |= cspinmask;
}

void Catmacey_SH1106::sh1106_data(uint8_t c) {
	// SPI
	*csport |= cspinmask;
	*dcport |= dcpinmask;
	*csport &= ~cspinmask;
	(void)spi->transfer(c);
	*csport |= cspinmask;
}

void Catmacey_SH1106::display(void) {
	sh1106_command(SH1106_SETSTARTLINE); // Set start line
	// SPI
	uint16_t idx = 0;
	uint8_t col = 0;
	uint8_t page = 0;
	for(page=SH1106_PAGEADDR; page < (SH1106_PAGEADDR+SH1106_PAGES); page++){
		// Autoincrement of column does not move onto next page
		// so each horizontal stripe (page) has to be zeroed before writing
		sh1106_command(page); // Set page addr
		sh1106_command(SH1106_SETLOWCOLUMN); // Lower col addr 0
		sh1106_command(SH1106_SETHIGHCOLUMN); // Upper col addr 0    
		*csport |= cspinmask;
		*dcport |= dcpinmask;
		*csport &= ~cspinmask;
		for (col=0; col<(SH1106_LCDWIDTH); col++) {
			(void)spi->transfer(buffer[idx++]);
		}
		*csport |= cspinmask;
	}
}

// clear everything
void Catmacey_SH1106::clearDisplay(void) {
	memset(buffer, 0, (SH1106_LCDWIDTH*SH1106_LCDHEIGHT/8));
}

// This is exactly the same as in Adafruit_SSD1306
void Catmacey_SH1106::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	boolean bSwap = false;
	switch(rotation) { 
		case 0:
			// 0 degree rotation, do nothing
			break;
		case 1:
			// 90 degree rotation, swap x & y for rotation, then invert x
			bSwap = true;
			swap(x, y);
			x = WIDTH - x - 1;
			break;
		case 2:
			// 180 degree rotation, invert x and y - then shift y around for height.
			x = WIDTH - x - 1;
			y = HEIGHT - y - 1;
			x -= (w-1);
			break;
		case 3:
			// 270 degree rotation, swap x & y for rotation, then invert y  and adjust y for w (not to become h)
			bSwap = true;
			swap(x, y);
			y = HEIGHT - y - 1;
			y -= (w-1);
			break;
	}

	if(bSwap) { 
		drawFastVLineInternal(x, y, w, color);
	} else { 
		drawFastHLineInternal(x, y, w, color);
	}
}

// Mostly the same as in Adafruit_SSD1306
// Modified to generate halftone output for colors
// 2 ,3 ,4
void Catmacey_SH1106::drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color) {
	// Do bounds/limit checks
	if(y < 0 || y >= HEIGHT) { return; }

	// make sure we don't try to draw below 0
	if(x < 0) { 
		w += x;
		x = 0;
	}

	// make sure we don't go off the edge of the display
	if( (x + w) > WIDTH) { 
		w = (HEIGHT- x);
	}

	// if our width is now negative, punt
	if(w <= 0) { return; }

	// set up the pointer for  movement through the buffer
	register uint8_t *pBuf = buffer;
	// adjust the buffer pointer for the current row
	pBuf += ((y/8) * SH1106_LCDWIDTH);
	// and offset x columns in
	pBuf += x;

	register uint8_t mask_white = 1 << (y&7);
	register uint8_t mask_black = ~mask_white;

	switch(color){
		case WHITE:{
			while(w--) { *pBuf++ |= mask_white; }
			break;
		}
		case GREY:{
			// Every other dot is white. 
			// Alternates every row
			// X X X X X
			//  X X X X
			// X X X X X
			//  X X X X
			int16_t dot = x+y;
			while(w--) { 
				if(dot & 0b1){
					*pBuf++ |= mask_white; 
				}else{
					*pBuf++ &= mask_black;
				}
				dot++;
			}
			break;
		}
    case SPARE:{
    	// Every third dot is white. 
    	// Alternate lines are black
    	// X X X X X
			//
			// X X X X X 
			//
			// X X X X X
      if(y & 0b1){
      	int16_t dot = x+y;
	      while(w--) { 
	        if(dot & 0b1){
	          *pBuf++ |= mask_white; 
	        }else{
	          *pBuf++ &= mask_black;
	        }
	        dot++;
	      }
      }else{
      	// Black
      	while(w--) { *pBuf++ &= mask_black; }
      }
      break;
    }	
		case GHOST:{
    	// Every 5th dot is white. 
    	// Alternate lines are black
    	// X   X   X   X   X
			//
			//   X   X   X   X   
			//
			// X   X   X   X   X
     	int16_t dot = x;
      switch(y & 0b11){
      	case 0:{
      		// X   X   X   X   X	
					dot += 2;      		
      	}
      	case 2:{
      		//   X   X   X   X   	
		      while(w--) { 
		        if(!(dot % 5)){
		          *pBuf++ |= mask_white; 
		        }else{
		          *pBuf++ &= mask_black;
		        }
		        dot++;
		      }
      		break;
      	}
      	default:{
					// Black
      		while(w--) { *pBuf++ &= mask_black; }
      	}
      }
      break;
    }	    
		default :{
			// Black      
			while(w--) { *pBuf++ &= mask_black; }
			break;
		}
	}

	// Not implemented
	    	// Every forth dot is white. 
    	// Shifts 1 every line
    	// X  X  X  X  X
			//   X  X  X  X  
			//  X  X  X  X  
			// X  X  X  X

}

// This is exactly the same as in Adafruit_SSD1306
void Catmacey_SH1106::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	bool bSwap = false;
	switch(rotation) { 
		case 0:
			break;
		case 1:
			// 90 degree rotation, swap x & y for rotation, then invert x and adjust x for h (now to become w)
			bSwap = true;
			swap(x, y);
			x = WIDTH - x - 1;
			x -= (h-1);
			break;
		case 2:
			// 180 degree rotation, invert x and y - then shift y around for height.
			x = WIDTH - x - 1;
			y = HEIGHT - y - 1;
			y -= (h-1);
			break;
		case 3:
			// 270 degree rotation, swap x & y for rotation, then invert y 
			bSwap = true;
			swap(x, y);
			y = HEIGHT - y - 1;
			break;
	}

	if(bSwap) { 
		drawFastHLineInternal(x, y, h, color);
	} else {
		drawFastVLineInternal(x, y, h, color);
	}
}

// This is exactly the same as in Adafruit_SSD1306
void Catmacey_SH1106::drawFastVLineInternal(int16_t x, int16_t __y, int16_t __h, uint16_t color) {

	// do nothing if we're off the left or right side of the screen
	if(x < 0 || x >= WIDTH) { return; }

	// make sure we don't try to draw below 0
	if(__y < 0) { 
		// __y is negative, this will subtract enough from __h to account for __y being 0
		__h += __y;
		__y = 0;

	} 

	// make sure we don't go past the height of the display
	if( (__y + __h) > HEIGHT) { 
		__h = (HEIGHT - __y);
	}

	// if our height is now negative, punt 
	if(__h <= 0) { 
		return;
	}

	// this display doesn't need ints for coordinates, use local byte registers for faster juggling
	register uint8_t y = __y;
	register uint8_t h = __h;


	// set up the pointer for fast movement through the buffer
	register uint8_t *pBuf = buffer;
	// adjust the buffer pointer for the current row
	pBuf += ((y/8) * SH1106_LCDWIDTH);
	// and offset x columns in
	pBuf += x;

	// do the first partial byte, if necessary - this requires some masking
	register uint8_t mod = (y&7);
	if(mod) {
		// mask off the high n bits we want to set 
		mod = 8-mod;

		// note - lookup table results in a nearly 10% performance improvement in fill* functions
		// register uint8_t mask = ~(0xFF >> (mod));
		static uint8_t premask[8] = {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
		register uint8_t mask = premask[mod];

		// adjust the mask if we're not going to reach the end of this byte
		if( h < mod) { 
			mask &= (0XFF >> (mod-h));
		}

		if(color == WHITE) { 
			*pBuf |= mask;
		} else {
			*pBuf &= ~mask;
		}

		// fast exit if we're done here!
		if(h<mod) { return; }

		h -= mod;

		pBuf += SH1106_LCDWIDTH;
	}


	// write solid bytes while we can - effectively doing 8 rows at a time
	if(h >= 8) { 
		// store a local value to work with 
		register uint8_t val = (color == WHITE) ? 255 : 0;

		do  {
			// write our value in
			*pBuf = val;

			// adjust the buffer forward 8 rows worth of data
			pBuf += SH1106_LCDWIDTH;

			// adjust h & y (there's got to be a faster way for me to do this, but this should still help a fair bit for now)
			h -= 8;
		} while(h >= 8);
	}

	// now do the final partial byte, if necessary
	if(h) {
		mod = h & 7;
		// this time we want to mask the low bits of the byte, vs the high bits we did above
		// register uint8_t mask = (1 << mod) - 1;
		// note - lookup table results in a nearly 10% performance improvement in fill* functions
		static uint8_t postmask[8] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
		register uint8_t mask = postmask[mod];
		if(color == WHITE) { 
			*pBuf |= mask;
		} else { 
			*pBuf &= ~mask;
		}
	}
}
