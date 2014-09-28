/*
	Definitions for the Effect and EffectManager
	Need to be include in main as well as in all effect files

*/

#ifndef __Effect__
#define __Effect__

#include "WProgram.h"
#include <stdint.h>
#include <Catmacey_SH1106.h>

#define EFFECTCOUNT 6

// Each Effect
typedef struct {
  char* name; // Name of effect
  uint8_t state; // 0x01 = on, 0x00 = off
  uint8_t featureIdx; // Feature 0 is a safe dummy feature that does nothing
  void (*nextFeature)(); // Cycles to the next Feature
  void (*adjustFeature)(int16_t); // Receives the encoder values
  uint8_t (*toggleOnOff)(); // Turns the Effect On/Off
  int32_t (*effectISR)(int32_t); // Called in the main ISR arg is the input buffer. Returns the modified sample
  void (*report)(); // Prints a report of the Effects current state to stdout.
} Effect_t;

// Global Effect manager
typedef struct {
  // nextEffect // Doesn't need to be here : // Function to select next Effect
  uint8_t effectIdx; // Currently selected Effect use this to pass through to functions
  Effect_t effects[EFFECTCOUNT]; // Array of available Effects
} EffectManager_t;

extern Catmacey_SH1106 display;

#endif
