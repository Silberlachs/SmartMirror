#include "TFTClass.h"
#include <Fonts/FreeMono9pt7b.h>//change custom font HERE(and in constructor		
								//note only a monospaced font will ensure fixed line width
								
#define LOGO					//comment out for no-Splash [saves flashmemory,fast bootup]
#ifdef LOGO
#include "parrot.c"							
#endif

#define DEBUG						//comment out for live use 	< ---- DEBUG SYMBOL
#ifdef DEBUG
#define Debug( x ) Serial.println(x);
#else
#define Debug( x ) 
#endif

//class variables
Adafruit_ILI9341 *screen = NULL;

TFTClass::TFTClass()
{
	screen = new Adafruit_ILI9341(CS, DC, MOSI, SCK, RESET, MISO);
	_lineCounter ^= _lineCounter;
	Debug("Constructor called\nscreenobject created!");

}
TFTClass::TFTClass(int reset,int dc,int cs,int mosi,int miso,int sck)
{
	screen = new Adafruit_ILI9341(cs, dc, mosi, sck, reset, miso);
	_lineCounter ^= _lineCounter;
}
TFTClass::~TFTClass()
{
	delete screen;

	Debug("Object destroyed");
}

/* 	assume some initialization to make use easier	+ faster								*/
int TFTClass::defaultInit()
{
	screen->begin();
	screen->setFont(&FreeMono9pt7b);		//change custom font HERE
	
/*	speed up things >> default Init 														*/
	screen->setRotation(1);					
	screen->setTextWrap(_textWrap);
	
	_textWrap = true;
	_backgroundColor = 0x0000;
	_textColor = 0x0F00;
	_borderColor = 0xF000;
	screen->fillScreen(_backgroundColor);
	
	#ifdef LOGO		//show a splash with a loading animation to give esp time to boot		*/
	screen->drawBitmap(10, 5,parrotImage, width, height,0xF000 );
	delay(2000);				
	screen->fillCircle(160,130,90,_backgroundColor);
	this->printText("LOADING",110,130);
	delay(500);
	this->printText(".",190,130);
	delay(500);
	this->printText(".",195,130);
	delay(500);
	this->printText(".",200,130);
	delay(500);
	this->printText(".",205,130);
	delay(500);
	#else	Debug("Skipping logo for fastboot");
	#endif
	
	#ifdef DEBUG
		this->fillChar();	
		//this->screenAdjust();
	#endif
	this->drawUI("MEINE NOTIZEN");
	this->clearScreen();
	Debug("TFT initialised");
	Serial.flush();
}

/* 	the next 3 functions are mostly for customisation										*/
void TFTClass::setTextSize(int newSize)
{
	screen->setTextSize(newSize);
}

void TFTClass::setRotation(int rotationCode)
{
	if(rotationCode < 1 && rotationCode > 4)
	{
		Debug("Rotation Values range from 1 to 4!\n");
		return;
		
	}
	screen->setRotation(rotationCode);
}

void TFTClass::swapTextWrap()
{
	screen->setTextWrap(_textWrap ^= true);
}

/*	fill the screen with a single color														*/
void TFTClass::clearScreen()
{
	screen->fillRect(4,26,312,210,_backgroundColor);
}

void TFTClass::setBackgroundColor(short bgc)
{
	_backgroundColor = bgc;
}

void TFTClass::setBorderColor(short border)
{
	_borderColor = border;
}

/* 	give the user a headline to orientate 													*/
void TFTClass::drawUI(String titleText)
{
	screen->setTextSize(1);
	screen->fillRect(0,0,320,25,_borderColor);
	screen->fillRect(0,0,3,240,_borderColor);
	screen->fillRect(317,0,3,240,_borderColor);
	screen->fillRect(0,237,320,3,_borderColor);
	
	//inline box
	screen->fillRect(3,25,314,1,_borderColor>>0xF);
	screen->fillRect(3,26,1,211,_borderColor >>0xF);
	screen->fillRect(316,26,1,211,_borderColor >>0xF);
	screen->fillRect(3,236,314,1,_borderColor >>0xF);
	
	
	screen->setCursor(160 - titleText.length()*5,19);		// 5 = lettersize / 2
	screen->setTextColor(0x0000);
	screen->println(titleText);
	
	screen->setCursor(160 - titleText.length()*5,20);		// writing BOLD
	screen->println(titleText);
	
	//give back color
	screen->setTextColor(_textColor);		
}

/*	work in progress 	*/
void TFTClass::printText(String theText,int x, int y)
{
	screen->setCursor(x,y);
	screen->setTextColor(_textColor);
	screen->println(theText);
}

//test character printing
void TFTClass::fillChar()
{
	Debug("Filling screen testwise");
	int cursor = 30;
	screen->setTextColor(0x0F00);
	for(int i=0;i<13;i++)
	{
		screen->setCursor(22,((i+1)*15) + cursor);
		screen->print("GGGGGGGGGGGGGGGGGGGGGGGGG");
	}
}

//raster coordinates for fine tuning ((todo: add numbers))
void TFTClass::screenAdjust()
{
	for(int c=0;c<320;c+=5)
	{
		//use for side raster
		//screen->fillRect(0,c,5 + c%10,1,0x000F); 
		//screen->fillRect(c,0,1,5 + (c%10),0x000F);
		
		//use for full screen raster, note 40 pixel offset between delimeters
		if(c % 40 == 0) 
		{
			screen->fillRect(0,c,320,1,0xFF00);
			screen->fillRect(c,0,1,240,0xFF00);
		}
		else
		{
			screen->fillRect(0,c,320,1,0x00F0); 
			screen->fillRect(c,0,1,240,0x00F0);
		}
		
	}
	Debug("finding screen center with magic numbers");
	screen->fillRect(160,110,1,20,0xF000);
	screen->fillRect(150,120,20,1,0xF000);
}


/*	functions to handle notes, string magic												    	*/
void TFTClass::setIndexSize(int index)
{
	_listIndex = index;
	Debug("Liste hat " + String(index) + " Eintraege");
}

void TFTClass::invokeUpdate()
{
	//check for updates from esp
}
