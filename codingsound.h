#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bass.h"
#include "bassenc.h"
#include <cmath>

#define DP 6.283185307179586476925286766559
#define OP 3.1415926535897932384626433832795
#define SR 48000.0
#define HSR 24000.0
#define HN 0.94387431268

float Pitch( int p )
{
	int i;
	float out;
	out = 1.0;
	
	if( p > 0 )
	{
		for( i = 0; i < p; i++ )
			out /= HN;
	}
	
	if( p < 0 )
	{
		for( i = 0; i > p; i-- )
			out *= HN;
	}
	
	return out;
}

typedef struct {
	float tones[100];
	float table[5000];
} ITABLE, *PTABLE;

#include "wavetable.h"
#include "codingsong.h"
#include "ultrahat.h"
#include "xnoise.h"
#include "xdrum.h"
#include "fromfile.h"
