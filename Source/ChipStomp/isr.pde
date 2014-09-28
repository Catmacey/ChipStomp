/*
	Interrupt service routines
	Really important that the interupt priority here matches that declared in the setup
	Look in \hardware\pic32\cores\pic32\System_Defs.h for defines
*/

/*
  Rotary encoder code
  Whilst this isn't an ISR it is called during ISR hence its inclusion here.
  The code is based on this Arduino library
  https://github.com/brianlow/Rotary/blob/master/Rotary.cpp
*/

#define DIR_CCW 0x10
#define DIR_CW 0x20
/*
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */

#define R_START 0x0

#ifdef HALF_STEP
// Use the half-step state table (emits a code at 00 and 11)
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char g_enc_table[6][4] = {
  // R_START (00)
  {R_START_M,             R_CW_BEGIN,     R_CCW_BEGIN,  R_START},
  // R_CCW_BEGIN
  {R_START_M | DIR_CCW,   R_START,        R_CCW_BEGIN,  R_START},
  // R_CW_BEGIN
  {R_START_M | DIR_CW,    R_CW_BEGIN,     R_START,      R_START},
  // R_START_M (11)
  {R_START_M,             R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},
  // R_CW_BEGIN_M
  {R_START_M,             R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},
  // R_CCW_BEGIN_M
  {R_START_M,             R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW},
};
#else
// Use the full-step state table (emits a code at 00 only)
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char g_enc_table[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
#endif

extern "C" {
/*
	Change notification
*/
	void __ISR(_CHANGE_NOTICE_VECTOR, _CN_IPL_ISR) cn_isr(){
    uint8_t btn_state;
    uint8_t btn_diff;
    uint8_t enc_state;
		// Get the inverse of the port (btn press = low)
    uint16_t state = ~PORTB;
    // AND with the input pins 
    state &= 0b0000001110010000;
    // Move the lower byte
    btn_state = (uint8_t)(state & 0x00ff);
    // Get the difference between current and stored state
    btn_diff = (btn_state ^ g_input.btn_state.complete);
    if(btn_diff){
      // One of the buttons changed
      g_input.btn_state.complete = btn_state;
      g_input.btn_diff.complete = btn_diff;
    }
    
    // Handle the encoder RB8 and RB9 : We need them in bit0 & bit1 of this byte
    enc_state = (uint8_t)(state >> 8);
    g_input.encoder.state = g_enc_table[g_input.encoder.state & 0xf][enc_state];
    switch(g_input.encoder.state & 0x30){
      case DIR_CW:{
        g_input.encoder.value--;
        break;
      }
      case DIR_CCW:{
        g_input.encoder.value++;
        break;
      }
    }

    mCNBClearIntFlag();
  }
}


// Need to check with LA that the ADC timings used aren't impacting this effect ISR.
// I've set the ADC timing very generous (I think)...

extern "C" {
  void __ISR(_TIMER_1_VECTOR, ipl3) T1InterruptHandler() {
    int32_t buffer; // ADC Value read here - Buffer is 32bit to allow headroom
    int16_t output; // Actual value written to OC's
    Effect_t *currentEffect;
    Effect_t **currentAddr = &g_effects[0]; // Get Ptr2ptr in array pos zero
    //mPORTBSetBits(LCDDC_BIT);
    mT1ClearIntFlag();
    while ( ! mAD1GetIntFlag() ) { 
     // wait for the first conversion to complete so there will be vaild data in ADC result registers
    }
    // Sensor value is a 10 bit signed
    buffer = ReadADC10(0); 
    // ADC result is 10bit signed - boost it up to 16bits
    buffer *= 64;
    
    // Write input level buffer for VU meter
    g_meter.input[g_meter.tick] = (int16_t)buffer;
    
    mAD1ClearIntFlag(); //Clear ADC interrupt flag

    // Process the effects
    while(*currentAddr > 0){
      currentEffect = *currentAddr;
      if(currentEffect->state > 0){
        buffer = currentEffect->effectISR(buffer);
      }      
      currentAddr++;
    }

    // Hard clipping
    if(buffer > CLIPHARD) buffer = CLIPHARD;
    if(buffer < -CLIPHARD) buffer = -CLIPHARD;
    
    if(buffer > CLIPLEVEL){
      // Keep a running sum of clip events
      mPORTASetBits(CLIP_BIT);
    }else{
      mPORTAClearBits(CLIP_BIT);
    }

    // Write output level buffer for VU meter
    g_meter.output[g_meter.tick] = (int16_t)buffer;

    //convert back to unsigned for feeding to OC's
    output = (uint16_t)(buffer + 0x7fff);

    g_meter.tick++;
    g_meter.tick &= VUTICKLEN_MASK;

    SetDCOC4PWM((uint8_t)(output>>8)); 
    SetDCOC2PWM((uint8_t)(output)); 
  }
}