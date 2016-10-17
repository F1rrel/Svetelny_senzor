word Sensor( int* Peak, byte pin1, byte pin2, boolean type )
{
  word Data[256];
  word PeakP;
  int i = 0;

  if (type)
  {
    while (i < 10)
    {
      readSensor( Data, pin1, pin2 );    
      if ((PeakP = calcPeak( Data )) == 1000)
      {
        *Peak = PeakP;
        return 1000;
      }
      else if (abs(*Peak - PeakP) < 3)
      {
        i++;
      }
      else
      {
        i = 0;
        *Peak = PeakP;
      }
      delay(100); // delay between values
    }
  }
  else
  {
    readSensor( Data, pin1, pin2 );
    if ((*Peak = calcPeak( Data )) == 1000)
    {
        return 1000;
    }
  }
  return 0;
}

void calcAngle(float* Angle, int* Peak1, int* Peak2)
{
    float pixel = 0.0635;
    float distance = 40.8;
    float AngleRad;
    
    AngleRad = atan2((pixel * (*Peak1-*Peak2)), distance);
    *Angle = (AngleRad*4068)/71;
}

void readSensor( word* Data, byte pin1, byte pin2 )
{

  // Next, stop the ongoing integration of light quanta from each photodiode by clocking in a
  // SI pulse:
  digitalWrite(SIpin, HIGH);
  ClockPulse();
  digitalWrite(SIpin, LOW);

  for (int i = 0; i < 260; i++)
  {
    ClockPulse();
  }
  delay(1);

  // Stop the ongoing integration of light quanta from each photodiode by clocking in a SI pulse
  // into the sensors register:
  digitalWrite(SIpin, HIGH);
  ClockPulse();
  digitalWrite(SIpin, LOW);

  // Next, read all 256 pixels in parallell. Store the result in the array. Each clock pulse
  // causes a new pixel to expose its value on the two outputs:
  for (int i = 0; i < 128; i++)
  {
    delayMicroseconds(20);// <-- We add a delay to stabilize the AO output from the sensor
    Data[i] = analogRead(pin1);
    Data[i + 128] = analogRead(pin2);
    ClockPulse();
  }

  
}

word calcPeak( word* Data )
{
  word MaxData[256];
  word Max;
  word Min;
  int Peak;
  word Length;
  word n;

  // Goes trough the arrray and finds maximums
  n = 0;
  Max = 0;

  for (int i = 0; i < 256; i++)
  {
    if (Data[i] > Max)
    {
      MaxData[0] = i;
      Max = Data[i];
      n = 0;
    }
    else if (Data[i] == Max)
    {
      n++;
      MaxData[n] = i;
    }
  }
  if (n+1 > errorAmbient)   // Detection of ambient light
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);
    return 1000;
  }
  else if ((maximum(Data, 256) - minimum(Data, 256)) < errorLaser)
  {
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, LOW);    
    return 1000;
  }
  else
  {
    // set the LEDs off
    digitalWrite(redPin, LOW);    
    digitalWrite(yellowPin, LOW);
  }

  Length = 0;
  Min = MaxData[0];
  if (n == 0)
  {
    return MaxData[0];
  }
  else
  {
    for (int i = 0; i < n; i++) 
    {
      if ((((MaxData[i + 1] - MaxData[i]) > 5) || (i == n - 1)) && ((MaxData[i] - Min) > Length))
      {
        Length = MaxData[i] - Min;
        Peak = (MaxData[i] + Min) / 2;
        Min = MaxData[i + 1];
      }
      else if ((i == n - 1) && ((MaxData[i] - Min) > Length))
      {
        Length = MaxData[n] - Min;
        Peak = (MaxData[n] + Min) / 2;
      }
    }
  }
  return Peak;
}

void initSensor()
{
  // Initialize two Arduino pins as digital output:
  pinMode(CLKpin, OUTPUT);
  pinMode(SIpin, OUTPUT);

  // To set up the ADC, first remove bits set by Arduino library, then choose
  // a prescaler: PS_16, PS_32, PS_64 or PS_128:
  ADCSRA &= ~PS_128;
  ADCSRA |= PS_32; // <-- Using PS_32 makes a single ADC conversion take ~30 us

  // Next, assert default setting:
  analogReference(DEFAULT);

  // Set IO pins low:
  digitalWrite(CLKpin, LOW);
  digitalWrite(SIpin, LOW);


  // Clock out any existing SI pulse through the ccd register:
  for (int i = 0; i < 260; i++)
  {
    ClockPulse();
  }
}

word minimum(word* Data, int size)
{
    word min = Data[0];
    for (int i = 0; i < size; i++)
  {
    if (Data[i] < min) min = Data[i];
  }
  return min;   
}

word maximum(word* Data, int size)
{
    word max = Data[0];
    for (int i = 0; i < size; i++)
  {
    if (Data[i] > max) max = Data[i];
  }
  return max;   
}

// This function generates an outgoing clock pulse from the Arduino digital pin 'CLKpin'. This clock
// pulse is fed into pin 3 of the linear sensor:
void ClockPulse()
{
  delayMicroseconds(1);
  digitalWrite(CLKpin, HIGH);
  digitalWrite(CLKpin, LOW);
}
