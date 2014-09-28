/*
	Echo functions
	Currently only a single tap.

	This echo has a lo-fi "tape" that records the current input. This is then 
	tapped at an adjustable delay offset and amplitude to introduce an echo.
	When combined with a little bit of analog feedback it gives quite a nice
	sustained echo.

	The "tape" actually uses a sample rate that is much lower than the main 
	input/output sample loop. I'm currently using 8:1 ratio.
	This drastically reduces the fidelity of the echo but it's not noticable.
	Even using a ratio of 8:1 with an effective sample rate of just 5.5Khz 
	sounds really nice. Echo's are not typically as "hi-fi" as the source signal 
	and we are focussing on a bass effect pedal so it works well.
	The advantage of course is that it increases the max echo delay for the same 
	amount of RAM allocated to the buffer.  4Kb of buffer at 8:1 gives nearly
	a second of delay.
	
	To reduce aliasing I'm storing the input in a small buffer and averaging the 
	the sum before storing it in the "tape" every Nth sample.  
	Then I interpolate the output to help recreate missing samples for the taps.
	I guess the averaging also introduce a small amount of low-pass filter.

	I wonder if I could actually just use 8bit for this, therefore doubling the 
	length again for the same memory

	Might add additional taps, each at 1/2 amplitude of prev tap. Doesn't seem
	necessary when using the analog feedback gives a good result.

*/
#include <PLIB.h>
#include "effect_echo.h"
	

//******** Private macros ********//

#define BUFFSIZE 4096 // int16_t so that's 8kb!
#define IDXRATIO 8 // Ratio of main sample rate for echo buffer
#define IDXSHIFT 3 // Number of bits to shift to match IDXRATIO
#define FEATURECOUNT 2  // Note : Default feature is 0 : It does nothing
#define AMP_MAX 0xffff
#define AMP_MIN 0x0000
#define DELAY_MAX (BUFFSIZE - IDXRATIO - 1)
#define DELAY_MIN 0x0001
#define DELAY_RANGE 200 // This is the range that the user sees

//******** Private function declarations ********//

void echo_nextFeature();
void echo_adjustFeature(int16_t value);
uint8_t echo_toggleOnOff();
int32_t echo_effectISR(int32_t value);
void echo_report();
void echo_delay_adjust(int16_t value);
void echo_amp_adjust(int16_t value);
float echo_getDelayMs();
uint16_t scaleAndClamp(uint16_t value, uint16_t range, uint16_t min, uint16_t max);

//******** Private variables ********//

// Internal state variables
typedef struct {
    uint16_t writepos; // Buffer write index
    uint16_t amplitude;
    uint16_t readpos; // Tap read offset position
    uint16_t delay; // Delay - Scaled user input
} settings_t;
static settings_t settings = {
		0
	,	AMP_MAX / 2
	, DELAY_MAX / 2
};

enum features_t {SAFE, AMP, DELAY};
static const char *featurenames[] = {"Safe", "Amplitude","Delay"};

static int16_t echo_buffer[BUFFSIZE]; // Main "tape"
static int16_t echo_lpf[IDXRATIO]; // Input buffer

//******** Global variables ********//

// This struct is exposed globally via extern in the header
Effect_t effect_Echo = {
		"Echo"
	, 0
	, 0
	, echo_nextFeature
	, echo_adjustFeature
	, echo_toggleOnOff
	, echo_effectISR
	, echo_report
};

//******** Function definitions ********//


// This is where the effect is actually processed
// Note this function could be made much more memory efficiant
// by reusing variables, at the cost of being much hard to read
int32_t echo_effectISR(int32_t value){
	uint16_t idx;
	int16_t sample1, sample2;
	int32_t result;
	uint8_t frac, tmp;

	frac = (uint8_t)(settings.writepos & (IDXRATIO-1)); // fetch the lower fractional bits
	idx = settings.writepos++ >> IDXSHIFT; // Get the upper integer bits
	// check if writepos has gotten bigger than buffer size
  if (settings.writepos >= (BUFFSIZE * IDXRATIO)) {
    settings.writepos = 0; // reset writepos
  }
	// store incoming data every nth samples
  echo_lpf[frac] = (int16_t)value;
  
  if(frac == 0){
  	// Every nth, write the average
  	result = 0;
  	for(tmp=0;tmp<IDXRATIO;tmp++){
  		result += echo_lpf[tmp];
  	}
  	result >>= IDXSHIFT;
  	echo_buffer[idx] = (int16_t)result;
  }
  
  // Get position to read from
  //idx = settings.writepos + (DELAY_MAX - (settings.readpos >> 8));
  idx += (DELAY_MAX - settings.readpos);
  // if we've gone over the table boundary -> wrap it
  if (idx >= BUFFSIZE) {
    idx -= BUFFSIZE;
  }
  sample1 = echo_buffer[idx];
  idx++;
  // check if we've gone over the boundary.
  if (idx >= BUFFSIZE) {
    idx = 0;
  }
	sample2 = echo_buffer[idx];
  // Interpolate between samples
  // multiply each sample by the fractional distance to the actual settings.location  value
  // scale sample 2
  sample2 = (sample2 * frac) >> IDXSHIFT;
  // scale sample 1
  sample1 = (sample1 * (IDXRATIO - frac )) >> IDXSHIFT;
  // Add samples together to get an average, result is now in sample2 
  sample2 += sample1;
  // Echo value
  //result = ((sample2 * settings.amplitude) >> 16);
  result = value + ((sample2 * settings.amplitude) >> 16);
//  result = value >> 1;
  return result;
}

// Cycles my features
void echo_nextFeature(){
	if(FEATURECOUNT <= 1) return;
	if(effect_Echo.featureIdx < FEATURECOUNT) {
		effect_Echo.featureIdx++;
	}else{
		// Skip the safe feature
		effect_Echo.featureIdx = 1;
	}
}

// Turns me on or off
uint8_t echo_toggleOnOff(){
	if(effect_Echo.state) effect_Echo.state = 0;
	else effect_Echo.state = 1;
	return effect_Echo.state;
}

// Adjust the value of the current feature
// Receives the encoder delta
void echo_adjustFeature(int16_t value){
	features_t feat = (features_t)effect_Echo.featureIdx;
	switch(feat){
		case AMP:{
			echo_amp_adjust(value*512);	
			break;
		}
		case DELAY:{
			echo_delay_adjust(value);	
			break;
		}
	}
}

// Alters the current echo delay value by value (+ or -)
// use an int32 for result to make boundry checking easy
// Clamps result to min/max
void echo_delay_adjust(int16_t value){
	int32_t result = settings.delay + value;
	if(result > DELAY_RANGE){
		result = DELAY_RANGE;
	}else if(result < 0){
		result = 0;
	}
	settings.delay = result;
	settings.readpos = scaleAndClamp((uint16_t)result, DELAY_RANGE, DELAY_MIN, DELAY_MAX);
}

// Alters the Echo amplitude value by value (+ or -)
// Clamps result to within min/max
void echo_amp_adjust(int16_t value){
	int32_t result = settings.amplitude + value;
	if(result > AMP_MAX){
		result = AMP_MAX;
	}else if(result < AMP_MIN){
		result = AMP_MIN;
	}
	settings.amplitude = (uint16_t)result;
}

// accepts a smaller input : outputs the scalled output clamped to within min max
uint16_t scaleAndClamp(uint16_t value, uint16_t range, uint16_t min, uint16_t max){
	uint16_t outrange = max - min;
	float ratio = (float)value / range;
	if(ratio > 1) ratio = 1;
	return (uint16_t)(ratio * outrange);
}

// Sends a string of my state to stdout
void echo_report(){
	features_t feat = (features_t)effect_Echo.featureIdx;

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

  if(feat == DELAY){
		display.setTextColor(0);
		display.fillRect(0,DISP_FEAT_Y+14,DISP_FEAT_W,13,1);
	}else{
		display.setTextColor(1);
	}
  display.setCursor(DISP_FEAT_INDENT,DISP_FEAT_Y+14);
  display.print("Delay ");
  display.print(echo_getDelayMs(), 0);
  display.print("mS");
}

// Returns the delay period from the step
float echo_getDelayMs(){
	float result = SAMPLETIME * 8 * settings.readpos;
	return result;
}
