#ifndef S5_GANT_H
#define S5_GANT_H

#include "mbed.h"
#include "accel.h"

#define POUCE 4
#define INDEX 3 
#define MAJEUR 2
#define ANNULAIRE 1 
#define AURICULAIRE 0

#define SEUIL_POUCE 40665
#define SEUIL_INDEX 32992
#define SEUIL_MAJEUR 33888
#define SEUIL_ANNULAIRE 43611
#define SEUIL_AURICULAIRE 50332

#define ACCEL_THRESH 1500
#define ACCEL_X_THRESH -500

static accel_t accel;
static I2C i2c(p9, p10);

typedef struct gant_data
{
	char resultats[2];
} gant_data;

static AnalogIn res1(p15);
static AnalogIn res2(p16);
static AnalogIn res3(p17);
static AnalogIn res4(p18);
static AnalogIn res5(p19);

extern AnalogIn tab_res[5];

static int last_val; 

static char chiffres1_5[32] = {0, //00000
							255, //00001
							255, //00010
							255, //00011
							255, //00100
							255, //00101
							255, //00110
							255, //00111
							 1, //01000
							255, //01001
							255, //01010
							255, //01011
							 2, //01100
							255, //01101
							 3, //01110
							 4, //01111
							255, //10000
							255, //10001
							255, //10010
							255, //10011
							255, //10100
							255, //10101
							255, //10110
							255, //10111
							255, //11000
							255, //11001
							255, //11010
							255, //11011
							255, //11100
							255, //11101
							255, //11110
							 5};//11111;

static char chiffres_signes[32] = {0, //00000
							255, //00001
							255, //00010
							255, //00011
							255, //00100
							255, //00101
							255, //00110
							 9, //00111
							 1, //01000
							255, //01001
							255, //01010
							 8, //01011
							 2, //01100
							 7, //01101
							 6, //01110
							 4, //01111
							255, //10000
							255, //10001
							255, //10010
							255, //10011
							255, //10100
							255, //10101
							255, //10110
							255, //10111
							255, //11000
							255, //11001
							255, //11010
							255, //11011
							3, //11100
							255, //11101
							255, //11110
							 5};//11111


char read_flex();

char interpret_number(char in);
char interpret_sign_number(char in);


int ConvertTwosComplementByteToInteger(uint16_t rawValue);


void init_capteur();


char lire_accel();
void lire_capteurs(char* resultats);

#endif