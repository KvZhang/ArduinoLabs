#include "Arduino.h"
#include "ColorSensorGY33.h"
//The setup function is called once at startup of the sketch

/*******************************
VCC->VCC
CT ->SCL
DR ->SDA
GND->GND
/******************************/
ColorSensorGY33 myColor;
void setup()
{
// Add your initialization code here
	uint8_t temp=0;
	myColor.init();//init IIC
	Serial.begin(9600);
	Serial.print("calibration? Y/N");//key 'y' or 'Y' to calibrate white balance, other key to skip 
	while(!Serial.available());
	temp=Serial.read();
	if(temp=='Y'||temp=='y')
	{
		myColor.calibration();
	}
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	myColor.getColor();
	Serial.print("The color is:");
	switch(myColor.color)
	{
	case SENSED_COLOR_BLACK:
		Serial.println("black");
		break;
	case SENSED_COLOR_BLUE:
		Serial.println("blue");
		break;
	case SENSED_COLOR_GREEN:
		Serial.println("green");
		break;
	case SENSED_COLOR_INDIGO:
		Serial.println("indigo");
		break;
	case SENSED_COLOR_PINK:
		Serial.println("pink");
		break;
	case SENSED_COLOR_RED:
		Serial.println("red");
		break;
	case SENSED_COLOR_WHITE:
		Serial.println("white");
		break;
	case SENSED_COLOR_YELLOW:
		Serial.println("yellow");
		break;
	default:
		Serial.println("unknown");
		break;
	}
	myColor.color=0;
	myColor.getRGB();
	Serial.print("R:");
	Serial.print(myColor.RGB.Red);
	Serial.print("G:");
	Serial.print(myColor.RGB.Green);
	Serial.print("B:");
	Serial.println(myColor.RGB.Blue);
	delay(1000);
}
