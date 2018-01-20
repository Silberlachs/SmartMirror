#ifndef	TFTClass_H
#define TFTCLASS_H

/* required includes for tft screen, Arduino 1.8.4 																	*/
#include <Arduino.h>
#include <Adafruit_GFX.h>			//1.2.2
#include <Adafruit_ILI9341.h>		//1.0.11
#include <SPI.h>					//default 1.0

/*	definations for arduino nano pinout,generic constructor															*/
#define RESET				8
#define DC					9
#define CS					10
#define MOSI				11
#define MISO				12
#define SCK					13

/* constants for rotation values (untested)																			*/
#define	VERTICAL_UP			0
#define	VERTICAL_DOWN		3
#define HORIZONTAL_UP		1	//default one
#define HORIZONTAL_DOWN		4


class TFTClass{
	public:
			TFTClass::TFTClass();
			TFTClass::TFTClass(int reset,int dc,int cd,int mosi,int miso,int sck);/*constructor for different boards*/
			virtual TFTClass::~TFTClass();
			int TFTClass::defaultInit();										//assume some values
			void TFTClass::setRotation(int r = HORIZONTAL_UP);
			void TFTClass::swapTextWrap();
			void TFTClass::clearScreen();										
			//TFTClass::loadFont(const GFXfont *f = NULL);						//use fixed font for developing
			void TFTClass::printText(String theText,int x=0,int y = 0);			//for custom font set line = 9
			void TFTClass::setTextColor(short txtCol = 0x0F00);					//default = green?
			void TFTClass::setBackgroundColor(short bgc = 0x0000);				//maxvalue 0xFFFF >> white
			void TFTClass::setBorderColor(short border = 0xF000);
			void TFTClass::setTextSize(int size=1);	
			void TFTClass::setIndexSize(int indexSize);
			void TFTClass::invokeUpdate();										//esp has news to update to us
		
	private:
			void TFTClass::drawUI(String title);
			void TFTClass::drawSymbol(int type,int x,int y,int rot=0);			//rotation ??
			void TFTClass::clearText(void);	
			
			//instance variables
			char* _lineBuffer[13];
			int _lineCounter;
			int _listIndex;
			short _backgroundColor;
			short _textColor;
			short _borderColor;
			bool _textWrap;
			
			/*		debug stuff		*/
			void TFTClass::fillChar();
			void TFTClass::screenAdjust();

};
#endif
