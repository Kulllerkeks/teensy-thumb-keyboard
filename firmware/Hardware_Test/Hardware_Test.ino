/*
  Test Programm to verify all key rows and columns are working

  collects every button press and sends info data over serial 9600
  if anything is send to the controller
*/

#include "ButtonKey.h"

// Row Pins
#define ROW0 4
#define ROW1 5
#define ROW2 7
#define ROW3 8
#define ROW4 6
#define ROW5 9
// Column Pins
#define COL0 0
#define COL1 1
#define COL2 2
#define COL3 3
#define COL4 15
#define COL5 14
#define COL6 17
#define COL7 16
#define COL8 20
#define COL9 21

ButtonKey AllKeys[10][6];

int row_pins[6];
int col_pins[10];

void setup() {
  Serial.begin(9600);
  
  row_pins[0] = ROW0;
  row_pins[1] = ROW1;
  row_pins[2] = ROW2;
  row_pins[3] = ROW3;
  row_pins[4] = ROW4;
  row_pins[5] = ROW5;

  col_pins[0] = COL0;
  col_pins[1] = COL1;
  col_pins[2] = COL2;
  col_pins[3] = COL3;
  col_pins[4] = COL4;
  col_pins[5] = COL5;
  col_pins[6] = COL6;
  col_pins[7] = COL7;
  col_pins[8] = COL8;
  col_pins[9] = COL9;

  for (int r=0; r < 6; r++){
    pinMode(row_pins[r], INPUT_PULLUP);
    for (int c=0; c < 10; c++){
      pinMode(col_pins[c], INPUT);
      AllKeys[c][r] = ButtonKey(r, c);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int c=0; c < 10; c++){
    pinMode(col_pins[c], OUTPUT);
    digitalWrite(col_pins[c], LOW);
    for (int r=0; r < 6; r++){
      //read stuff
      if(digitalRead(row_pins[r]) == LOW){
        AllKeys[c][r].pressed = true;
      }
    }
    pinMode(col_pins[c], INPUT);
  }
  if (Serial.available() > 0) {
    Serial.read();
    Serial.println("Sending Pressed Buttons List");
    Serial.println("");
    for (int r=0; r < 6; r++){
      String pressedButtons = "";
      for(int c=0; c < 10; c++){  
        pressedButtons = pressedButtons + " C" + AllKeys[c][r].col + " R" + AllKeys[c][r].row + " p=";
        if(AllKeys[c][r].pressed){
          pressedButtons = pressedButtons + "A";
        }else{
          pressedButtons = pressedButtons + "X";
        }
      }
      Serial.println(pressedButtons);
    }
    
    Serial.println("");
    Serial.println("");
    Serial.println("------------------------------");
    for (int r=0; r < 6; r++){
      String pressedButtons = "";
      for(int c=0; c < 10; c++){  
        if(AllKeys[c][r].pressed){
          pressedButtons = pressedButtons + "|O|";
        }else{
          pressedButtons = pressedButtons + "|X|";
        }
      }
      Serial.println(pressedButtons);
      Serial.println("------------------------------");
    }
    Serial.println("");
    Serial.println("End of List ");
    Serial.read();
  }
}
