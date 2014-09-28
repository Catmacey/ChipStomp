/*
	Pitch Shifter functions
	Simplistic but quite effective
*/

#include <PLIB.h>
#include "effect_pitchshift.h"
	

//******** Private macros ********//

#define FEATURECOUNT 2  // Note : Default feature is 0 : It does nothing

#define BUFFER_SIZE 512 // * int16_t
#define WRAP_SHIFT 4
#define WRAP_SIZE (1 << WRAP_SHIFT) // How much overlap there is to reduce glitching


#define MIX_MAX 0xffff
#define MIX_MIN 0x0000
#define BEND_RANGE 0x1ff // This is the range that the user sees
#define BEND_MID ((BEND_RANGE / 2)+1)
#define READPOS_MAX_MASK ((BUFFER_SIZE << 8)-1)

//******** Private function declarations ********//

void pitch_nextFeature();
void pitch_adjustFeature(int16_t value);
uint8_t pitch_toggleOnOff();
int32_t pitch_effectISR(int32_t value);
void pitch_report();
void pitch_bend_adjust(int16_t value);
void pitch_mix_adjust(int16_t value);

//******** Private variables ********//

// Internal state variables
typedef struct {
    uint16_t mix;
    uint16_t writepos; // Buffer write index
    uint32_t readpos; // Tap read offset position int + 8bit fractional
    uint16_t step; // Playback rate (0x0100 = 1 step)
} settings_t;
static settings_t settings = {
		MIX_MAX / 2
	,	0
	, 0
	, 0x100
};

enum features_t {SAFE, MIX, BEND};
static const char *featurenames[] = {"Safe", "Mix","Bend"};

static int16_t pitch_buffer[BUFFER_SIZE]; // Sample grain

//******** Global variables ********//

// This struct is exposed globally via extern in the header
Effect_t effect_Pitchshift = {
		"Pitchbend"
	, 0
	, 0
	, pitch_nextFeature
	, pitch_adjustFeature
	, pitch_toggleOnOff
	, pitch_effectISR
	, pitch_report
};

//******** Function definitions ********//


// This is where the effect is actually processed
// We can't alter the input sample rate nor the final output sample rate.
// So to pitch shift we have a "playhead" that can increment at a fractional rate
// To avoid glitching when the record and play heads pass we cross fade for a few samples
// The initial plan was to grab two samples from the input buffer N and N+1 and interpolates between 
// them to produce a reasonable approx of what the actual sample might be.
// But that didn't work out well so SCREW IT! 
// This super naive single un-interpolated sample version sounds far better than the clever interpolated one.

int32_t pitch_effectISR(int32_t value){
	uint16_t idx, diff;
	int16_t sample;
	int32_t result;
	uint8_t diff_comp;

	// We always write at a constant rate
	pitch_buffer[settings.writepos] = (int16_t)value;
	
	idx = settings.readpos >> 8; // Get the upper integer bits
	if(idx > BUFFER_SIZE) idx = 0;
  // Increment the read position : Note use of 8bits of fractional
  // This allows the reading to be done at a different rate than writing
  settings.readpos += settings.step;
  settings.readpos &= READPOS_MAX_MASK; // Fast wrap around

	// Grab a sample
	sample = pitch_buffer[idx];

	// Difference between record and play heads : Used to determine if we should xfade
	diff = ( idx - settings.writepos + BUFFER_SIZE ) % BUFFER_SIZE;
	if(diff < WRAP_SIZE){
    // We need to cross-fade
		// Get current output sample multiplied by diff
    // Add sample for just before write head multiplied the complement of the diff
    // Divide result by length of wrap (wrap_shift)

		diff_comp = (WRAP_SIZE - diff);

    result = sample * diff;
    result += pitch_buffer[settings.writepos] * diff_comp;
		// store the final result back in sample
		sample = (int16_t)(result >> WRAP_SHIFT);
  }

  // Increment write position : check if position has gotten bigger than buffer size
  settings.writepos++;
	if (settings.writepos >= BUFFER_SIZE) {
    settings.writepos = 0; // reset
  }

  // Handle mixing
  // TODO : Actually mix the original signal with the mdified.
 	result = ((sample * settings.mix) >> 16);
  return result;
}

// Cycles my features
void pitch_nextFeature(){
	if(FEATURECOUNT <= 1) return;
	if(effect_Pitchshift.featureIdx < FEATURECOUNT) {
		effect_Pitchshift.featureIdx++;
	}else{
		// Skip the safe feature
		effect_Pitchshift.featureIdx = 1;
	}
}

// Turns me on or off
uint8_t pitch_toggleOnOff(){
	if(effect_Pitchshift.state) effect_Pitchshift.state = 0;
	else effect_Pitchshift.state = 1;
	return effect_Pitchshift.state;
}

// Adjust the value of the current feature
// Receives the encoder delta
void pitch_adjustFeature(int16_t value){
	features_t feat = (features_t)effect_Pitchshift.featureIdx;
	switch(feat){
		case MIX:{
			pitch_mix_adjust(value*512);	
			break;
		}
		case BEND:{
			pitch_bend_adjust(value);	
			break;
		}
	}
}

// Alters the current read step value by value (+ or -)
// use an int32 for result to make boundry checking easy
// Clamps result to min/max
void pitch_bend_adjust(int16_t value){
	int32_t result = settings.step + value;
	if(result > BEND_RANGE){
		result = BEND_RANGE;
	}else if(result < 0){
		result = 0;
	}
	settings.step = result;
	//settings.readpos = scaleAndClamp((uint16_t)result, BEND_RANGE, STEP_MIN, STEP_MAX);
}

// Alters the mix value by value (+ or -)
// Clamps result to within min/max
void pitch_mix_adjust(int16_t value){
	int32_t result = settings.mix + value;
	if(result > MIX_MAX){
		result = MIX_MAX;
	}else if(result < MIX_MIN){
		result = MIX_MIN;
	}
	settings.mix = (uint16_t)result;
}

// Sends a string of my state to stdout
void pitch_report(){
	features_t feat = (features_t)effect_Pitchshift.featureIdx;

	// Write to screen
	if(feat == MIX){
		display.setTextColor(0);
		display.fillRect(0,DISP_FEAT_Y,DISP_FEAT_W,13,1);
	}else{
		display.setTextColor(1);
	}
	display.print("Mix ");
  display.print(percentage(settings.mix, MIX_MAX, MIX_MIN), 2);
	display.print("%");

  if(feat == BEND){
		display.setTextColor(0);
		display.fillRect(0,DISP_FEAT_Y+14,DISP_FEAT_W,13,1);
	}else{
		display.setTextColor(1);
	}
  display.setCursor(DISP_FEAT_INDENT,DISP_FEAT_Y+14);
  display.print("Bend ");
  display.print(settings.step - BEND_MID, DEC);
  //display.print("mS");
	
}
