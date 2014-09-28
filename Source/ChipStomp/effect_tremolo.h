/*
	Header for LFO Effect
	Each Effect is self contained
	The only interfac declared is the Effect_t
	
	Effects must provide a struct to comply with Effect_t;		

	Build the array of Effects in the main file (the one with setup() and loop())
*/
#ifndef __Effect_Tremolo__
#define __Effect_Tremolo__

#include "config.h"
#include "Effect_typeDefs.h"

extern Effect_t effect_Tremolo;

#endif
