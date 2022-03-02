#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void){
	int SW = (PORTD >> 8) & 0xf; // get four LSB

	return SW;
}

int getbtns(void){
	int BTN = ((PORTD >> 5) & 0x7); 

	return BTN;
}

int getbtn1(void){
	int btn1 = (PORTF & 0x2);

	return btn1;
}