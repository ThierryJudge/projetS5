/**
 *	Gestion de l'acc�l�rom�tre MMA8452Q
 *
 *	@autheurs 	Thierry Judge, Andr� Jacques
 *	@date				2019-02-07
 *  @modifier 	2019-02-07
 */

#ifndef S5_ACCEL_H
#define S5_ACCEL_H

#include "mbed.h"


struct accel_t {
		// Object I2C de la librairie mbed
		I2C* i2c;
	
		// Valeur obetenue en x, y et z
		uint16_t x, y, z;
	
};

/**
 *	Initialisation des registres
 */
accel_t init_accel_t(I2C *i2c);

/**
 *	Permet la lecture du registre de contr�le
 */
void readCtrlReg1(accel_t *accel);

/**
 *	Lecture des registres x, y et z
 */
void read_accel_t(accel_t *accel);

#endif
