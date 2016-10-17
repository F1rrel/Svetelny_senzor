void initMotor()
{
    // init pins
    pinMode(stp, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(MS0, OUTPUT);
    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);
    pinMode(SLEEP, OUTPUT);
    pinMode(RESET, OUTPUT);

    stepper.setMaxSpeed(200*mstep);
    stepper.setAcceleration(200*mstep);
    stepper.setCurrentPosition(0); 

    micro32();
}

// Calculate motor steps and move
void moveMotor(int Peak)
{ 
    resetEDPins();
    micro32();
    delay(500);
    
    long steps = ((127L - Peak)*mstep)*pstep;
    if (abs(steps) > 100000) {
      while (1) {
        digitalWrite(redPin, !digitalRead(redPin));
        delay(500);
      }
    }
    stepper.move(steps);
}

//Reset Easy Driver pins to default states
void resetEDPins()
{
    digitalWrite(stp, LOW);
    digitalWrite(dir, LOW);
    digitalWrite(MS0, LOW);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    digitalWrite(RESET, HIGH);
    digitalWrite(SLEEP, HIGH);
}      

void stopMotor() {
    digitalWrite(stp, LOW);
    digitalWrite(dir, LOW);
    digitalWrite(MS0, LOW);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    digitalWrite(RESET, LOW);
    digitalWrite(SLEEP, LOW);
}

// Microstepping
void micro16()
{
    // 1/16 microstepping
    digitalWrite(MS0, LOW); 
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, HIGH);
}

// Microstepping
void micro32()
{
    // 1/32 microstepping
    digitalWrite(MS0, LOW); 
    digitalWrite(MS1, HIGH);
    digitalWrite(MS2, HIGH);
}

