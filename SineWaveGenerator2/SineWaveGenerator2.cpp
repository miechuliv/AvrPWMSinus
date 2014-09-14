/*
 * SineWaveGenerator2.cpp
 *
 * Created: 2014-09-10 21:59:15
 *  Author: miechuliv
 */ 




#define F_CPU 1000000L
#include <avr/io.h>



#include <avr/pgmspace.h>
#include <util/delay.h>

// tablica z wartoœciami jednego okresu sinusa 
uint8_t sine[256]={
	127,
	130,
	133,
	136,
	139,
	143,
	146,
	149,
	152,
	155,
	158,
	161,
	164,
	167,
	170,
	173,
	176,
	178,
	181,
	184,
	187,
	189,
	192,
	195,
	197,
	200,
	203,
	205,
	207,
	210,
	212,
	214,
	217,
	219,
	221,
	223,
	225,
	227,
	229,
	231,
	232,
	234,
	236,
	237,
	239,
	240,
	242,
	243,
	244,
	245,
	246,
	248,
	248,
	249,
	250,
	251,
	251,
	252,
	253,
	253,
	253,
	254,
	254,
	254,
	254,
	254,
	254,
	254,
	253,
	253,
	253,
	252,
	252,
	251,
	250,
	250,
	249,
	248,
	247,
	246,
	245,
	243,
	242,
	241,
	239,
	238,
	236,
	235,
	233,
	231,
	229,
	227,
	225,
	224,
	221,
	219,
	217,
	215,
	213,
	210,
	208,
	206,
	203,
	201,
	198,
	195,
	193,
	190,
	187,
	185,
	182,
	179,
	176,
	173,
	170,
	167,
	164,
	161,
	158,
	155,
	152,
	149,
	146,
	143,
	140,
	137,
	134,
	131,
	128,
	125,
	121,
	118,
	115,
	112,
	109,
	106,
	103,
	100,
	97,
	94,
	91,
	88,
	85,
	82,
	79,
	76,
	73,
	71,
	68,
	65,
	62,
	60,
	57,
	55,
	52,
	50,
	47,
	45,
	42,
	40,
	38,
	36,
	34,
	31,
	29,
	27,
	26,
	24,
	22,
	20,
	19,
	17,
	15,
	14,
	13,
	11,
	10,
	9,
	8,
	7,
	6,
	5,
	4,
	3,
	3,
	2,
	2,
	1,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	1,
	1,
	2,
	2,
	3,
	4,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	12,
	13,
	14,
	16,
	17,
	19,
	21,
	22,
	24,
	26,
	28,
	30,
	32,
	34,
	36,
	39,
	41,
	43,
	45,
	48,
	50,
	53,
	55,
	58,
	61,
	63,
	66,
	69,
	72,
	74,
	77,
	80,
	83,
	86,
	89,
	92,
	95,
	98,
	101,
	104,
	107,
	110,
	113,
	116,
	119,
	122,
};


int main(void)
{
	// wyjœciem rejestru OCR1A jest PB1
	DDRB |= (1 << DDB1);
	// PB1 is now an output
	

	// ustawiaj¹æ wartoœæ OCR2 ustawiamy wartoœæ wyjœciowa PWN ( chyba ? )
	OCR1A = 128;
	// set PWM for 50% duty cycle

	// rejestr kontroluj¹cy prace countera 
	// ustawiamy tryb none-inverting
	// @see https://sites.google.com/site/qeewiki/books/avr-guide/pwm-atmega8
	TCCR1A |= (1 << COM1A1);
	// set none-inverting mode

	// wybieramy tryb pracy Fast PWM / Phase corrected PWM
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	// set 10bit phase corrected PWM Mode


	// ustawiam prescaler na 8 , tzn. iteracja countera co ka¿de 8 cykli proca
	//TCCR1B |= (1 << CS11);
	// set prescaler to 8 and starts PWM

	TCCR1B |= (1 << CS10);
	// no prescaling
	


	

	
	

	
	
	while(1)
	{
		
		uint8_t delay,n,i;
		
		delay = 2;
		
		/*for(i=0;i<=254;i++)
		{
			// zmieniajac wartoœæ OCRO zmieniamy wartoœæ na wyjœciu PWM ( chyba ? )
			// przywpisujemy do rejstru OCRO kolejna próbke okresu sinusa
			// OOCR1A przyjmuje wartosc od 0 do 255, tak wiec amplituda sinusa to maks 128
			OCR1A=pgm_read_byte_near(sine+i);
			// petla która wykonuje 4 cykle proca na iteracje ( w praktyce pewnie troche wiecej )
			// @see delay_basic.h
			_delay_loop_2(delay);

		}*/
		
		for(i=0;i<=254;i++)
		{
			// zmieniajac wartoœæ OCRO zmieniamy wartoœæ na wyjœciu PWM ( chyba ? )
			// przywpisujemy do rejstru OCRO kolejna próbke okresu sinusa
			// OOCR1A przyjmuje wartosc od 0 do 255, tak wiec amplituda sinusa to maks 128
			// rejestr porównawczy OCR1A , tak d³ugo jak wartosc timera jest nizsza od wartosc OCR1A tak d³ugo na wyjsciu PWM ustawiony jest stan wysoki, po przekroczeniu wartosci ustawionej
			// na OCR1A ustawiony zostaje na PWM stan niski tak dlugo az timer dojdzie do wartosci maksymalnej i przeplni sie wracajac do zero
			// oznacza to ze jesli ustawimy OCR1A np: na 128 , timer zlicza od 0 ( na PWM jest stan wysoki ), timer dochodzi do wartosci rownej OCR1A ( 128 ) na PWM zostaje ustawiony stan niski
			// timer dochodzi do 255 i sie przelnia i zacznyna zliczac od 0 stan na PWM jest teraz wysoki....
			//OCR1A=pgm_read_byte_near(sine+i);
			//OCR1A=sine[i];
			// petla która wykonuje 4 cykle proca na iteracje ( w praktyce pewnie troche wiecej )
			// @see delay_basic.h
			//_delay_loop_2(delay*100000);

		}
		
		/*for(delay=1;delay<=10;delay++)
		{
			
			for(i=0;i<=254;i++)
			{
				// zmieniajac wartoœæ OCRO zmieniamy wartoœæ na wyjœciu PWM ( chyba ? )
				// przywpisujemy do rejstru OCRO kolejna próbke okresu sinusa
				// OOCR1A przyjmuje wartosc od 0 do 255, tak wiec amplituda sinusa to maks 128
				
				OCR1A=pgm_read_byte_near(sine+(i*delay));
				// petla która wykonuje 4 cykle proca na iteracje ( w praktyce pewnie troche wiecej )
				// @see delay_basic.h
				//_delay_loop_2(delay);

			}
		}*/
		
		// zmianna delay steruje czestotliwoscia sygnalu, czym wieksza jej wartosc tym nizsza czestotliwosc sygnalu
		/*for(delay=1;delay<=50;delay++)
		{
			// czas trwania sygnalu o danej czestotliwosc
			for(n=0;n<(51-delay);n++)
			{
				// jeden okres sinusa to 255 wykonan tej pelti , czym wiekszy delay tym mniejsza czestotliwosc sygnalu
				for(i=0;i<=254;i++)
				{
					// zmieniajac wartoœæ OCRO zmieniamy wartoœæ na wyjœciu PWM ( chyba ? )
					// przywpisujemy do rejstru OCRO kolejna próbke okresu sinusa 
					// OOCR1A przyjmuje wartosc od 0 do 255, tak wiec amplituda sinusa to maks 128
					OCR1A=pgm_read_byte_near(sine+i);
					// petla która wykonuje 4 cykle proca na iteracje ( w praktyce pewnie troche wiecej )
					// @see delay_basic.h
					_delay_loop_2(delay);

				}
			}
		}
		for(delay=50;delay>=2;delay--)
		{
			for(n=0;n<(51-delay);n++)
			{
				for(i=0;i<=254;i++)
				{
					OCR1A=pgm_read_byte_near(sine+i);
					_delay_loop_2(delay);
				}
			}
		}*/
	}
}

