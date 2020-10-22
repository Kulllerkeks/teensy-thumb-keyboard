#include <Mouse.h>  
#include <Bounce.h>
  
const int leftButtonPin = 7;  
const int rightButtonPin = 8;  
const int mouseSpeedDivisor = 60;
Bounce leftButton = Bounce(leftButtonPin, 10);
Bounce rightButton = Bounce(rightButtonPin, 10);

const int xPin = A0;  
const int yPin = A1;  
  
int xValue = 0;         // the sensor value  
int xMin = 1023;        // minimum sensor value  
int xMax = 0;           // maximum sensor value  
int yValue = 0;  
int yMin = 1023;  
int yMax = 0;  

int leftClickState = LOW;
int rightClickState = LOW;
  
//Refresh rate between polling intervals, lower is smoother movement  
#define REFRESH_RATE 1  
static unsigned long lastRefresh = 0;  
  
void setup()  
{  
  
  Serial.begin(9600);  
  pinMode(leftButtonPin, INPUT);  
  pinMode(rightButtonPin, INPUT);  
//  // turn on LED to signal the start of the calibration period:  
//  pinMode(13, OUTPUT);  
//  digitalWrite(13, HIGH);  
//  
//  // calibrate during the first five seconds  
//  while (millis() < 5000) {  
//   
//  }  
//  // signal the end of the calibration period  
//  digitalWrite(13, LOW);  
    
  Mouse.begin();  
}  
  
void loop()  
{  
  leftButton.update();
  rightButton.update();


  xValue = analogRead(xPin);  
  yValue = analogRead(yPin);  
  
  // record the maximum sensor value  
  if (xValue > xMax) {  
    xMax = xValue;  
  }  
  if (yValue > yMax) {  
    yMax = yValue;  
  }  
  
  // record the minimum sensor value  
  if (xValue < xMin) {  
    xMin = xValue;  
  }  
  if (yValue < yMin) {  
    yMin = yValue;  
  }  
  
  if (leftButton.risingEdge()) {
    Mouse.press(MOUSE_LEFT);
  }
  if (leftButton.fallingEdge()) {
    Mouse.release(MOUSE_LEFT);
  }
  
  if (rightButton.risingEdge()) {
    Mouse.press(MOUSE_RIGHT);
  }
  if (rightButton.fallingEdge()) {
    Mouse.release(MOUSE_RIGHT);
  }

  if ((lastRefresh + REFRESH_RATE) < millis())  
  {  
    moveMouse();  
  
    lastRefresh = millis();  
  }  
}  
  
void moveMouse()  
{  
  int xValue = analogRead(A1);  
  int yValue = analogRead(A0);  
  int xMove = (((xValue) - 512) / mouseSpeedDivisor);  
  int yMove = ((-1*((yValue) - 512) / mouseSpeedDivisor));  
  Serial.print("X: ");  
  Serial.print(xMove);  
  Serial.print(", Y: ");  
  Serial.print(yMove);  
  Mouse.move(xMove, yMove, 0);  
  Serial.println();  
}  
