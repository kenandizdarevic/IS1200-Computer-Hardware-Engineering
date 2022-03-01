#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void){
	int SW = (PORTD >> 8) & 0xf; // get four LSB

	return SW;
}

int getbtn1(void){
	int button1 = (PORTF & 0x2);
	
	return button1;
}

int getbtns(void){
	int BTN = (PORTD >> 5) & 0x7; // get three LSB

	return BTN;
}
