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

#ifndef Catmacey_SH1106_h
#define Catmacey_SH1106_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#if !defined(__PIC32MX__)
		#error "Only built for pic32"
#endif

typedef volatile uint32_t PortReg;
typedef volatile uint32_t PortMask;

#include <DSPI.h>
#include <Adafruit_GFX.h>

#define BLACK 0
#define WHITE 1
#define GREY 2
#define SPARE 3
#define GHOST 4

/*=========================================================================
		SH1106 Displays
		-----------------------------------------------------------------------
		The driver only supports 128x64 displays
		-----------------------------------------------------------------------*/
/*=========================================================================*/

#define SH1106_LCDWIDTH   128
#define SH1106_LCDHEIGHT  64
#define SH1106_PAGES      8

#define SH1106_SETCONTRAST 0x81
#define SH1106_DISPLAYALLON_RESUME 0xA4
#define SH1106_DISPLAYALLON 0xA5
#define SH1106_NORMALDISPLAY 0xA6
#define SH1106_INVERTDISPLAY 0xA7
#define SH1106_DISPLAYOFF 0xAE
#define SH1106_DISPLAYON 0xAF

#define SH1106_SETDISPLAYOFFSET 0xD3
#define SH1106_SETCOMPINS 0xDA

#define SH1106_SETVCOMDETECT 0xDB

#define SH1106_SETDISPLAYCLOCKDIV 0xD5
#define SH1106_SETPRECHARGE 0xD9

#define SH1106_SETMULTIPLEX 0xA8

#define SH1106_SETLOWCOLUMN 0x02
#define SH1106_SETHIGHCOLUMN 0x10

#define SH1106_SETSTARTLINE 0x40

#define SH1106_COLUMNADDR 0x21
#define SH1106_PAGEADDR   0xB0

#define SH1106_COMSCANINC 0xC0
#define SH1106_COMSCANDEC 0xC8

#define SH1106_SEGREMAPRL 0xA0
#define SH1106_SEGREMAPLR 0xA1

#define SH1106_SETINTERNALDCDC 0xAD
#define SH1106_INTERNALDCDCOFF 0x8A
#define SH1106_INTERNALDCDCON 0x8B

class Catmacey_SH1106 : public Adafruit_GFX {
 DSPI *spi;
 public:
	// DSPI Library handles the setup and definition of MOSI and MISO pins
	Catmacey_SH1106(
			int8_t DC
		, int8_t RST
		, int8_t CS
		, DSPI *SPI
		, const FONT_INFO * font_table[]
		// , const FONT_INFO * const font_table[]
	);

	void begin();
	void sh1106_command(uint8_t c);
	void sh1106_data(uint8_t c);

	void clearDisplay(void);
	void invertDisplay(uint8_t i);
	void display();

	void setContrast(uint8_t contrast);

	void drawPixel(int16_t x, int16_t y, uint16_t color);

	virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

 private:
	int8_t dc, rst, cs;

	PortReg *csport, *dcport;
	PortMask cspinmask, dcpinmask;

	inline void drawFastVLineInternal(int16_t x, int16_t y, int16_t h, uint16_t color) __attribute__((always_inline));
	inline void drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color) __attribute__((always_inline));

};

#endif