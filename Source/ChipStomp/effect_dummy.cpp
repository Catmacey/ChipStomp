/*
	This is a dummy effect
	Just a place holder nothing else
*/
#include <PLIB.h>
#include "effect_dummy.h"

//******** Private macros ********//

#define FEATURECOUNT 4

//******** Private function declarations ********//

void nextFeature();
void dummy_adjustFeature(int16_t value);
uint8_t dummy_toggleOnOff();
int32_t effectISR(int16_t value);
void dummy_report();

//******** Private variables ********//

// Internal state variables


//******** Global variables ********//

// This struct is exposed globally via extern in the header
Effect_t effect_dummy = {
		"Dummy"
	, 0
	, 0
	, 0
	, dummy_adjustFeature
	, dummy_toggleOnOff
	, 0
	, dummy_report
};
/*
	, nextFeature
	, adjustFeature

	, effectISR
*/


//******** Function definitions ********//

// Cycles my features
uint8_t dummy_toggleOnOff(){
	if(effect_dummy.state) effect_dummy.state = 0;
	else effect_dummy.state = 1;
	return effect_dummy.state;
}

// Adjust the value of the current feature
// Receives the encoder delta
void dummy_adjustFeature(int16_t value){
	// Currently hard coded to alter the step
	
}

// Sends a string of my state to stdout
void dummy_report(){
	// Serial.println("Dummy has no state.");
}