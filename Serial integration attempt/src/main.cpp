#include "Arduino.h"

#pragma region //all variables
#pragma region //Serial variables

void step(int x, int y);

int led = DD2;
int one;
int ten;
int hundred;
int datastart = 47; //      /
int stepstart = 46; //      .
int xchar = 120;    //      x
int ychar = 121;    //      y
int received = 0;
#pragma endregion

#pragma region      //x variables
int stepperx = DD2; //the step pin of the X axis stepper pulse 1 for a step
int xdir = DD3;     //the direction pin of the X axis stepper set to 1 or 0 for diffirent directions
int xref = 0;       //reference value to compare with to determine wether or not you have to step left or right
int deltax = 0;     //value when refferencing xsteps with xref => this value gets send to the step method
int xsteps = 0;     //Serially received location of the next timeframe in steps
#pragma endregion

#pragma region      //y variables
int steppery = DD4; //the step pin of the Y axis stepper pulse 1 for a step
int ydir = DD5;     //the direction pin of the Y axis stepper set to 1 or 0 for diffirent directions
int yref = 0;       //reference value to compare with to determine wether or not you have to step left or right
int deltay = 0;     //value when refferencing ysteps with yref => this value gets send to the step method
int ysteps = 0;     //Serially received location of the next timeframe in steps

#pragma endregion


#pragma endregion

void setup()
{
  Serial.begin(115200);
  Serial.println("Ready");
  DDRD |= 1 << stepperx;
  DDRD |= 1 << xdir;
  DDRD |= 1 << steppery;
  DDRD |= 1 << ydir;
}

void loop()
{
  if (Serial.available())
  {
    delay(1);
    received = Serial.read();
    #pragma region // reading x and y step values from serial connection
    if (received == datastart)
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
          if (ten == xchar)
          {
            xsteps = (hundred - 48);
            i = 4;
          }
          if (ten == ychar)
          {
            ysteps = (hundred - 48);
            i = 4;
          }
          break;

        case 2:
          one = Serial.read();
          if (one == xchar)
          {
            xsteps = (hundred - 48) * 10 + (ten - 48);
            i = 4;
          }
          if (one == ychar)
          {
            ysteps = (hundred - 48) * 10 + (ten - 48);
            i = 4;
          }
          break;

        case 3:
          if (Serial.read() == xchar)
            xsteps = (hundred - 48) * 100 + (ten - 48) * 10 + one - 48;
          if (Serial.read() == ychar)
            ysteps = (hundred - 48) * 100 + (ten - 48) * 10 + one - 48;

        default:
          break;
        }
      }
      #pragma endregion
    }
    if(received == stepstart)
    {
      step(xsteps,ysteps);
      Serial.write("Next");
    }
  }
}
void step(int x, int y)
{
#pragma region // check positivity of x and y to determine direction
  if (x > 0)
    PORTD |= 1 << xdir;
  else if (x < 0)
  {
    x *= -1;
    PORTD &= ~(1 << xdir);
  }
  if (y > 0)
    PORTD |= 1 << ydir;
  else if (y < 0)
  {
    y *= -1;
    PORTD &= ~(1 << ydir);
  }
#pragma endregion

#pragma region // executing steps
  while (x > 0 || y > 0)
  {
    if (x > 0)
    {
      Serial.println("x ");
      Serial.println(x);
      PORTD |= 1 << stepperx;
      x--;
    }
    if (y > 0)
    {
      Serial.println("y ");
      Serial.println(y);
      PORTD |= 1 << steppery;
      y--;
    }
    delay(50);
    PORTD &= ~(1 << stepperx);
    PORTD &= ~(1 << steppery);
    delay(10);
  }
  #pragma endregion
}