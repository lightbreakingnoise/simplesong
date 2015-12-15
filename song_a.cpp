#include "codingsound.h"

int main()
{
	BASS_Init( 0, 44100, 0, 0, 0 );
	
	CodingSong *song = new CodingSong( 125.0, 32, 200 );
	XNoise *nos = new XNoise();
	XDrum *xd = new XDrum();
	UltraHat *hat = new UltraHat( 2000 );
	FromFile *funky = new FromFile( "funky.wav" );
	FromFile *gett = new FromFile( "get.wav" );
	
	int c;
	
	while( song->getC() < song->getN() )
	{
		c = song->getC();

		if( c%16 == 0 )
		{
			nos->Noise( song->getL(), 19, 0.25, song->get16(4), song->getLFO(2.0) );
			nos->Noise( song->getR(), 19, 0.25, song->get16(4), song->getLFO(2.0) );
		}
		if( c%16 == 6 )
		{
			nos->Noise( song->getL(), 22, 0.25, song->get16(4), song->getLFO(3.0) );
			nos->Noise( song->getR(), 22, 0.25, song->get16(4), song->getLFO(3.0) );
		}
		if( c >= 128 )
		{
			if( c%16 == 12 )
			{
				nos->Noise( song->getL(), 36, 0.35, song->get16(5), song->getLFO(1.0) );
				nos->Noise( song->getR(), 36, 0.35, song->get16(5), song->getLFO(1.0) );
			}
		}
		if( c >= 256 )
		{
			if( c%16 == 15 )
			{
				nos->Noise( song->getL(), 39, 0.75, song->get16(2), song->getLFO(3.0) );
				nos->Noise( song->getR(), 39, 0.75, song->get16(2), song->getLFO(3.0) );
			}
		}
		if( c >= 128 )
		{
			if( c%16 == 0 )
				funky->MixEcho( song->getL(), song->getR(), 0.6, song->get16(3), 0.2 );
			if( c%16 == 14 )
				gett->MixEcho( song->getL(), song->getR(), 0.4, song->get16(3), 0.2 );
		}
		
		if( c < 192 || c >= 256 )
		{
			if( c%4 == 2 )
			{
				hat->Hat( song->getL(), 38, 0.1, song->get16(1) / 2 );
				hat->Hat( song->getR(), 38, 0.1, song->get16(1) / 2 );
				hat->Hat( song->getL(), 38+2, 0.1, song->get16(1) / 2 );
				hat->Hat( song->getR(), 38+2, 0.1, song->get16(1) / 2 );
				hat->Hat( song->getL(), 38+3, 0.1, song->get16(1) / 2 );
				hat->Hat( song->getR(), 38+3, 0.1, song->get16(1) / 2 );
				hat->Hat( song->getL(), 38+6, 0.1, song->get16(1) / 2 );
				hat->Hat( song->getR(), 38+6, 0.1, song->get16(1) / 2 );
			}
		}
		
		if( c%64 == 0 )
		{
			fputs( "-", stdout );
			fflush( stdout );
		}
		
		song->next();
	}
	
	song->reset(4);
	while( song->getC() < song->getN() )
	{
		c = song->getC();
		
		if( c < 192 || c >= 256 )
		{
			if( c%4 == 0 )
			{
				xd->BassDrum( song->getL(), 0.8 );
				xd->BassDrum( song->getR(), 0.8 );
			}
		}
		if( c == 254 )
		{
			xd->BassDrum( song->getL(), 0.8 );
			xd->BassDrum( song->getR(), 0.8 );
		}

		if( c%128 == 0 )
		{
			fputs( "=", stdout );
			fflush( stdout );
		}
		
		song->next();
	}

	song->toFile();
	puts( "ich habe fertig" );
	
	return 0;
}
