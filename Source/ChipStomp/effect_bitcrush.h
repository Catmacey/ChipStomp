/*
	Header for Bitcrush Effect
	Each Effect is self contained
	The only interface declared is the Effect_t
	
	Effects must provide a struct to comply with Effect_t;		

	Build the array of Effects in the main file (the one with setup() and loop())
*/
#ifndef __Effect_Bitcrush__
#define __Effect_Bitcrush__

#include "config.h"
#include "Effect_typeDefs.h"

extern Effect_t effect_Bitcrush;


#endif
