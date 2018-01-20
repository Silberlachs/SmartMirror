//#include <SoftwareSerial.h>
#include <Arduino.h>
#include "TFTClass.h"

//https://xkcd.com/1172/
TFTClass *display;
bool upDateFlag = false;

void setup()
{
		Serial.begin(74880);
		display = new TFTClass();
		display->defaultInit();
}

void loop()
{
		if(upDateFlag)
		{
			display->invokeUpdate();
			upDateFlag ^= true;
		}
		delay(10);
}

void serialEvent() {
  while (Serial.available()) {
	  
    String inputString = Serial.readString();

	/*	use serial command codes for program control	*/
	if(inputString.startsWith("#!#"))
	{
		switch(inputString.charAt(3))
		{
			case '0'://raise update flag
				upDateFlag ^= true;
			break;
			case '1'://get listindex
				display->setIndexSize(inputString.substring(4).toInt());
			break;
			default:
				Serial.println("Unknown comCode");
			break;
		}
	}
	
	
  }
}
  
