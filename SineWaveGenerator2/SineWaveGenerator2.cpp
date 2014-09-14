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

uint8_t i;
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


/************************************************************************/
/* Generowanie pojedyczego sinusa za pomoca PWM. Zasada dzia³ania:
Rejestr OCR1A s³uzy jako rejestr porównawczy. Timer zlicza wartosci od 0 do 255 i za kazdym razem poruwnuje z wartoscia rejestru OCR1A,
tak d³ugo jak wartoœæ timera jest mniejsza ni¿ wartoœæ OCR1A tak d³ugo na wyjœciu PWM bedzie stan wysoki, po przekroczeniu przez timer wartoœæi na OCR1A 
stan na wyjœciu PWM zostaje ustawiony na niski , OCR1A tak samo jak timer jest 8-bitowym rejestrem tak wiec maks wartosc wynosi 255, 
ustawiajac wartosc 128 dla rejestru OCR1A otrzymujemy na wyjsciu PWM sygna³ prostokatny o 50% wype³nieniu.                                                                     */
/************************************************************************/
int main(void)
{
	// wyjœciem rejestru OCR1A jest PB1
	DDRB |= (1 << DDB1);
	
	

	// ustawiaj¹æ wartoœæ OCR2 ustawiamy % wype³nienia sygna³u na wyjœciu PWM. % Wype³nienia = (wartosc_przypisana_do_OCR1A / 256) * 100%
	// (128 / 256) * 100% = 50% wype³nienia
	OCR1A = 128;
	

	// rejestr kontroluj¹cy prace countera 
	// ustawiamy tryb none-inverting: w tyme trybie gdy timer < OCR1A = stan wysoki, gdy timer > OCR1A = stan niski , w trybie inverting jest odwrotnie
	// @see https://sites.google.com/site/qeewiki/books/avr-guide/pwm-atmega8
	TCCR1A |= (1 << COM1A1);
	

	// wybieramy tryb pracy Fast PWM / Phase corrected PWM
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	


	// ustawiam prescaler na 8 , tzn. iteracja countera co ka¿de 8 cykli proca
	TCCR1B |= (1 << CS11);
	

	//TCCR1B |= (1 << CS10);
	// no prescaling
	


	
	
	while(1)
	{
		
		for(i=0;i<256;i++)
		{
			
			OCR1A = sine[i];
			_delay_loop_2(8);
		}
	}
}

