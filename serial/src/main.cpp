#include "Arduino.h"
int led = DD2;
String inputascii = "";
int one;
int ten;
int hundred;
int start = 47;
int number;
int xsteps;
int ysteps;
int xchar = 120;
int ychar = 121;
int xory;
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
      for (int i = 0; i < 4; i++)
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
        case 3:
        xory = Serial.read();
          if (xory == xchar)
            xsteps = (hundred - 48) * 100 + (ten - 48) * 10 + one - 48;
          if (xory == ychar)
            ysteps = (hundred - 48) * 100 + (ten - 48) * 10 + one - 48;
        default:
          break;
        }
      }
    }
    number = (hundred -48)*100 + (ten -48)*10 + one-48;
    if(xsteps == 321 && ysteps == 123)
    {
      PORTD = 1 << led;
      Serial.write('S');
    }

   }
}