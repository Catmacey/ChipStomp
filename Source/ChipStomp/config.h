/*
	Main header file
*/

#ifndef __Config__
#define __Config__

#include <stdint.h> 

#define SAMPLERATE 44100    // Hz
#define SAMPLETIME 0.023 // Approx sample time in mS 
#define CLIPLEVEL 31000  // Full range is +32767 to -32767 but this is the level we light the LED at.
#define CLIPHARD 32767

// PIC port/pins
// PORT A
#define OLEDRES_BIT BIT_0  // RA0
#define CLIP_BIT    BIT_1  // RA1
// BIT_2 Osc
// BIT_3 Osc
#define DACHI_BIT   BIT_4  // RA4

// PORT B
// Outputs
#define OLEDCS_BIT  BIT_0
#define MOSI_BIT    BIT_1   // RB1
// BIT_2 Spare
#define OLEDDC_BIT  BIT_3   // RB3
#define DACLO_BIT   BIT_5   // RA5
#define SCLK_BIT    BIT_14

// Inputs
#define BTNSELECT_BIT BIT_4 // RB4
#define BTNEFFECT_BIT BIT_7 // RB7
#define ENCA_BIT BIT_8 // RB8
#define ENCB_BIT BIT_9 // RB9
#define ENCBTN_BIT BIT_15 // RB15

#define ENC_MASK ENCA_BIT | ENCB_BIT // Mask for encoder inputs
#define BTN_MASK BTNEFFECT_BIT | BTNSELECT_BIT | ENCBTN_BIT // Mask for buttons
#define INPUT_MASK ENC_MASK | BTN_MASK // Mask for all inputs

#define VUTICKLEN 16
#define VUTICKLEN_MASK 0x0f

// Some handy values for screen layout
#define DISP_FEAT_Y 20  // Start point for features area
#define DISP_FEAT_W 123 // MAx width of features area (allowing space for VU meter)
#define DISP_FEAT_INDENT 2  // Start point for features area

// Stupid Arduino pin numbers
#define OLED_RESET 9 // RA0 
#define DACL 0 // RB5 DAC Low byte
#define DACH 18 // RA4 DAC High byte
#define SPI_CLK 7 // RB14
#define OLED_CS 11 // RB0
#define OLED_DC 14 // RB3
#define SPI_MOSI 12 // RB1
#define _DSPI1_MOSI_PIN   12
// End of stupid Arduino pin numbers

#define SYS_FREQ 40000000 // PIC OSC frequency
#define GetSystemClock() SYS_FREQ
#define GetPeripheralClock()    (GetSystemClock() / (1 << OSCCONbits.PBDIV))

// This is used to store button state
// The Port the buttons are on is 16bit but the 
// in our case all the buttons are on the lower byte
typedef union {
  uint8_t complete;
  struct {
    unsigned :4;
    unsigned select:1;
    unsigned :1;
    unsigned :1;
    unsigned effect:1;
  };
} ButtonState_t;

// This is used to store the input
typedef struct {
  struct {
    int16_t value; // Accumulated value of encoder input. Set to 0 once actioned
    uint8_t state; // Current state, used in ISR decoding
  } encoder;
  ButtonState_t btn_state; // 1 = pressed
  ButtonState_t btn_diff; // 1 = different from last time
  uint32_t btn_timer; // Could use this to determine how long since last input...
} InputState_t;

// This is used to store the input and output VU Meter
typedef struct {
  int16_t input[VUTICKLEN];
  int16_t output[VUTICKLEN];
  uint8_t peak_in;
  uint8_t peak_out;
  uint8_t tick;
} VUMeter_t;


// Sinewave : 1024 value array of signed 16bit integers
const int16_t g_sinewave[] = {
  #include <sinetable.inc>
};

// Splash screen
const uint8_t g_splashscreen[] = {
  #include <splashscreen.inc>
};


// Returns the percentage value of value between the min and max range
extern float percentage(uint16_t value, uint16_t max, uint16_t min);

#endif