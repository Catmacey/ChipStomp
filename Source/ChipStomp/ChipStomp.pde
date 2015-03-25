// 
// ChipStomp
// Multifunction audio effects processor built on a Microchip PIC32MX
//

/*
	Reads mono audio in on the ADC
	Processes it with one or more digital effects
	Sends it out on two 8bit PWM summed together to form a 16bit mono output

	Hardware is a combination of the ChipKit DP32 and an Open Labs StompShield
	StompShield : Shield http://www.openmusiclabs.com/projects/stomp-shield/
	DP32 : https://digilentinc.com/Products/Detail.cfm?NavPath=2,892,1174&Prod=CHIPKIT-DP32
	Display is a 128x64 px SH1106 based OLED

	Copyright (C) 2014 Matt Casey : catmacey.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#define VERSION "1.0"

#include <PLIB.h>  // Use this Microchip library to make access to the peripherals easier
#include <DSPI.h>
#include <Adafruit_GFX.h>
#include <Catmacey_SH1106.h>
#include "config.h"

// Each effect is it's own self contained module
#include "Effect_typeDefs.h"
#include "effect_tremolo.h"
#include "effect_flanger.h"
#include "effect_echo.h"
#include "effect_bitcrush.h"
#include "effect_dummy.h"
#include "effect_pitchshift.h"
// #include "effect_sinus.h"

// Effects stack : Important that the last one is NULL so that we are a the end.
Effect_t *g_effects[] = {
			&effect_Tremolo
		, &effect_Flanger
		, &effect_Pitchshift
		, &effect_Bitcrush
		, &effect_Echo
		// , &effect_Sinus
		, NULL
	};

// TODO : Create a distortion effect with configuable threshold, shoft/hard clipping.
// TODO : Add a metronome effect (last in the chain) with config bpm/volume.
// TODO : Improve input sampling by oversampling (running ADC at faster rate then averaging the results)
// TODO : Add "cost" to each effect (measured using LA) to allow user to select effects that fit withing the overall CPU budget.
// TODO : Allow user to change order or load-out of effects to allow duplication of effects?
// TODO : Allow user to save their current config and effect values. Provide interface to load these saves.
// TODO : Bandpass|HP|LP filters? Might be too CPU intensive to run concurrent with other effects. (Hence need for cost/budget)

// Digilent hardware SPI library
DSPI0 spi;
// OLED Driver : Uses Adafruit GFX library
Catmacey_SH1106 display(OLED_DC, OLED_RESET, OLED_CS, &spi);

// Global for holding the state of the various inputs
InputState_t g_input;
// Global struct for holding VU values. Used by both ISR and main()
volatile VUMeter_t g_meter;

// USed for managing the input 
enum btnmode_t {START, TOGGLE, HOLD};
// Only used for debugging above
const char *btnmode_str[] = {"Nada","Toggle","Hold"};


// Arduino setup routine
void setup() {
	// set the digital pin as output:
	mPORTASetPinsDigitalOut(DACHI_BIT | CLIP_BIT | OLEDRES_BIT);
	mPORTBSetPinsDigitalOut(OLEDCS_BIT | MOSI_BIT | OLEDDC_BIT | DACLO_BIT | SCLK_BIT);
	mPORTBSetPinsDigitalIn(ENCA_BIT | ENCB_BIT | BTNEFFECT_BIT | BTNSELECT_BIT | ENCBTN_BIT);
	
	// Set up PPS for OC (Note: Arduino pin numbers)
	mapPps(DACH, PPS_OUT_OC4);
	mapPps(DACL, PPS_OUT_OC2);

	// DPSPI.begin() sets up PPS for us

	// Setup change notification with pullups for the buttons and rotary encoder with pullups for the rotary encoder
	// | CNB15_ENABLE
	mCNBOpen(CNB_ON, CNB4_ENABLE | CNB7_ENABLE | CNB8_ENABLE | CNB9_ENABLE, CNB8_PULLUP_ENABLE | CNB9_PULLUP_ENABLE);
	// Read the port to start the ball rolling
	mPORTBRead();
	// Start CN interrupt
	ConfigIntCNB(CHANGE_INT_ON | _CN_IPL_IPC);
	
	// Setup the two 8bit PWM outputs
	OpenTimer3(T3_ON | T3_PS_1_1, 256);
	OpenOC4(OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
	OpenOC2(OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
	delay(1);

	// Setup ADC
	CloseADC10();
	// Set ADC input as AN11 and reference as GND
	SetChanADC10( ADC_CH0_POS_SAMPLEA_AN11 | ADC_CH0_NEG_SAMPLEA_NVREF);
	// Configure and turn on ADC
	OpenADC10( 
			// ouTput in integer | trigger mode auto | enable autosample 
			ADC_FORMAT_SIGN_INT32 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON 
			//ADC ref internal | disable offset test | disable scan mode | Interrupt after X samples | use dual buffers | use alternate mode
		, ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF 
			// use ADC PB clock| set sample time | auto
		, ADC_CONV_CLK_PB | ADC_SAMPLE_TIME_31 
			// Enable only AN11
		, ENABLE_AN11_ANA
			// Don't scan channels (we're only using a single channel)
		, SKIP_SCAN_ALL  
	);
	// Set the ADC conversion clock pretty fast.
	// This results in a fast sampling speed. (I think)
	AD1CON3bits.ADCS = 0x01;
	EnableADC10();

	// Setup timer to trigger ISR for main processing routine.
	// Timer is set to the desired sample rate (eg. 44.1khz)
	ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_3);
	OpenTimer1(T1_ON | T1_PS_1_1, F_CPU / SAMPLERATE);

	// Set the default duty cycles for the PWMs
	SetDCOC4PWM(0x7f); 
	SetDCOC2PWM(0xff); 
	

	// Setup hardware SPI. Not we're not using MISO
	spi.begin(0, SPI_MOSI, OLED_CS);
	spi.setSpeed(10000000);
 	
 	// Initialize the OLED using the internal DC/DC convertor
	display.begin();
	// Load the spashscreen into the displaybuffer
	display.drawBitmap(0, 0, g_splashscreen, 128, 64, 1);
	display.display(); // show splashscreen
	
	// Setup serial for debugging
	Serial.begin(115200);
	// Wait. Cos I read that you must wait after enabling serial debugging before you use it.
	// We use this delay to show the splashscreen for a bit
	delay(2000);
	
	// init done
}
	
void loop() {
	//Serial.println("loop.start");
	uint8_t idx = 0;
	uint8_t effectCount = 0;
	uint8_t somethinghappened = false;
	int tmp, addr = 0;
	
	uint16_t ctr;

	btnmode_t mode = START;  // Default button mode
	char buff[100];
	Effect_t *currentEffect;
	Effect_t **currentAddr = &g_effects[0]; // Get Ptr2ptr in array pos zero
	// Start with currentEffect as first one
	currentEffect = *currentAddr;
	InputState_t input;

	mPORTAToggleBits(CLIP_BIT);
	display.setTextColor(1);
	display.setCursor(2,53);
	display.print("Version ");
	display.print(VERSION);
	display.display();

	delay(500);
	mPORTAToggleBits(CLIP_BIT);
	delay(500);
	display.clearDisplay();   // clears the buffer
	display.display();
	mPORTAToggleBits(CLIP_BIT);

	// Set this to cause the display to be rendered on the first run through
	somethinghappened = true;

	// Loop here. Not using the Arduino loop().
	while(1){
		// Grab a copy : It changes fast
		input = g_input;
		if(input.btn_diff.complete){
			/*
				TODO: Would like to add a timeout so that if the Effect
				button is held for too long then it drops back to START
				This might be handy where you press the button in error
				, just hold it until it times out.
				Could maybe also have a timeout for the Effect's featureIdx.
				After a period of no input it would reset to the dummy feature (0)
			*/ 
			/*
				TODO: Might be useful to add some sort of "acceleration" factor
				to the input from the encoder. It takes ages to go from end to end 
				of the scale. Maybe if the encoder delta is > X we double it?
			*/
			switch(mode){
				case TOGGLE:
				case HOLD:{
					if(input.btn_diff.effect & !input.btn_state.effect){
						// Released the effect button
						if(mode == HOLD){
							// No other button was pressed
							// Serial.println("Switch");
							// Each press should cycle through the available g_effects
							//Serial.print("Switch Effect to ");
							currentAddr++;
							if(*currentAddr == 0){
								currentAddr = &g_effects[0];
							}
							currentEffect = *currentAddr;
							//Serial.println(currentEffect->name);
							// sprintf(buff, "currentEffect size:%d, addr:%p, ptrAddr:%x \n", sizeof(*currentEffect), currentEffect, *currentAddr);
							// Serial.println(buff);
							// Flag that something has happened
							somethinghappened = true;        
						}
						mode = START;
					}else if(input.btn_diff.select & !input.btn_state.select){
						// Released the select button
						//Serial.println("Toggle");
						currentEffect->toggleOnOff();
						//Serial.print(currentEffect->name);
						//Serial.println(currentEffect->state?" ON":" OFF");
						// Switch mode to indicate that we've done this
						mode = TOGGLE;
						// Flag that something has happened
						somethinghappened = true;
					}

					break;
				}
				case START:{
					// No other buttons held : This is the start of something.
					if(input.btn_diff.effect & input.btn_state.effect & !input.btn_state.select){
						// Pressed the effect button (ignore if select is pressed)
						mode = HOLD;
					}
					if(input.btn_diff.select & input.btn_state.select){
						// Released the select button
						//Serial.println("Next feature");
						currentEffect->nextFeature();
						// Flag that something has happened
						somethinghappened = true;
					}


					break;
				}
			}
			//sprintf(buff, "Now Mode:%d:%s", mode, btnmode_str[mode]);
			//Serial.println(buff);

			// Need to clear btn_diff once you've "used" it
			g_input.btn_diff.complete = 0;
			
		}
		if(input.encoder.value != 0){
			//Serial.print("Encoder:");
			//Serial.print(input.encoder.value, DEC);
			input.encoder.value *= abs(input.encoder.value);
			//Serial.print(" : ");
			//Serial.println(input.encoder.value, DEC);
			// Encoder has been twiddled
			if(input.btn_state.effect){
				// Choose effect
				// lfo_step_alter(input.encoder.value);
			}else{
				currentEffect->adjustFeature(input.encoder.value);
			}

			// Set the value to zero once used
			g_input.encoder.value = 0;
			// Flag that something has happened
			somethinghappened = true;
		}

		if(somethinghappened){
			// Output a report of current state
			// The first line is the same for all effects
			display.clearDisplay();
			display.setCursor(0,DISP_FEAT_INDENT);
			display.setTextColor(1);
			display.print(currentEffect->name);
			display.drawFastHLine(0,17,DISP_FEAT_W,1);
			if(currentEffect->state){
				display.setTextColor(0);
				display.fillRect(98,0,25,18,1);
				display.setCursor(105,2);
				display.print("on");
			}else{
				display.drawRect(98,0,25,18,1);
				display.setCursor(103,2);
				display.print("off");
			}
			display.setTextColor(1);
			// Other lines are specifc to the effect and its internal settings
			display.setCursor(DISP_FEAT_INDENT,DISP_FEAT_Y);
			//display.setTextSize(1);
			currentEffect->report();
			somethinghappened = false;
		}

		// Render the VU bars
		renderVU();

		// Now render the whole display buffer
		display.display();

		delay(35);
		mPORTBToggleBits(BIT_2);
	} //while
}

// Render the input and output V meters
void renderVU(){
	uint8_t idx, yi, yo, ypo, ypi;
	uint32_t sum_out, sum_in;

	sum_in = 0;
	sum_out = 0;
	// First do the averaging
	for(idx=0; idx < VUTICKLEN; idx++){
		sum_in += abs(g_meter.input[idx]);
		sum_out += abs(g_meter.output[idx]);
	}

	sum_in /= VUTICKLEN;
	sum_out /= VUTICKLEN;
	// The sums should now contain an average of the last N samples
	// Scale is 15bits (half a 16bit signed int)
	// Shift them down to 6 bits to fit in vertical scale of screen
	sum_in >>= 9;
	sum_out >>= 9;
	yi = 63-sum_in;
	yo = 63-sum_out;

	if(sum_in > g_meter.peak_in) g_meter.peak_in = sum_in;
	else if(g_meter.peak_in > 1) g_meter.peak_in-=2;

	if(sum_out > g_meter.peak_out) g_meter.peak_out = sum_out;
	else if(g_meter.peak_out > 1) g_meter.peak_out-=2;

	ypi = 63-g_meter.peak_in;
	ypo = 63-g_meter.peak_out;

	// Clear space
	display.drawFastVLine(124,0,63,0);
	display.drawFastVLine(125,0,63,0);
	display.drawFastVLine(126,0,63,0);
	display.drawFastVLine(127,0,63,0);
	// VU input
	display.drawFastHLine(124,ypi,2,1);
	display.drawFastVLine(124,yi,sum_in,1);
	display.drawFastVLine(125,yi,sum_in,1);
	
	display.drawFastHLine(126,ypo,2,1);
	display.drawFastVLine(126,yo,sum_out,1);
	display.drawFastVLine(127,yo,sum_out,1);
	
}


// Returns a pergentage value (float)
float percentage(uint16_t value, uint16_t max, uint16_t min){
	float result, frac;
	uint16_t range, offset;
	range = max - min;
	offset = value - min;
	frac = (float)offset/range;
	result = frac * 100;
	return result;
}
