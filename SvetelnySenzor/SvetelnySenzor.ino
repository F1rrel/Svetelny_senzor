
#include <AccelStepper.h>
#include <EEPROM.h>

//-----------------------
// Program variables
//-----------------------

int step = 0;   // case variable
#define redPin 13
#define yellowPin 12

//-----------------------
// Sensor variables
//-----------------------

#define AddressErrorAmbient 0   // Ambient light sensitivity
#define AddressErrorLaser 1    // Laser detection sensitivity

byte errorAmbient;
word errorLaser;

#define CLKpin 9    // <-- Arduino pin delivering the clock pulses to pin 3 (CLK) of the TSL1402R
#define SIpin 10     // <-- Arduino pin delivering the SI (serial-input) pulse to pin 2 of the TSL1402R
#define AOpin1 3    // <-- Arduino pin connected to pin 4 (analog output 3)of the TSL1402R
#define AOpin2 4    // <-- Arduino pin connected to pin 8 (analog output 4)of the TSL1402R
#define AOpin3 1    // <-- Arduino pin connected to pin 4 (analog output 1)of the TSL1402R
#define AOpin4 2    // <-- Arduino pin connected to pin 8 (analog output 2)of the TSL1402R

// Define various ADC prescaler:
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

int Peak1;
int Peak2;
float Angle;

//-----------------------
// Motor variables
//-----------------------

#define dir 2
#define stp 3
#define SLEEP 4
#define RESET 5
#define MS0 6
#define MS1 7
#define MS2 8

AccelStepper stepper(AccelStepper::DRIVER, stp, dir); // step/dir control
#define mstep 32  // microstep resolution
#define pstep 10.08    //  steps per pixel

//-----------------------
// Serial variables
//-----------------------

#define SDATABUFFERSIZE 20
char sdataBuffer[SDATABUFFERSIZE + 1]; //Add 1 for NULL terminator
byte sdataBufferIndex = 0;
boolean sstoreString = false; // flag to put the data in our buffer
word serialRead;

//------------------------------------------------------------------------------------------------

//-----------------------
// Setup
//-----------------------

void setup()
{
  Serial.begin(115200);
  
  initSensor();
  initMotor();

  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);

  EEPROM.get(AddressErrorAmbient, errorAmbient);
  EEPROM.get(AddressErrorLaser, errorLaser);
}

//-----------------------
// Loop
//-----------------------

void loop()
{
  switch (step)
  {
    case 0:
      {
       
        if (Sensor( &Peak1, AOpin1, AOpin2, true ) == 1000)
        {
          delay(2000);
        }
        else if (Peak1 < 130 && Peak1 > 124)
        {
          step = 31;
        }
        else
        {
          step = 20;
        }
        Serial.print("Peak: ");
        Serial.println(Peak1);

        while (Serial.available() > 0)
        {
          serialRead = readSerial(Serial.read());
          if (serialRead == 10) {
            Serial.println("Motor move");
            step = 21;
            break;
          }
          else if (serialRead == 20) {
            EEPROM.get(AddressErrorLaser, errorLaser);
          }
          else if (serialRead == 30) {
            EEPROM.get(AddressErrorAmbient, errorAmbient);
          }
          
        }
        
        break;
      }
    case 20:
      {
        moveMotor(Peak1);
        step = 21;
        break;
      }
    case 21:
      {
        if (stepper.distanceToGo() == 0)
        {
          stopMotor();
          step = 30;
          break;
        }
        stepper.run();
        break;
      }
    case 30:
      {
        if (Sensor( &Peak1, AOpin1, AOpin2, true ) == 1000)
        {
          step = 0;
        }
        else if (Peak1 >= 130 || Peak1 <= 124)
        {
          step = 20;
        }
        else
        {
          step = 31;
        }
        break;
      }
    case 31:
      {
        if (Sensor( &Peak2, AOpin3, AOpin4, false ) == 1000)
        {
          step = 0;
        }
        else
        {
          calcAngle( &Angle, &Peak1, &Peak2 );
          Serial.print("Angle: ");
          Serial.println(Angle);
          step = 0;
        }
        delay(2000);
        break;        
      }
  }
}


























