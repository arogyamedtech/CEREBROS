/*
   OpenNIRS driver baseline firmware
   Author: Sandeepan Sengupta (mail@sandeepan.info)
   Version 0.1.0
   Released under CC-BY-ND 4.0
*/

#define Marker '#'

//#define _dataViewer_
//#define _Simulate_  //To simulate OpenNIRS SensorBoard Activity

//#define CH4


/*The following configurations are optimized STM32F103C based board eg. BluePill*/
#define NIR PA0

#define CH0 PA1
#define CH1 PA2
#define TRG PA3
#define RST PA4

//#define timeOut 5 //See 'rset()' in 'functions'

#define channelDelay 320  //Ref. Page 49, 10^6/(3.125)

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    ;
  }

#ifndef _Simulate_
  pinMode(NIR, INPUT_ANALOG);
#endif

  pinMode(CH0, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(TRG, OUTPUT);
  pinMode(RST, OUTPUT);
}

uint8_t   reference   = NULL; //To be accessed by swCH()
uint16_t  counter     = NULL;
uint32_t  timeStamp   = NULL;

#ifdef Marker
boolean initialize  = false;
#endif

uint16_t  data[8] = {};

uint32_t  interval  = NULL;
uint32_t  interval_ms  = NULL;
uint32_t  interval_us  = NULL;

void loop()
{

#ifdef Marker
  if (!initialize)
  {
    while (Serial.available() > NULL)
    {
      if (Serial.read() == Marker)
      {
        initialize = true;
        Serial.write("~\n");
      }
    }
  }
  else if (initialize)
#endif

  {
    for (uint8_t i = NULL; i < 8; i++)
    {
      swCH();
      trig(true);
      data[i] = analogRead(NIR);
      delayMicroseconds(channelDelay);
      i++;
      data[i] = analogRead(NIR);
      trig(false);
      //rset(); //Same as trig(false)
      timeKeeper();
    }
    serialPrinter();
  }
}
