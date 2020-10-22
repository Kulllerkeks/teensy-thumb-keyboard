#include "Arduino.h"
#include "ButtonKey.h"

ButtonKey::ButtonKey(int pRow, int pCol)
{
  row = pRow;
  col = pCol;
  pressed = false;
}

ButtonKey::ButtonKey()
{
  pressed = false;
}
