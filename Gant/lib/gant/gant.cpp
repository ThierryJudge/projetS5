#include "gant.h"



AnalogIn tab_res[5] = { res1, res2, res3, res4, res5 };

char read_flex() {
	char sortie_flex = 0;
		// Lecture des 5 valeurs analogiques des resistances flex Pour la calibration
		//printf("%d-%d-%d-%d-%d\r\n", res1.read_u16(), res2.read_u16(), res3.read_u16(), res4.read_u16(), res5.read_u16());
	
	if(tab_res[POUCE].read_u16()>SEUIL_POUCE){
		sortie_flex =0;
		//pc.printf("pouce plie: %d\n\r", doigts[0]);
	}
	else{
		sortie_flex =1;
		//pc.printf("pouce deplie: %d\n\r", doigts[0]);
	}
	if(tab_res[INDEX].read_u16()>SEUIL_INDEX){
		sortie_flex = sortie_flex << 1;
		//pc.printf("index plie: %d\n\r", doigts[1]);
	}
	else{
		sortie_flex = sortie_flex << 1 | 0x1;
		//pc.printf("index deplie: %d\n\r", doigts[1]);
	}
	if(tab_res[MAJEUR].read_u16()>SEUIL_MAJEUR){
		sortie_flex = sortie_flex << 1;
		//pc.printf("MAJEUR plie: %d\n\r", doigts[2]);
	}
	else{
		sortie_flex = sortie_flex << 1 | 0x1;
		//pc.printf("MAJEUR deplie: %d\n\r", doigts[2]);
	}
	if(tab_res[ANNULAIRE].read_u16()>SEUIL_ANNULAIRE){
		sortie_flex = sortie_flex << 1;
		//pc.printf("ANNULAIRE plie: %d\n\r", doigts[3]);
	}
	else{
		sortie_flex = sortie_flex << 1 | 0x1;
		//pc.printf("ANNULAIRE deplie: %d\n\r", doigts[3]);
	}
	if(tab_res[AURICULAIRE].read_u16()>SEUIL_AURICULAIRE){
		sortie_flex = sortie_flex << 1;
		//pc.printf("AURICULAIRE plie: %d\n\r", doigts[4]);
	}
	else{
		sortie_flex = sortie_flex << 1 | 0x1;
		//pc.printf("AURICULAIRE deplie: %d\n\r", doigts[4]);
	}

	//imprimer les résultats
	/*pc.printf("got_flex_results: %d\r\n", sortie_flex);
	pc.printf("got_flex_results: ");

	for (int i = 0; i < 8; i++) {
      printf("%d", !!((sortie_flex << i) & 0x80));
  }
  printf("\r\n");*/
	return sortie_flex;
}

char interpret_number(char in){
	return chiffres1_5[in];
}
char interpret_sign_number(char in){
	return chiffres_signes[in];
}


int ConvertTwosComplementByteToInteger(uint16_t rawValue)
{
    // If a positive value, return it
    if ((rawValue & 0x800) == 0)
    {
        return rawValue;
    }

    // Otherwise perform the 2's complement math on the value
    return  ((int)(rawValue ^ 0xFFF) + 1)*-1;
}


void init_capteur()
{
	accel = init_accel_t(&i2c);
}

char lire_accel()
{
	char swipe = 0;
	read_accel_t(&accel);
  // printf("%d, %d, %d\r\n", ConvertTwosComplementByteToInteger(accel.x), 
  //                         ConvertTwosComplementByteToInteger(accel.y), 
  //                         ConvertTwosComplementByteToInteger(accel.z));
  
  //printf("%d, %d\r\n", (accel.z & 0x800) >> 11, accel.z & 0x7FF);
  

  //printf("X: %d\r\n", ConvertTwosComplementByteToInteger(accel.x)); 

  //printf("Z: %d\r\n", ConvertTwosComplementByteToInteger(accel.z));
  //printf("%d\r\n", ConvertTwosComplementByteToInteger(accel.z));

  int zval = ConvertTwosComplementByteToInteger(accel.z);
  int xval = ConvertTwosComplementByteToInteger(accel.x);

  //printf("diff: %d\r\n", zval - last_val);
  int diff = zval - last_val;
  if (xval > ACCEL_X_THRESH) //prevent swipes from occuring when the hand is not in swipe position
  {
    if (diff < -ACCEL_THRESH)
    {
      //printf("-------------------------------Swipe Rigth\r\n");
			swipe = 3;
    }
    else if (diff > ACCEL_THRESH)
    {
      //printf("--------------------------------Swipe Left\r\n");
			swipe = 1;
    }
  }

  last_val = zval;
	
	return swipe;

}


void lire_capteurs(char* resultats){
	resultats[0] = read_flex();
	resultats[1] = lire_accel();
}