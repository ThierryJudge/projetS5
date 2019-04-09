#include <mbed.h>
#include <rtos.h>
#include "gant.h"
#include "xbeegant.h"


int main (void) {
	//char test;
	//char swipe;
	char resultats[2];

	osThreadId id = Thread::gettid();

	start_xbee(id);
	init_capteur();
	Thread::signal_wait(0x01);
	while (true) {
		/*test = read_flex();	
		swipe = lire_accel();
		pc.printf("Chiffre lu: %d\r\n", interpret_number(test));
		pc.printf("Signe lu: %d\r\n\n", interpret_sign_number(test));
		*/
		lire_capteurs(resultats);
		if(resultats[1] == 1)
		{
			printf("--------------------------------Swipe Left\r\n");
		}
		else if(resultats[1] == 3)
		{
			printf("--------------------------------Swipe Right\r\n");
		}
		printf("Chiffre lu: %d\r\n", interpret_number(resultats[0]));
		printf("Signe lu: %d\r\n\n", interpret_sign_number(resultats[0]));
		send_data(resultats);
		wait(0.5);
  	}
}
