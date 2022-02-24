#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void){
	int SW = (PORTD >> 8) & 0xf; // get four LSB

	return SW;
}

int getbtns(void){
	int BTN = (PORTD >> 5) & 0x7; // get three LSB

	return BTN;
}