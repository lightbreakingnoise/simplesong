class XNoise
{
	public:
	XNoise()
	{
	}

	void Noise( float *out, int note, float vol, int len, float lfrq )
	{
		float freq;
		freq = 27.5*Pitch(note);
		int i;
		int n;
		float phase;
		phase = -1.0;
		float inc;
		inc = 2.0 / SR * freq;
		float sam;
		float noise;
		noise = 0.0;
		float nextnoise;
		float noiseinc;
		nextnoise = ((float)(rand()%100) / 50.0) - 1.0;
		noiseinc = (nextnoise - noise) / 50.0;
		int ndest;
		ndest = 50;
		int nlen;
		float v;
		v = 2.0;
		float vdec;
		vdec = 2.0 / (float)len;
		
		float lph;
		lph = -1.0;
		float linc;
		linc = 2.0 / SR * lfrq;
		
		float hi;
		hi = 0.0;
		float low;
		low = 0.0;
		float low2;
		low2 = 0.0;
		float q;
		
		for( n = 0; n < len; n++ )
		{
			sam = noise + phase;
			
			noise += noiseinc;
			if( n == ndest )
			{
				nextnoise = ((float)(rand()%100) / 50.0) - 1.0;
				nlen = 5 + (rand()%50);
				noiseinc = (nextnoise - noise) / (float)nlen;
				ndest += nlen;
			}
			
			if( lph < 0.0 )
			{
				sam *= 3.0;
				q = 200.0 / HSR;
			}
			else
				q = 2500.0 / HSR;
			
			sam *= v;
			v -= vdec;
			
			hi += (sam - hi) * q;
			sam -= hi;
			low -= (low - sam) * q;
			sam = low;
			low2 -= (low2 - sam) * q;
			sam = low2;
			
			out[n] += vol * sam;

			phase += inc;
			if( phase >= 1.0 )
				phase -= 2.0;
			lph += linc;
			if( lph >= 1.0 )
				lph -= 2.0;
		}
	}
};
