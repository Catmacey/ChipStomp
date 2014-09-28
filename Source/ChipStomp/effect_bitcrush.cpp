/*
	Bitcrush functions
	Can reduce the bit depth of the sample from 16bit down to 1bit
	Can reduce the sample rate by ratios down to 1/64th of the the main sample rate.

*/
#include <PLIB.h>
#include "effect_bitcrush.h"

//******** Private macros ********//

#define FEATURECOUNT 2  // Note : Default feature is 0 : It does nothing
#define BITS_MAX 16
#define BITS_MIN 1
#define RATIO_MIN 1
#define RATIO_MAX 64


//******** Private function declarations ********//

void bitcrush_nextFeature();
void bitcrush_adjustFeature(int16_t value);
uint8_t bitcrush_toggleOnOff();
int32_t bitcrush_effectISR(int32_t value);
void bitcrush_report();
uint16_t bitcrush_getHz();
void bitcrush_ratio_adjust(int16_t value);
void bitcrush_bits_adjust(int16_t value);

//******** Private variables ********//

// Internal state variables
typedef struct {
    uint8_t bits; // Number of bits for output
    uint8_t ratio; // Sample rate ratio
    uint8_t step; // position within ratio
    int32_t buffer; // Saved sample
    int32_t accumulator; // For averaging samples
} settings_t;
static settings_t settings = {
		16
	,	1
	, 0
	, 0
	, 0
};


enum features_t {SAFE, BITS, RATIO};
static const char *featurenames[] = {"Safe", "Bits", "Ratio"};

static int32_t buffer; // Input buffer

//******** Global variables ********//

// This struct is exposed globally via extern in the header
Effect_t effect_Bitcrush = {
		"Bitcrush"
	, 0
	, 0
	, bitcrush_nextFeature
	, bitcrush_adjustFeature
	, bitcrush_toggleOnOff
	, bitcrush_effectISR
	, bitcrush_report
};

//******** Function definitions ********//

// This is where the effect is actually processed
int32_t bitcrush_effectISR(int32_t value){
	uint8_t shift = 16 - settings.bits;
	int32_t result;
  // Sample rate reduction : Done by only updating output every nth sample
  if(settings.step == 0){
  	// Save current sample
  	settings.accumulator += value;
  	// Calc average of prev N samples
  	settings.buffer = settings.accumulator / settings.ratio;
  	result = settings.buffer;
  	settings.accumulator = 0;
  }else{
  	// Use previously saved sample
  	settings.accumulator += value;
  	result = settings.buffer;
  }
	if(++settings.step >= settings.ratio){
		settings.step = 0;
	}

  // Bit depth reduction
  if(shift){
  	//Shift right to drop resolution
  	result >>= shift;
  	// Shift back up to retain amplitude
  	result <<= shift;
  }

  return result;
}

// Cycles my features
void bitcrush_nextFeature(){
	if(FEATURECOUNT <= 1) return;
	if(effect_Bitcrush.featureIdx < FEATURECOUNT) {
		effect_Bitcrush.featureIdx++;
	}else{
		// Skip the safe feature
		effect_Bitcrush.featureIdx = 1;
	}
}

// Turns me on or off
uint8_t bitcrush_toggleOnOff(){
	if(effect_Bitcrush.state) effect_Bitcrush.state = 0;
	else effect_Bitcrush.state = 1;
	return effect_Bitcrush.state;
}

// Adjust the value of the current feature
// Receives the encoder delta
void bitcrush_adjustFeature(int16_t value){
	features_t feat = (features_t)effect_Bitcrush.featureIdx;
	switch(feat){
		case BITS:{
			bitcrush_bits_adjust((uint16_t)value);	
			break;
		}
		case RATIO:{
			bitcrush_ratio_adjust((uint16_t)value);	
			break;
		}
	}
}

// Alters the current sample rate ratio value by value (+ or -)
// Ratio determines output sample frequency
// use an int32 for result to make boundry checking easy
// Clamps result to within min/max
void bitcrush_ratio_adjust(int16_t value){
	int32_t result = settings.ratio - value;
	if(result > RATIO_MAX){
		result = RATIO_MAX;
	}else if(result < RATIO_MIN){
		result = RATIO_MIN;
	}
	settings.ratio = (uint8_t)result;
}

// Alters the current number of bits by value (+ or -)
// Clamps result to within min/max
void bitcrush_bits_adjust(int16_t value){
	int32_t result = settings.bits + value;
	if(result > BITS_MAX){
		result = BITS_MAX;
	}else if(result < BITS_MIN){
		result = BITS_MIN;
	}
	settings.bits = (uint8_t)result;
}

// Sends a string of my state to stdout
void bitcrush_report(){
	features_t feat = (features_t)effect_Bitcrush.featureIdx;

	// Write to screen
	if(feat == BITS){
		display.setTextColor(0);
		display.fillRect(0,DISP_FEAT_Y,DISP_FEAT_W,13,1);
	}else{
		display.setTextColor(1);
	}
	display.print("Bits ");
  display.print(settings.bits, DEC);
  
  if(feat == RATIO){
		display.setTextColor(0);
		display.fillRect(0,DISP_FEAT_Y+14,DISP_FEAT_W,13,1);
	}else{
		display.setTextColor(1);
	}
  display.setCursor(DISP_FEAT_INDENT,DISP_FEAT_Y+14);
  display.print("Ratio ");
  display.print(settings.ratio, DEC);
  display.print(":1 ");
  display.print(bitcrush_getHz(), DEC);
	display.print("Hz");
	
	display.setTextColor(1);
	display.setCursor(DISP_FEAT_INDENT,DISP_FEAT_Y+28);
	display.print("One extra line");
}

// Returns the frequency calculated from the step
uint16_t bitcrush_getHz(){
	return SAMPLERATE / settings.ratio;
}