#ifndef _PIN_H    //make sure only one token makes it into the current page
#define _PIN_H
#include <Arduino.h>

class Pin {

// oeffentlich zugreifbare memberfunktionen
public: 
  Pin(int, int);                        // konstruktor normal
  virtual ~Pin(void);                   // destruktor

  int getState();           
  void write(int);                      // wert auf pin schreiben

  
// zugriff gesperrt, attribute fuer abgeleitete klassen zugreifbar
protected:
  int pin_;                             // pin nummer
  int mode_;                            // mode input oder output
  int value_;                           // value low oder high
};

#endif
