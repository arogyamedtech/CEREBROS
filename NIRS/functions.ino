/*
   OpenNIRS driver baseline firmware functions
   Author: Sandeepan Sengupta (mail@sandeepan.info)
   Version 0.1.0
   Released under CC-BY-ND 4.0
*/

void trig(bool state)
{
  digitalWrite(TRG, state);
  digitalWrite(RST, !state);

  /*
     Timing inntervals are set as recomended at openNIRS project documentation
     Please refer to page 55
     http://www.opennirs.org/docu/openNIRS_full_documentation_v1.pdf
  */
  if (state)
  {
    delay(4);
  }
  else
  {
    delay(1);
  }
}

/*
void rset()
{
  digitalWrite(TRG, LOW);
  digitalWrite(RST, HIGH);

#ifdef timeOut
  delay(timeOut);
#endif
}
*/

void swCH()
{
  if ((reference % 4) == 0)
  {
    digitalWrite(CH0, LOW);
    digitalWrite(CH1, LOW);
  }
  else if ((reference % 4) == 1)
  {
    digitalWrite(CH0, LOW);
    digitalWrite(CH1, HIGH);
  }
  else if ((reference % 4) == 2)
  {
    digitalWrite(CH0, HIGH);
    digitalWrite(CH1, LOW);
  }
  else if ((reference % 4) == 3)
  {
    digitalWrite(CH0, HIGH);
    digitalWrite(CH1, HIGH);
  }
  reference++;
}

void timeKeeper()
{
  uint32_t  instance  = micros();
  interval  = instance - timeStamp;
  timeStamp = instance;

  interval_us = interval % 1000;  //Fetching us value
  interval_ms = (interval - interval_us) / 1000;  //1ms is 1000us
}

void dataSet()
{
  for (uint8_t i = NULL; i < 8; i++)
  {
    if (i < 6)
    {
      Serial.print(data[i]);
    }
    if (i >= 6)
    {
#ifdef CH4
      Serial.println(data[i]);
#else
      Serial.println();
#endif
    }
    else
    {
      Serial.print('\t');
    }
  }
  counter++;
}

void serialPrinter()
{
#ifndef _dataViewer_
  Serial.print(counter);
  Serial.print('\t');
  if (counter == NULL)
  {
    Serial.print(counter);
    Serial.print('\t');
    //Serial.print(counter);
  }
  else
  {
    Serial.print(interval);
    Serial.print('\t');
    /*
    Serial.print(interval_ms);
    Serial.print('\t');
    Serial.print(interval_us);
    */
  }
  Serial.print('\t');
#endif

  dataSet();
}
