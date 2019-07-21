                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   #include <Arduino.h>

#pragma region //all variables
#pragma region //x variables
int stepperx = DD2;   //the step pin of the X axis stepper pulse 1 for a step
int xdir = DD3;       //the direction pin of the X axis stepper set to 1 or 0 for diffirent directions
int xref = 0;         //reference value to compare with to determine wether or not you have to step left or right
int deltax = 0;       //value when refferncing xsteps with xref => this value gets send to the step method
#pragma endregion

#pragma region //y variables
int steppery = DD4;   //the step pin of the Y axis stepper pulse 1 for a step
int ydir = DD5;       //the direction pin of the Y axis stepper set to 1 or 0 for diffirent directions
int yref = 0;         //reference value to compare with to determine wether or not you have to step left or right
int deltay = 0;       //value when refferncing xsteps with xref => this value gets send to the step method
#pragma endregion

#pragma region //x steps array
//the steps X needs to take for each time frame calculated with python script
int xsteps[] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 9, 9, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 16, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 382, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 421, 421, 421, 421, 421, 421, 421, 421, 422, 422, 422, 422, 422, 422, 422, 422, 423, 423, 423, 423, 423, 423, 423, 424, 424, 424, 424, 424, 424, 424, 413, 413, 413, 414, 413, 413, 394, 394, 393, 393, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 5, 5, 167, 167, 168, 168, 169, 169, 170, 170, 170, 171, 171, 171, 172, 172, 173, 173, 173, 174, 174, 174, 175, 175, 175, 176, 176, 177, 177, 177, 178, 178, 178, 179, 179, 180, 180, 180, 181, 181, 181, 182, 182, 183, 183, 183, 184, 184, 184, 185, 185, 186, 186, 186, 187, 187, 187, 188, 188, 189, 189, 189, 190, 190, 190, 191, 191, 192, 192, 192, 193, 193, 193, 194, 194, 194, 195, 195, 196, 196, 196, 197, 197, 197, 198, 198, 199, 199, 199, 200, 200, 201, 201, 201, 202, 202, 202, 203, 203, 204, 204, 204, 205, 205, 205, 206, 206, 207, 207, 207, 208, 208, 208, 209, 209, 209, 210, 210, 211, 211, 211, 212, 212, 212, 213, 213, 213, 214, 214, 214, 215, 215, 215, 216, 216, 216, 217, 217, 218, 218, 218, 219, 219, 219, 230, 229, 228, 228, 227, 227, 226, 226, 226, 225, 225, 224, 224, 223, 223, 223, 222, 222, 221, 221, 221, 220, 220, 220, 219, 219, 218, 218, 218, 217, 217, 216, 216, 216, 215, 215, 214, 214, 214, 213, 213, 213, 212, 212, 211, 211, 211, 210, 210, 209, 209, 209, 208, 208, 207, 207, 207, 206, 206, 205, 205, 204, 204, 204, 203, 203, 202, 202, 202, 201, 201, 200, 200, 200, 199, 199, 198, 198, 197, 197, 197, 196, 196, 195, 195, 194, 194, 194, 193, 193, 192, 192, 192, 191, 191, 190, 190, 189, 189, 189, 188, 188, 187, 187, 186, 186, 185, 185, 184, 184, 183, 183, 182, 182, 181, 181, 181, 180, 180, 179, 179, 178, 178, 177, 177, 177, 176, 176, 175, 175, 174, 174, 174, 173, 173, 172, 172, 172, 171, 171, 171, 170, 170, 170, 169, 169, 168};
#pragma endregion

#pragma region //y steps array
//the steps Y needs to take for each time frame calculated with python script
int ysteps[] = {15, 16, 19, 20, 37, 38, 39, 40, 18, 18, 18, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 17, 18, 18, 33, 34, 35, 35, 36, 37, 38, 39, 40, 41, 42, 43, 43, 44, 45, 46, 47, 48, 49, 50, 51, 51, 52, 53, 54, 57, 58, 58, 59, 60, 62, 63, 64, 65, 65, 66, 67, 70, 71, 368, 404, 405, 406, 408, 408, 408, 408, 408, 356, 362, 363, 363, 364, 365, 366, 367, 368, 376, 377, 378, 379, 379, 380, 383, 384, 385, 386, 388, 389, 390, 391, 392, 393, 394, 396, 397, 398, 401, 402, 402, 404, 405, 406, 407, 408, 409, 152, 152, 153, 153, 154, 154, 155, 156, 156, 157, 158, 158, 159, 160, 160, 161, 162, 162, 163, 164, 165, 165, 166, 167, 167, 168, 169, 169, 170, 171, 171, 172, 173, 173, 174, 175, 175, 176, 177, 177, 178, 179, 179, 180, 181, 182, 182, 183, 184, 184, 185, 186, 186, 187, 188, 188, 189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 196, 196, 197, 198, 198, 199, 200, 200, 201, 202, 203, 203, 204, 205, 205, 206, 207, 207, 208, 209, 209, 210, 211, 211, 212, 213, 213, 214, 215, 215, 216, 217, 217, 218, 219, 219, 220, 221, 221, 222, 223, 223, 224, 225, 225, 226, 227, 228, 228, 229, 230, 230, 231, 232, 232, 233, 234, 235, 235, 236, 237, 237, 238, 239, 239, 240, 241, 242, 242, 243, 244, 244, 245, 246, 246, 247, 248, 150, 151, 151, 152, 153, 153, 154, 154, 155, 155, 156, 157, 157, 158, 159, 159, 160, 160, 161, 162, 162, 163, 164, 164, 165, 166, 166, 167, 168, 168, 169, 169, 170, 171, 171, 172, 173, 173, 174, 175, 175, 176, 177, 177, 178, 179, 179, 180, 180, 181, 182, 182, 183, 184, 184, 185, 186, 186, 187, 187, 188, 189, 189, 190, 191, 191, 192, 192, 193, 194, 194, 195, 195, 196, 197, 197, 198, 198, 199, 200, 200, 201, 201, 202, 203, 203, 204, 205, 205, 206, 206, 207, 208, 208, 209, 209, 210, 210, 211, 212, 212, 213, 213, 214, 214, 215, 215, 216, 216, 217, 217, 218, 218, 219, 219, 219, 220, 220, 221, 222, 222, 223, 223, 224, 224, 225, 226, 226, 227, 227, 228, 229, 229, 230, 231, 231, 232, 232, 233, 234, 235, 235, 236, 237, 237, 238, 238};
#pragma endregion

int timeframe = 0;
#pragma endregion

void setup() 
{
  //set bits in ddrd register (datadirection register) to 1 for output 
  DDRD |= 1 << stepperx;
  DDRD |= 1 << xdir;
  DDRD |= 1 << steppery;
  DDRD |= 1 << ydir;
}

void loop() 
{
  deltax = xsteps[timeframe]-xref;
  deltay = ysteps[timeframe]-yref;
  step(deltax,deltay);
  delay(20);
  xref = xsteps[timeframe];
  yref = ysteps[timeframe];
  timeframe ++;
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

  while (x > 0 || y > 0)
  {  
    if (x > 0)
      PORTD |= 1 << stepperx;
      x--;
    if (y > 0)
      PORTD |= 1 << steppery;
      y--;
    delay(100);
    PORTD &= ~(1 << stepperx);
    PORTD &= ~(1 << steppery);
    delay(50);
  }
  
  

}
/*
X = 0 set entire byte
X |= 1 << 5 set specified bit
X &= ~(1 << 1) clear specified bit
*/
