* Created: 29/09/2021 22:47:51
* Author : will
*/

#include <avr/io.h>
#include <stdio.h>

void atraso(){

TCNT1 = 3036;				   //Para 4 Hz
// assim: 65536 - 62500 = 3036
while ((TIFR1 & (1<<0)) == 0); // Aguarda flag de estouro
TIFR1 = (1<<0);				   //Limpa flag de estouro

}

int main(void)
{
int i = 0;			 // valor inicial
int hora;
int min;

TCCR1A = 0;          // Modo Normal
TCCR1B = 0x5;		 // Clock 1024
TCNT1 = 3036;		 //Para 4 Hz
// assim: 65536 - 62500 = 3036
/* Replace with your application code */
while (1)
{

atraso();
i++;

if(i >= 21600){
i=0;
}

hora = i/900;
min = i/(15*(hora+1));



}
}/*
 * GccApplication1.c
 *
 * Created: 01/10/2021 09:19:47
 * Author : luiz-
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

