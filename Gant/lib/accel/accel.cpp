#include "mbed.h"
#include "accel.h"


// Adresse I2C de l'acc�l�rateur
static const int MMA8452Q_ADDR = 0x1D << 1;

// Adresse du registre de contr�le
static const char MMA8452Q_CTRL_REG1 		= 0x2A;

// Valeur du registre de contr�le pour changer l'�tat de l'acc�l�rom�tre � STANDBY
static const char CTRL_REG1_DEFAULT			= 0x00;
// Activer l'acc�l�rom�tre
static const char CTRL_REG1_ACTIVE 			= 0x01;
// Activer la lecture rapide de l'acc�l�rom�tre
static const char CTRL_REG1_FREAD 				= 0x02;

// Adresse des registre de mesure des MSB de X, Y, et Z 
static const char MMA8452Q_REG_X = 0x01;
static const char MMA8452Q_REG_Y = 0x03;
static const char MMA8452Q_REG_Z = 0x05;

/**
 *	Initialisation des registres
 */
accel_t init_accel_t(I2C *i2c) {

	accel_t accel;
	
	accel.i2c = i2c;

	accel.x = 0;
	accel.y = 0;
	accel.z = 0;
	
	// On doit changer le mode � STANDBY pour changer le registre FREAD
	// (Data Sheet: Technical Data, Rev 4.1, 08/2011)
	char action[2] = {0, 0};
	
	action[0] = MMA8452Q_CTRL_REG1;
	action[1] = CTRL_REG1_DEFAULT;
	accel.i2c->write(MMA8452Q_ADDR, action, 2);
	
	action[0] = MMA8452Q_CTRL_REG1;
	action[1] = CTRL_REG1_ACTIVE;
	accel.i2c->write(MMA8452Q_ADDR, action, 2);
	
	return accel;
}

/**
 *	Permet la lecture du registre de contr�le
 */
void readCtrlReg1(accel_t *accel) {
	char temp[1];
	
	accel->i2c->write(MMA8452Q_ADDR, &MMA8452Q_CTRL_REG1, 1, true);
	accel->i2c->read(MMA8452Q_ADDR, temp, 1);
	printf("CTRL_PRO1: %d\r\n", temp[0]);
}

/**
 *	Lecture des registres x, y et z
 */
void read_accel_t(accel_t *accel) {
	char temp[6] = {0, 0, 0, 0, 0, 0};
	
	accel->i2c->write(MMA8452Q_ADDR, &MMA8452Q_REG_X, 1, true);
	accel->i2c->read(MMA8452Q_ADDR, temp, 6);

	accel->x = (temp[0] << 4) | (temp[1] >> 4);
	accel->y = (temp[2] << 4) | (temp[3] >> 4);
	accel->z = (temp[4] << 4) | (temp[5] >> 4);
}
