int readSerial(char sincomingbyte)
{

  char startChar = '<';
  char endChar = '\r';
  String string;

  if (sincomingbyte == startChar)
  {
    sdataBufferIndex = 0;  //initialize the dataBufferIndex
    sstoreString = true;
  }
  if (sstoreString)
  {
    //check the serial buffer, bail if buffer overrun
    if (sdataBufferIndex == SDATABUFFERSIZE)
    {
      // index is pointing to an array element outside our buffer. re init the buffer and bail
      sdataBufferIndex = 0;
    }
    if (sincomingbyte == endChar) // got a command line, parse it
    {
      Serial.println("ok"); //acknowlege the command

      if (String(sdataBuffer).substring(1, 6) == "LASER") //
      {
        string = String(sdataBuffer).substring(8, 13);
        EEPROM.put(AddressErrorLaser, constrain(word(string.toInt()),200,1000));

        sstoreString = false;
        return 20;
      }
      else if (String(sdataBuffer).substring(1, 4) == "AMB") //
      {
        string = String(sdataBuffer).substring(6, 11);
        EEPROM.put(AddressErrorAmbient, constrain(byte(string.toInt()),1,250));

        sstoreString = false;
        return 30;
      }
      else if (String(sdataBuffer).substring(1, 6) == "MOTOR") //
      {
        resetEDPins();
        micro32();
        delay(500);
        string = String(sdataBuffer).substring(8, 13);
        stepper.move(string.toInt()*mstep);

        sstoreString = false;
        return 10;
      }
      else
      {
        Serial.println("Not existing command");
      }
      sstoreString = false;
    }
    else
    {
      sdataBuffer[sdataBufferIndex++] = sincomingbyte;
      sdataBuffer[sdataBufferIndex] = 0; //null terminate the C string
    }
  }
  return 0;
}
