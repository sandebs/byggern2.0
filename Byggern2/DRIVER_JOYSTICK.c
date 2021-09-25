#include "DRIVER_ADC.h"
#include "DRIVER_JOYSTICK.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "util.h"


volatile uint8_t x_offset;
volatile uint8_t y_offset;

void joystick_calibrate(){
	int n=10,arrx[n],arry[n];
	for(int i = 0;i < n;i++) {
		arrx[i]=adc_read(1);
		arry[i]=adc_read(0);
	}
	
	x_offset = util_median(arrx,n);
	y_offset = util_median(arry,n);
}

joystick_position joystick_getPosition(void){
	joystick_position position;
	uint8_t x = adc_read(1);
	uint8_t y = adc_read(0);

	if(x > x_offset){
			position.x_pos = 100*(x-x_offset)/(0xFF - x_offset);
	}
	else if (x < x_offset){
		position.x_pos = 100*(x-x_offset)/(x_offset - 0);
	}
	else {
		position.x_pos = 0;
	}

	if(y > y_offset){
		position.y_pos = 100*(y-y_offset)/(0xFF - y_offset);
	}
	else if (y < y_offset){
		position.y_pos = 100*(y-y_offset)/(y_offset - 0);
	}
	else {
		position.y_pos = 0;
	}
	
	return position;
}

joystick_position joystick_getDirection(void){
	//We havn't tested this function, since we haven't defined a way to print the struct. 
	joystick_position position;

	position = joystick_getDirection();
	
	if(position.x_pos < -50){
		position.direction = "LEFT";
	}
	else if(position.x_pos > 50){
		position.direction = "Right";	
	}

	if(position.y_pos < -50){
		position.direction = "DOWN";
	}
	else if(position.y_pos > 50){
		position.direction = "UP";
	}
	
	if(position.x_pos == 0 && position.y_pos == 0){
		position.direction = "NEUTRAL";
	}
	
	return position;
}