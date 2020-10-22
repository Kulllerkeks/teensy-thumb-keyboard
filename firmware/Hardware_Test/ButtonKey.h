#ifndef ButtonKey_h
#define ButtonKey_h
#include "Arduino.h"

class ButtonKey {
public:
  ButtonKey(int pRow, int pCol);
  ButtonKey();
  int row;
  int col;
  bool pressed;
  String Name;
};
#endif
