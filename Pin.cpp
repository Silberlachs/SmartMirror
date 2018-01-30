#include "Pin.h"

int pin_;
int mode_;

// konstruktor
Pin::Pin(int p, int m) 
{
  pin_ = p;
  mode_ = m;
  pinMode(pin_, mode_);
}

// destruktor
Pin::~Pin(void) 
{}

// wert v auf pin schreiben
void Pin::write(int v) 
{
  value_ = v;
  digitalWrite(pin_, value_);
}

int Pin::getState()
{
  return value_;
}

