/*
	Flanger functions
	It's sort of like a wobbly tape drive.
	This effect maintains an input buffer loop of max BUFFSIZE samples
	It records the input to loop at a fixed rate.
	It plays back from this loop using a read head that oscilates at a speed you can control.
	The oscillation uses the sinewave lookup.
*/
#include <PLIB.h>
#include "effect_flanger.h"
	
/*
TODO : Rename AMP to depth or delay.  It is not amplitude!
TODO : Add mix attribute to control the mix of the original and the modified signal.
TODO : Do I really need to a) use a 16bit sine? b) interpolate between two sine posision?
TODO : Is the interpolation between the two samples really worth it? The pitch shift worked fine with just single int values.
TODO : Add control over the length of the buffer (within max of BUFFSIZE)
*/

//******** Private macros ********//

#define FEATURECOUNT 2  // Note : Default feature is 0 : It does nothing
#define WAVE_LEN 0x03ff  // Number of samples
#define AMP_MAX 0xffff
#define AMP_MIN 0x0000
#define STEP_MAX 0x03ff
#define STEP_MIN 0x0001
#define POSITION_MAX 0x0003ffff  
#define BASEFREQ SAMPLERATE / WAVE_LEN  // 43hz for 1024 samples @ 44.1khz
#define BUFFSIZE 2000


//******** Private function declarations ********//

void flng_nextFeature();
void flng_adjustFeature(int16_t value);
uint8_t flng_toggleOnOff();
int32_t flng_effectISR(int32_t value);
void flng_report();
float flng_getHz();
void flng_freq_adjust(int16_t value);
void flng_amp_adjust(int16_t value);

//******** Private variables ********//

// Internal state variables
typedef struct {
    uint32_t location; // Sinewave lookup index (24b.8b)
    uint16_t position; // Buffer read/write index
    uint16_t amplitude;
    uint16_t step;
} settings_t;
static settings_t settings = {
		0
	, 0
	,	AMP_MAX / 2
	, 55
};

enum features_t {SAFE, AMP, FREQ};
static const char *featurenames[] = {"Safe", "Amplitude","Rate"};

static int16_t flng_buffer[BUFFSIZE];

//******** Global variables ********//

// This struct is exposed globally via extern in the header
Effect_t effect_Flanger = {
		"Flanger"
	, 0
	, 0
	, flng_nextFeature
	, flng_adjustFeature
	, flng_toggleOnOff
	, flng_effectISR
	, flng_report
};

//******** Function definitions ********//
// This is where the effect is actually processed
// Note this function could be made much more memory efficiant
// by reusing variables, at the cost of being much hard to read
int32_t flng_effectISR(int32_t value){
	uint16_t idx;
	int16_t sine1, sine2, offset, sample1, sample2;
	int32_t result;
	uint8_t frac;

  settings.location += settings.step;
  // if we've gone over the table boundary -> loop back
  settings.location &= POSITION_MAX;
  // Get the index part
  idx = (settings.location >> 8);
  // Retrieve first sine sample sample
  sine1 = g_sinewave[idx];
  // go to next sample
  idx++;
  // check if we've gone over the boundary.
  idx &= STEP_MAX; 
  // get second sample and put it in sine2 
  sine2 = g_sinewave[idx];
  // Interpolate between samples
  // multiply each sample by the fractional distance to the actual settings.location  value
  frac = (uint8_t)(settings.location & 0x000000ff); // fetch the lower 8b
  // scale sample 2
  sine2 = (sine2 * frac) >> 8;
  // scale sample 1
  sine1 = (sine1 * (0xff - frac )) >> 8;
  // Add samples together to get an average, resultant sinewave is now in sine2 
  sine2 += sine1;
  // Flanger offset
  offset = (sine2 * settings.amplitude) >> 16;

	// store incoming data
  flng_buffer[settings.position++] = (int16_t)value;
  // check if position has gotten bigger than buffer size
  if (settings.position >= BUFFSIZE) {
    settings.position = 0; // reset position
  }

  // Now do the Flanger effect
	// fetch delayed data with sinusoidal offset
  idx = settings.position + (BUFFSIZE/2) + (offset >> 8);
  if (idx >= BUFFSIZE) { // check for buffer overflow
    idx -= BUFFSIZE;
  }
  // fetch delayed data
  sample1 = flng_buffer[idx];
  // fetch next delayed data for interpolation
  if (++idx == BUFFSIZE) { // check for buffer overflow
    idx = 0;
  }
  sample2 = flng_buffer[idx];
  // interpolate between values
  sample2 = (sample2 * (offset & 0xff)) >> 8;
  sample1 = (sample1 * (0xff - (offset & 0xff))) >> 8;
 
  result = (sample1 + sample2);

  // TODO : Add the mix here!
  return result;
}

// Cycles my features
void flng_nextFeature(){
	if(FEATURECOUNT <= 1) return;
	if(effect_Flanger.featureIdx < FEATURECOUNT) {
		effect_Flanger.featureIdx++;
	}else{
		// Skip the safe feature
		effect_Flanger.featureIdx = 1;
	}
}

// Turns me on or off
uint8_t flng_toggleOnOff(){
	if(effect_Flanger.state) effect_Flanger.state = 0;
	else effect_Flanger.state = 1;
	return effect_Flanger.state;
}

// Adjust the value of the current feature
// Receives the encoder delta
void flng_adjustFeature(int16_t value){
	// Currently hard coded to alter the step
	features_t feat = (features_t)effect_Flanger.featureIdx;
	switch(feat){
		case AMP:{
			flng_amp_adjust((uint16_t)value*255);	
			break;
		}
		case FREQ:{
			flng_freq_adjust((uint16_t)value);	
			break;
		}
	}
}

// Alters the current LFO step value by value (+ or -)
// Step value determines frequency
// use an int32 for result to make boundry checking easy
// Clamps result to within min/max
void flng_freq_adjust(int16_t value){
	int32_t result = settings.step + value;
	if(result > STEP_MAX){
		result = STEP_MAX;
	}else if(result < STEP_MIN){
		result = STEP_MIN;
	}
	settings.step = (uint16_t)result;
}

// Alters the current LFO amplitude value by value (+ or -)
// Clamps result to within min/max
void flng_amp_adjust(int16_t value){
	int32_t result = settings.amplitude + value;
	if(result > AMP_MAX){
		result = AMP_MAX;
	}else if(result < AMP_MIN){
		result = AMP_MIN;
	}
	settings.amplitude = (uint16_t)result;
}

// Sends a string of my state to stdout
void flng_report(){
	features_t feat = (features_t)effect_Flanger.featureIdx;

	// Write to screen
	if(feat == AMP){
		display.setTextColor(0);
		display.fillRect(0,DISP_FEAT_Y,DISP_FEAT_W,13,1);
	}else{
		display.setTextColor(1);
	}
	display.print("Amp ");
  display.print(percentage(settings.amplitude, AMP_MAX, AMP_MIN), 2);
	display.print("%");

  if(feat == FREQ){
		display.setTextColor(0);
		display.fillRect(0,DISP_FEAT_Y+14,DISP_FEAT_W,13,1);
	}else{
		display.setTextColor(1);
	}
	display.setCursor(DISP_FEAT_INDENT,DISP_FEAT_Y+14);
  display.print("Freq ");
  display.print(flng_getHz(), 2);
	display.print("Hz");
}

// Returns the LFO frequency calculated from the step
float flng_getHz(){
	uint16_t step = settings.step; // This is volatile. Get it once
	uint8_t idx;
	uint8_t frac;
	float result;
	idx = (step >> 8);
	frac = (uint8_t)(step & 0x00ff);
	result = (float)(frac * BASEFREQ)/256;
	result += (float)(idx * BASEFREQ);
	return result;
}
