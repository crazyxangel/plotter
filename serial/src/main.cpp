#include "Arduino.h"
int led = DD2;
String inputascii = "";
int one;
int ten;
int hundred;
int start = 47;
int number;
void setup()
{
  Serial.begin(115200);
  Serial.println("Ready");
  DDRD = 1 << led;

}

void loop()
{
  if (Serial.available())
  {
    if(Serial.read() == start)
    {
      for (int i = 0; i < 3; i++)
      {
        delay(1);
        switch (i)
        {
        case 0:
          hundred = Serial.read();
          break;
        case 1:
          ten = Serial.read();
          break;
        case 2:
          one = Serial.read();
          break;
        
        default:
          break;
        }
      }
    }
    number = (hundred -48)*100 + (ten -48)*10 + one-48;
    if(number == 123)
    {
      PORTD = 1 << led;
    }
    if(number == 321)
    {
      PORTD = 0;
    }
   }
}