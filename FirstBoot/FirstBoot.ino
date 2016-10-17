// Initializes variables stored in EEPROM

#include <EEPROM.h>

#define AddressErrorAmbient 0   // Ambient light sensitivity
#define AddressErrorLaser 1    // Laser detection sensitivity

byte errorAmbient = 20;
word errorLaser = 800;

void setup() {
  // put your setup code here, to run once:

  EEPROM.put(AddressErrorAmbient, errorAmbient);
  EEPROM.put(AddressErrorLaser, errorLaser);

}

void loop() {
  // put your main code here, to run repeatedly:

}
