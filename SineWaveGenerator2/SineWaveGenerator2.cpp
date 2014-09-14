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


/************************************************************************/
/* Generowanie pojedyczego sinusa za pomoca PWM. Zasada dzia�ania:
Rejestr OCR1A s�uzy jako rejestr por�wnawczy. Timer zlicza wartosci od 0 do 255 i za kazdym razem poruwnuje z wartoscia rejestru OCR1A,
tak d�ugo jak warto�� timera jest mniejsza ni� warto�� OCR1A tak d�ugo na wyj�ciu PWM bedzie stan wysoki, po przekroczeniu przez timer warto��i na OCR1A 
stan na wyj�ciu PWM zostaje ustawiony na niski , OCR1A tak samo jak timer jest 8-bitowym rejestrem tak wiec maks wartosc wynosi 255, 
ustawiajac wartosc 128 dla rejestru OCR1A otrzymujemy na wyjsciu PWM sygna� prostokatny o 50% wype�nieniu.                                                                     */
/************************************************************************/
int main(void)
{
	// wyj�ciem rejestru OCR1A jest PB1
	DDRB |= (1 << DDB1);
	
	

	// ustawiaj�� warto�� OCR2 ustawiamy % wype�nienia sygna�u na wyj�ciu PWM. % Wype�nienia = (wartosc_przypisana_do_OCR1A / 256) * 100%
	// (128 / 256) * 100% = 50% wype�nienia
	OCR1A = 128;
	

	// rejestr kontroluj�cy prace countera 
	// ustawiamy tryb none-inverting: w tyme trybie gdy timer < OCR1A = stan wysoki, gdy timer > OCR1A = stan niski , w trybie inverting jest odwrotnie
	// @see https://sites.google.com/site/qeewiki/books/avr-guide/pwm-atmega8
	TCCR1A |= (1 << COM1A1);
	

	// wybieramy tryb pracy Fast PWM / Phase corrected PWM
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	


	// ustawiam prescaler na 8 , tzn. iteracja countera co ka�de 8 cykli proca
	TCCR1B |= (1 << CS11);
	

	//TCCR1B |= (1 << CS10);
	// no prescaling
	


	
	
	while(1)
	{
		
		
	}
}

